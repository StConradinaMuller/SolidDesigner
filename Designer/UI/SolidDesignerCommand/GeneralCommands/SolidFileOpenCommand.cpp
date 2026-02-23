#include "SolidFileOpenCommand.h"

#include "AliceIMainWindow.h"
#include "AliceIDocumentManager.h"
#include "AliceIDocument.h"
#include "AliceCommandParameter.h"
#include "AliceIOperation.h"
#include "SolidDesignerCommands.h"

#include "AliceCoreAppUtil.h"
#include "AliceISession.h"
#include "AliceIWorkBenchManager.h"

#include "AliceIUiApplicationFactory.h"
#include "AliceIUiApplication.h"

#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QSettings>
#include <QDir>

using namespace alice;
using namespace sdr;

SolidFileOpenCommand::SolidFileOpenCommand() noexcept
	: AppCommandBase(std::string(Cmd::FILE_OPEN))
{
}

SolidFileOpenCommand::~SolidFileOpenCommand()
{

}

bool SolidFileOpenCommand::IsSupported() const
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

bool SolidFileOpenCommand::IsVisible() const
{
	return IsSupported();
}

bool SolidFileOpenCommand::IsEnabled() const
{
	return IsSupported();
}

std::string SolidFileOpenCommand::DisabledReason() const
{
	//if (!m_mainWindow)
	//	return "Main window is not available.";

	//if (!m_docManager)
	//	return "Document manager is not available.";

	return {};
}

std::unique_ptr<IOperation> SolidFileOpenCommand::Execute(const CommandParameter& param)
{
	if (!IsEnabled())
		return nullptr;

	ISession* session = CoreAppUtil::GetCurrentSession();
	if (!session)
		return nullptr;

	IMainWindow* mainWindow = nullptr;
	if (IUiApplicationFactory* pAppFactory = IUiApplicationFactory::Get())
	{
		if (IUiApplication* pApp = pAppFactory->GetUiApplication())
			mainWindow = const_cast<IMainWindow*>(pApp->GetMainWindow());
	}

	std::wstring filePath;
	const std::string paramPath = param.GetString("filePath");
	if (!paramPath.empty())
		filePath = QString::fromUtf8(paramPath.c_str()).toStdWString();
	else
		filePath = showOpenFileDialog_();
	if (filePath.empty())
		return nullptr; // 用户取消

	IDocument* doc = session->OpenDocument(filePath);
	if (!doc) 
	{
		if (QWidget* parent = mainWindow ? mainWindow->AsQMainWindow() : nullptr)
			QMessageBox::critical(parent, QObject::tr("Open"), QObject::tr("Failed to open file."));
		return nullptr;
	}

	// Workbench switching + view opening
	if (mainWindow)
	{
		if (IWorkBenchManager* pWbMgr = mainWindow->GetWorkbenchManager())
		{
			std::string wbId = pWbMgr->ResolveWorkbenchByDocument(doc);
			if (!wbId.empty())
				pWbMgr->ActivateWorkBench(wbId, doc);
			else
				pWbMgr->ActiveStartupWorkbench(doc);
		}
	}

	// Update recent list (Backstage uses the same key).
	{
		const QString path = QDir::fromNativeSeparators(QString::fromStdWString(filePath));
		QSettings s("AliceSoft", "AliceCAD");
		s.beginGroup(QStringLiteral("Backstage"));
		QStringList list = s.value(QStringLiteral("RecentFiles")).toStringList();
		list.removeAll(path);
		list.prepend(path);
		while (list.size() > 20)
			list.removeLast();
		s.setValue(QStringLiteral("RecentFiles"), list);
		s.endGroup();
	}

	return nullptr;
}

std::wstring SolidFileOpenCommand::showOpenFileDialog_() const
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
	const QString filter = QObject::tr("Alice Documents (*.alice);;All Files (*.*)");
	const QString file = QFileDialog::getOpenFileName(parent, QObject::tr("Open"), QString(), filter);
	if (file.isEmpty())
		return {};
	return file.toStdWString();
}

IDocument* SolidFileOpenCommand::openDocument_(const std::wstring& filePath) const
{
	//if (!m_docManager)
	//	return nullptr;

	//return m_docManager->OpenFromFile(filePath);
	return nullptr;
}

//QWidget* SolidFileOpenCommand::openViewForDocument_(IDocument* doc,
//	const std::wstring& filePath) const
//{
//	if (!m_mainWindow || !doc)
//		return nullptr;
//
//	const std::string viewKind = "view.default.fromDocKind"; 
//	const QString     title = QString::fromStdWString(filePath);
//
//	QWidget* w = m_mainWindow->OpenView(viewKind, static_cast<void*>(doc), title);
//	return w;
//}
