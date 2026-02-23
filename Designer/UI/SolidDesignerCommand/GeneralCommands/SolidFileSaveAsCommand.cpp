#include "SolidFileSaveAsCommand.h"

#include "SolidDesignerCommands.h"

#include "AliceCommandParameter.h"
#include "AliceCoreAppUtil.h"
#include "AliceISession.h"
//Owner: hananiah
#include "AliceIDocument.h"
#include "AliceIUiApplicationFactory.h"
#include "AliceIUiApplication.h"
#include "AliceIMainWindow.h"
#include <QWidget>
#include <QMainWindow>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QSettings>
#include <QDir>
#include <QDateTime>
#include "AliceIOperation.h"

using namespace alice;
using namespace sdr;

SolidFileSaveAsCommand::SolidFileSaveAsCommand() noexcept
	: AppCommandBase(std::string(Cmd::FILE_SAVEAS))
{
}

SolidFileSaveAsCommand::~SolidFileSaveAsCommand() = default;

bool SolidFileSaveAsCommand::IsSupported() const
{
	ISession* session = CoreAppUtil::GetCurrentSession();
	if (!session)
		return false;
	if (!session->GetDocumentManagerFw())
		return false;
	IUiApplicationFactory* pAppFactory = IUiApplicationFactory::Get();
	if (!pAppFactory)
		return false;
	IUiApplication* pApp = pAppFactory->GetUiApplication();
	if (!pApp)
		return false;
	return pApp->GetMainWindow() != nullptr;
}

bool SolidFileSaveAsCommand::IsVisible() const
{
	return IsSupported();
}

bool SolidFileSaveAsCommand::IsEnabled() const
{
	if (!IsSupported())
		return false;
	ISession* session = CoreAppUtil::GetCurrentSession();
	return session && session->GetActiveDocument();
}

std::string SolidFileSaveAsCommand::DisabledReason() const
{
	ISession* session = CoreAppUtil::GetCurrentSession();
	if (!session)
		return "Session is not available.";
	if (!session->GetActiveDocument())
		return "There is no active document.";
	return {};
}

std::unique_ptr<IOperation> SolidFileSaveAsCommand::Execute(const CommandParameter& param)
{
	if (!IsEnabled())
		return nullptr;

	ISession* session = CoreAppUtil::GetCurrentSession();
	IDocument* doc = session ? session->GetActiveDocument() : nullptr;
	if (!doc)
		return nullptr;

	IMainWindow* pMainWindow = nullptr;
	if (IUiApplicationFactory* pAppFactory = IUiApplicationFactory::Get())
	{
		if (IUiApplication* pApp = pAppFactory->GetUiApplication())
			pMainWindow = pApp->GetMainWindowFw();
	}

	std::wstring path;
	const std::string paramPath = param.GetString("filePath");
	const std::string mode = param.GetString("mode");
	if (!paramPath.empty())
	{
		path = QString::fromUtf8(paramPath.c_str()).toStdWString();
	}
	else if (mode == "backup")
	{
		// Auto backup to the current document directory.
		QString basePath = QString::fromStdWString(doc->GetSourceUri());
		QFileInfo fi(basePath);
		QString dir = fi.exists() ? fi.absolutePath() : QDir::currentPath();
		QString stem = fi.exists() ? fi.completeBaseName() : QString::fromStdWString(doc->GetDocumentName());
		if (stem.isEmpty())
			stem = QStringLiteral("Untitled");
		const QString ts = QDateTime::currentDateTime().toString(QStringLiteral("yyyyMMdd_HHmmss"));
		QString out = dir + QLatin1Char('/') + stem + QStringLiteral("_backup_") + ts + QStringLiteral(".alice");
		path = out.toStdWString();
	}
	else
	{
		path = showSaveAsDialog_(doc->GetSourceUri());
	}

	if (path.empty())
		return nullptr;

	const bool ok = doc->SaveAs(path);

	if (!ok)
	{
		if (QWidget* parent = pMainWindow ? pMainWindow->AsQMainWindow() : nullptr)
			QMessageBox::critical(parent, QObject::tr("Save As"), QObject::tr("Failed to save file."));
		return nullptr;
	}

	// Update recent list.
	{
		const QString qpath = QDir::fromNativeSeparators(QString::fromStdWString(path));
		QSettings s("AliceSoft", "AliceCAD");
		s.beginGroup(QStringLiteral("Backstage"));
		QStringList list = s.value(QStringLiteral("RecentFiles")).toStringList();
		list.removeAll(qpath);
		list.prepend(qpath);
		while (list.size() > 20)
			list.removeLast();
		s.setValue(QStringLiteral("RecentFiles"), list);
		s.endGroup();
	}

	return nullptr;
}

std::wstring SolidFileSaveAsCommand::showSaveAsDialog_(const std::wstring& hintPath) const
{
	QWidget* parent = nullptr;
	if (IUiApplicationFactory* pAppFactory = IUiApplicationFactory::Get())
	{
		if (IUiApplication* pApp = pAppFactory->GetUiApplication())
		{
			if (const IMainWindow* mw = pApp->GetMainWindow())
				parent = const_cast<IMainWindow*>(mw)->AsQMainWindow();
		}
	}

	QString dir;
	QString suggested;
	if (!hintPath.empty())
	{
		QFileInfo fi(QString::fromStdWString(hintPath));
		dir = fi.absolutePath();
		suggested = fi.fileName();
	}

	const QString filter = QObject::tr("Alice Documents (*.alice);;All Files (*.*)");
	const QString file = QFileDialog::getSaveFileName(parent, QObject::tr("Save As"),
		dir.isEmpty() ? suggested : dir + QLatin1Char('/') + suggested, filter);
	if (file.isEmpty())
		return {};
	return file.toStdWString();
}
