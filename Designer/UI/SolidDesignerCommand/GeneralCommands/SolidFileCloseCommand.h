#pragma once

#include "BaseCommands/SolidBaseCommand.h"

namespace alice
{
	struct CommandParameter;
	class IOperation;
}

namespace sdr
{
	/// \brief Implements "file.close" for the active document view.
	class SolidFileCloseCommand final : public AppCommandBase
	{
	public:
		SolidFileCloseCommand() noexcept;
		~SolidFileCloseCommand() override;

		bool IsSupported() const override;
		bool IsVisible() const override;
		bool IsEnabled() const override;
		std::string DisabledReason() const override;

		std::unique_ptr<alice::IOperation> Execute(const alice::CommandParameter& param) override;
	};
}
