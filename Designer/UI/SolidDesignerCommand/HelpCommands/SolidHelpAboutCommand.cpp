#include "SolidHelpAboutCommand.h"
#include "SolidDesignerCommands.h"
#include "AliceIOperation.h"
#include "AliceIMainWindow.h"
#include "AliceIDocumentManager.h"
#include "AliceCommandParameter.h"

#include "AliceIUiApplicationFactory.h"
#include "AliceIUiApplication.h"

#include <QMessageBox>
#include <QSysInfo>
#include <QWidget>
#include <QMainWindow>

using namespace sdr;
using namespace alice;

sdr::SolidHelpAboutCommand::SolidHelpAboutCommand() noexcept
	: AppCommandBase(std::string(Cmd::HELP_ABOUT))
{

}

sdr::SolidHelpAboutCommand::~SolidHelpAboutCommand()
{

}

bool sdr::SolidHelpAboutCommand::IsSupported() const
{
	return IUiApplicationFactory::Get() != nullptr;
}

bool sdr::SolidHelpAboutCommand::IsVisible() const
{
	return IsSupported();
}

bool sdr::SolidHelpAboutCommand::IsEnabled() const
{
	return IsSupported();
}

std::string sdr::SolidHelpAboutCommand::DisabledReason() const
{
	return {};
}

std::unique_ptr<alice::IOperation> sdr::SolidHelpAboutCommand::Execute(const alice::CommandParameter& param)
{
	QWidget* parent = nullptr;
	if (auto* pFactory = IUiApplicationFactory::Get())
	{
		if (auto* pUiApp = pFactory->GetUiApplication())
		{
			if (alice::IMainWindow* pMainWindow = pUiApp->GetMainWindowFw())
			{
				parent = pMainWindow->AsQMainWindow();
			}
		}
	}

	QString text;
	text += QObject::tr("SolidDesigner\n");
	text += QObject::tr("Qt: %1\n").arg(qVersion());
	text += QObject::tr("OS: %1\n").arg(QSysInfo::prettyProductName());
	text += QObject::tr("CPU: %1\n").arg(QSysInfo::currentCpuArchitecture());

	QMessageBox::information(parent, QObject::tr("About"), text);
	return nullptr;
}
