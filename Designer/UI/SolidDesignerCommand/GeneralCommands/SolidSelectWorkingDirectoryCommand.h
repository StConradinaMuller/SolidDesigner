#pragma once

#include "BaseCommands/SolidBaseCommand.h"

namespace alice { struct CommandParameter; class IOperation; }

namespace sdr
{
	/// \brief Implements Backstage: Manage Session -> Select Working Directory.
	class SolidSelectWorkingDirectoryCommand final : public AppCommandBase
	{
	public:
		SolidSelectWorkingDirectoryCommand() noexcept;
		~SolidSelectWorkingDirectoryCommand() override;

		bool IsSupported() const override;
		bool IsVisible() const override;
		bool IsEnabled() const override;
		std::string DisabledReason() const override;

		std::unique_ptr<alice::IOperation> Execute(const alice::CommandParameter& param) override;
	};
}
