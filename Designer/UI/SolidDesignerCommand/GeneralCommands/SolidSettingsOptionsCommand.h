#pragma once

#include "BaseCommands/SolidBaseCommand.h"

namespace alice { struct CommandParameter; class IOperation; }

namespace sdr
{
	/// \brief Opens an Options dialog (Backstage: Options).
	/// \note Not in CommandsConfig.xml yet; invoked directly by the Backstage.
	class SolidSettingsOptionsCommand final : public AppCommandBase
	{
	public:
		SolidSettingsOptionsCommand() noexcept;
		~SolidSettingsOptionsCommand() override;

		bool IsSupported() const override;
		bool IsVisible() const override;
		bool IsEnabled() const override;
		std::string DisabledReason() const override;

		std::unique_ptr<alice::IOperation> Execute(const alice::CommandParameter& param) override;
	};
}
