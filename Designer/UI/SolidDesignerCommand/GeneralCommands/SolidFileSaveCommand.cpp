#include "SolidFileSaveCommand.h"

#include "AliceIMainWindow.h"
#include "AliceIDocumentManager.h"
#include "AliceIDocument.h"
#include "AliceCommandParameter.h"
#include "AliceIOperation.h"
#include "SolidDesignerCommands.h"

#include "AliceCoreAppUtil.h"
#include "AliceISession.h"

#include "AliceIUiApplicationFactory.h"
#include "AliceIUiApplication.h"

#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QSettings>
#include <QFileInfo>
#include <QDir>

using namespace alice;
using namespace sdr;

SolidFileSaveCommand::SolidFileSaveCommand() noexcept
	: AppCommandBase(std::string(Cmd::FILE_SAVE))
{
}

SolidFileSaveCommand::~SolidFileSaveCommand()
{

}

bool SolidFileSaveCommand::IsSupported() const
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

bool SolidFileSaveCommand::IsVisible() const
{
	return IsSupported();
}

bool SolidFileSaveCommand::IsEnabled() const
{
	if (!IsSupported())
		return false;

	IDocument* doc = getActiveDocument_();
	return (doc != nullptr);
}

std::string SolidFileSaveCommand::DisabledReason() const
{
	//if (!m_mainWindow)
	//	return "Main window is not available.";

	//if (!m_docManager)
	//	return "Document manager is not available.";

	if (!getActiveDocument_())
		return "There is no active document to save.";

	return {};
}

std::unique_ptr<IOperation> SolidFileSaveCommand::Execute(const CommandParameter& param)
{
	if (!IsEnabled())
		return nullptr;

	IDocument* doc = getActiveDocument_();
	if (!doc)
		return nullptr;

	IMainWindow* mainWindow = nullptr;
	if (IUiApplicationFactory* pAppFactory = IUiApplicationFactory::Get())
	{
		if (IUiApplication* pApp = pAppFactory->GetUiApplication())
			mainWindow = const_cast<IMainWindow*>(pApp->GetMainWindow());
	}

	std::wstring path;
	bool         isSaveAs = false;

	if (hasFilePath_(*doc)) {
		// 已有路径：直接保存
		path = getFilePath_(*doc);
		isSaveAs = false;
	}
	else 
	{
		path = showSaveAsDialog_(L"");
		if (path.empty())
			return nullptr; 
		isSaveAs = true;
	}

	const bool ok = saveDocument_(*doc, path, isSaveAs);
	if (!ok)
	{
		if (QWidget* parent = mainWindow ? mainWindow->AsQMainWindow() : nullptr)
			QMessageBox::critical(parent, QObject::tr("Save"), QObject::tr("Failed to save file."));
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

	// 保存文件通常不进 Undo/Redo
	return nullptr;
}

IDocument* SolidFileSaveCommand::getActiveDocument_() const
{
	ISession* session = CoreAppUtil::GetCurrentSession();
	if (!session)
		return nullptr;
	return session->GetActiveDocument();
}

bool SolidFileSaveCommand::hasFilePath_(IDocument& doc) const
{
	return !doc.GetSourceUri().empty();
}

std::wstring SolidFileSaveCommand::getFilePath_(IDocument& doc) const
{
	return doc.GetSourceUri();
}

std::wstring SolidFileSaveCommand::showSaveAsDialog_(const std::wstring& hintPath) const
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
	const QString file = QFileDialog::getSaveFileName(parent, QObject::tr("Save"),
		dir.isEmpty() ? suggested : dir + QLatin1Char('/') + suggested, filter);
	if (file.isEmpty())
		return {};
	return file.toStdWString();
}

bool SolidFileSaveCommand::saveDocument_(IDocument& doc, const std::wstring& path, bool isSaveAs) const
{
	if (isSaveAs)
		return doc.SaveAs(path);
	return doc.Save();
}


