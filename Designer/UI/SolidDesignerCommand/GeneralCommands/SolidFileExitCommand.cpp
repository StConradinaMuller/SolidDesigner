#include "SolidFileExitCommand.h"
#include "SolidDesignerCommands.h"
#include "AliceCommandParameter.h"
#include <QCoreApplication>
#include "AliceIOperation.h"

using namespace sdr;

SolidFileExitCommand::SolidFileExitCommand() noexcept
	: AppCommandBase(std::string(Cmd::FILE_EXIT))
{
}

SolidFileExitCommand::~SolidFileExitCommand() = default;

bool SolidFileExitCommand::IsSupported() const
{
	return true;
}

bool SolidFileExitCommand::IsVisible() const
{
	return true;
}

bool SolidFileExitCommand::IsEnabled() const
{
	return true;
}

std::string SolidFileExitCommand::DisabledReason() const
{
	return {};
}

std::unique_ptr<alice::IOperation> SolidFileExitCommand::Execute(const alice::CommandParameter& /*param*/)
{
	QCoreApplication::quit();
	return nullptr;
}
