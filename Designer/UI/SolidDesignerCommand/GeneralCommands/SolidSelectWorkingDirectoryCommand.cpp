#include "SolidSelectWorkingDirectoryCommand.h"

#include "AliceCommandParameter.h"

#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>
#include "AliceIOperation.h"

using namespace sdr;

SolidSelectWorkingDirectoryCommand::SolidSelectWorkingDirectoryCommand() noexcept
	: AppCommandBase(std::string("data.select_working_directory"))
{
}

SolidSelectWorkingDirectoryCommand::~SolidSelectWorkingDirectoryCommand() = default;

bool SolidSelectWorkingDirectoryCommand::IsSupported() const { return true; }
bool SolidSelectWorkingDirectoryCommand::IsVisible() const { return true; }
bool SolidSelectWorkingDirectoryCommand::IsEnabled() const { return true; }
std::string SolidSelectWorkingDirectoryCommand::DisabledReason() const { return {}; }

std::unique_ptr<alice::IOperation> SolidSelectWorkingDirectoryCommand::Execute(const alice::CommandParameter& /*param*/)
{
	const QString dir = QFileDialog::getExistingDirectory(nullptr, QObject::tr("Select Working Directory"));
	if (dir.isEmpty())
		return nullptr;

	QSettings s("AliceSoft", "AliceCAD");
	s.beginGroup(QStringLiteral("Session"));
	s.setValue(QStringLiteral("WorkingDirectory"), QDir::fromNativeSeparators(dir));
	s.endGroup();

	QDir::setCurrent(dir);
	QMessageBox::information(nullptr, QObject::tr("Working Directory"), QObject::tr("Working directory set to:\n%1").arg(dir));
	return nullptr;
}
