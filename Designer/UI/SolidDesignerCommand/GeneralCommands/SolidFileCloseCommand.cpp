// Owner: hananiah
#include "SolidFileCloseCommand.h"
#include "SolidDesignerCommands.h"
#include "AliceCommandParameter.h"
#include "AliceCoreAppUtil.h"
#include "AliceISession.h"
#include "AliceIDocument.h"
#include "AliceIUiApplicationFactory.h"
#include "AliceIUiApplication.h"
#include "AliceIMainWindow.h"
#include "AliceIOperation.h"

using namespace alice;
using namespace sdr;

SolidFileCloseCommand::SolidFileCloseCommand() noexcept
	: AppCommandBase(std::string(Cmd::FILE_CLOSE))
{
}

SolidFileCloseCommand::~SolidFileCloseCommand() = default;

bool SolidFileCloseCommand::IsSupported() const
{
	ISession* session = CoreAppUtil::GetCurrentSession();
	if (!session)
		return false;
	IUiApplicationFactory* pAppFactory = IUiApplicationFactory::Get();
	if (!pAppFactory)
		return false;
	IUiApplication* pApp = pAppFactory->GetUiApplication();
	if (!pApp)
		return false;
	return pApp->GetMainWindow() != nullptr;
}

bool SolidFileCloseCommand::IsVisible() const
{
	return IsSupported();
}

bool SolidFileCloseCommand::IsEnabled() const
{
	if (!IsSupported())
		return false;
	ISession* session = CoreAppUtil::GetCurrentSession();
	return session && session->GetActiveDocument();
}

std::string SolidFileCloseCommand::DisabledReason() const
{
	ISession* session = CoreAppUtil::GetCurrentSession();
	if (!session)
		return "Session is not available.";
	if (!session->GetActiveDocument())
		return "There is no active document.";
	return {};
}

std::unique_ptr<IOperation> SolidFileCloseCommand::Execute(const CommandParameter& /*param*/)
{
	if (!IsSupported())
		return nullptr;

	IUiApplicationFactory* pAppFactory = IUiApplicationFactory::Get();
	IUiApplication* pApp = pAppFactory ? pAppFactory->GetUiApplication() : nullptr;
	IMainWindow* pMainWindow = pApp ? pApp->GetMainWindowFw() : nullptr;
	if (!pMainWindow)
		return nullptr;

	pMainWindow->CloseCurrentView();
	return nullptr;
}
