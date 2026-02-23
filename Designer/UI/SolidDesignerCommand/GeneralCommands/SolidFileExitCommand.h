#pragma once

#include "BaseCommands/SolidBaseCommand.h"

namespace alice { struct CommandParameter; class IOperation; }

namespace sdr
{
	/// \brief Implements "file.exit".
	class SolidFileExitCommand final : public AppCommandBase
	{
	public:
		SolidFileExitCommand() noexcept;
		~SolidFileExitCommand() override;

		bool IsSupported() const override;
		bool IsVisible() const override;
		bool IsEnabled() const override;
		std::string DisabledReason() const override;

		std::unique_ptr<alice::IOperation> Execute(const alice::CommandParameter& param) override;
	};
}
