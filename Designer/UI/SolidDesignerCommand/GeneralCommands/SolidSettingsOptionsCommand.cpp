//Owner: hananiah
#include "SolidSettingsOptionsCommand.h"

#include "AliceCommandParameter.h"

#include "AliceIUiApplicationFactory.h"
#include "AliceIUiApplication.h"
#include "AliceIMainWindow.h"

#include <QDialog>
#include <QWidget>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLabel>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QMainWindow>
#include "AliceIOperation.h"

using namespace sdr;

SolidSettingsOptionsCommand::SolidSettingsOptionsCommand() noexcept
	: AppCommandBase(std::string("settings.options"))
{
}

SolidSettingsOptionsCommand::~SolidSettingsOptionsCommand() = default;

bool SolidSettingsOptionsCommand::IsSupported() const
{
	return alice::IUiApplicationFactory::Get() != nullptr;
}

bool SolidSettingsOptionsCommand::IsVisible() const
{
	return true;
}

bool SolidSettingsOptionsCommand::IsEnabled() const
{
	return true;
}

std::string SolidSettingsOptionsCommand::DisabledReason() const
{
	return {};
}

std::unique_ptr<alice::IOperation> SolidSettingsOptionsCommand::Execute(const alice::CommandParameter& /*param*/)
{
	QWidget* parent = nullptr;
	if (auto* pFactory = alice::IUiApplicationFactory::Get())
	{
		if (auto* app = pFactory->GetUiApplication())
		{
			if (auto* pMainWindow = app->GetMainWindowFw())
				parent = pMainWindow->AsQMainWindow();
		}
	}

	QDialog dlg(parent);
	dlg.setWindowTitle(QObject::tr("Options"));
	dlg.resize(640, 480);

	auto* layout = new QVBoxLayout(&dlg);
	auto* tabs = new QTabWidget(&dlg);

	// General
	{
		auto* page = new QWidget(tabs);
		auto* fl = new QFormLayout(page);
		fl->addRow(QObject::tr("Status"), new QLabel(QObject::tr("Options UI is available; settings persistence will be integrated later."), page));
		tabs->addTab(page, QObject::tr("General"));
	}

	// Display
	{
		auto* page = new QWidget(tabs);
		auto* fl = new QFormLayout(page);
		fl->addRow(QObject::tr("Viewport"), new QLabel(QObject::tr("Theme/viewport preferences are not wired yet."), page));
		tabs->addTab(page, QObject::tr("Display"));
	}

	// Files
	{
		auto* page = new QWidget(tabs);
		auto* fl = new QFormLayout(page);
		fl->addRow(QObject::tr("File"), new QLabel(QObject::tr("Default file locations and backups will be added later."), page));
		tabs->addTab(page, QObject::tr("Files"));
	}

	layout->addWidget(tabs, 1);

	auto* buttons = new QDialogButtonBox(QDialogButtonBox::Ok, &dlg);
	QObject::connect(buttons, &QDialogButtonBox::accepted, &dlg, &QDialog::accept);
	layout->addWidget(buttons);

	dlg.exec();
	return nullptr;
}
