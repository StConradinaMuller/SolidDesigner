#include "SolidHelpContentsCommand.h"
#include "SolidDesignerCommands.h"
#include "AliceIOperation.h"
#include "AliceCommandParameter.h"
#include "AliceIDocumentManager.h"
#include "AliceIMainWindow.h"

#include "AliceIUiApplicationFactory.h"
#include "AliceIUiApplication.h"

#include <QDesktopServices>
#include <QUrl>

using namespace alice;
using namespace sdr;

sdr::SolidHelpContentsCommand::SolidHelpContentsCommand() noexcept
	: AppCommandBase(std::string(Cmd::CMD_HELP_CONTENTS))
{

}

SolidHelpContentsCommand::~SolidHelpContentsCommand()
{

}

bool SolidHelpContentsCommand::IsSupported() const
{
	return true;
}

bool SolidHelpContentsCommand::IsEnabled() const
{
	return true;
}

bool SolidHelpContentsCommand::IsVisible() const
{
	return true;
}

std::string SolidHelpContentsCommand::DisabledReason() const
{
	return {};
}

std::unique_ptr<alice::IOperation> SolidHelpContentsCommand::Execute(const alice::CommandParameter& param)
{
	QDesktopServices::openUrl(QUrl(QStringLiteral("https://github.com/Ludwigstrasse/SolidDesigner")));
	return nullptr;
}