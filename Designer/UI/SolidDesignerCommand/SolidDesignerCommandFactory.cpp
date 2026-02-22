#include "SolidDesignerCommandFactory.h"
#include "EditCommands/SolidEditUndoCommand.h"
#include "GeneralCommands/SolidFileNewCommand.h"
#include "GeneralCommands/SolidFileOpenCommand.h"
#include "GeneralCommands/SolidFileSaveCommand.h"
#include "GeneralCommands/SolidFileSaveAsCommand.h"
#include "GeneralCommands/SolidFileCloseCommand.h"
#include "GeneralCommands/SolidFileExitCommand.h"
#include "GeneralCommands/SolidSettingsOptionsCommand.h"
#include "GeneralCommands/SolidManageFileRenameCommand.h"
#include "GeneralCommands/SolidSelectWorkingDirectoryCommand.h"
#include "GeneralCommands/SolidSessionObjectListCommand.h"
#include "HelpCommands/SolidHelpAboutCommand.h"
#include "HelpCommands/SolidHelpContentsCommand.h"
#include "ModelCommands/SolidModelBlendCommand.h"
#include "ModelCommands/SolidModelExtrudeCommand.h"
#include "ModelCommands/SolidModelHelicalSweepCommand.h"
#include "ModelCommands/SolidModelHoleCommand.h"
#include "ModelCommands/SolidModelRevolveCommand.h"
#include "ModelCommands/SolidModelRotationalBlendCommand.h"
#include "ModelCommands/SolidModelSweepCommand.h"
#include "ModelCommands/SolidModelSweptBlendCommand.h"
#include "ModelCommands/SolidModelVolumeHelicalSweepCommand.h"
#include "EditCommands/SolidEditCopyCommand.h"
#include "EditCommands/SolidEditCutCommand.h"
#include "EditCommands/SolidEditDeleteCommand.h"
#include "EditCommands/SolidEditPasteCommand.h"
#include "EditCommands/SolidEditRedoCommand.h"
#include "EditCommands/SolidEditSelectAllCommand.h"

using namespace sdr;

sdr::SolidDesignerCommandFactory& SolidDesignerCommandFactory::GetInstance()
{
	static SolidDesignerCommandFactory s_Instance;
	return s_Instance;
}

std::vector<std::shared_ptr<alice::ICommand>> SolidDesignerCommandFactory::CreateCommands()
{
	std::vector<std::shared_ptr<alice::ICommand>> vecCommands;
	vecCommands.emplace_back(std::make_shared<SolidEditCopyCommand>());
	vecCommands.emplace_back(std::make_shared<SolidEditCutCommand>());
	vecCommands.emplace_back(std::make_shared<SolidEditDeleteCommand>());
	vecCommands.emplace_back(std::make_shared<SolidEditPasteCommand>());
	vecCommands.emplace_back(std::make_shared<SolidEditRedoCommand>());
	vecCommands.emplace_back(std::make_shared<SolidEditSelectAllCommand>());
	vecCommands.emplace_back(std::make_shared<SolidEditUndoCommand>());

	vecCommands.emplace_back(std::make_shared<SolidFileNewCommand>());
	vecCommands.emplace_back(std::make_shared<SolidFileOpenCommand>());
	vecCommands.emplace_back(std::make_shared<SolidFileSaveCommand>());
	vecCommands.emplace_back(std::make_shared<SolidFileSaveAsCommand>());
	vecCommands.emplace_back(std::make_shared<SolidFileCloseCommand>());
	vecCommands.emplace_back(std::make_shared<SolidFileExitCommand>());
	vecCommands.emplace_back(std::make_shared<SolidSettingsOptionsCommand>());
	vecCommands.emplace_back(std::make_shared<SolidManageFileRenameCommand>());
	vecCommands.emplace_back(std::make_shared<SolidSelectWorkingDirectoryCommand>());
	vecCommands.emplace_back(std::make_shared<SolidSessionObjectListCommand>());

	vecCommands.emplace_back(std::make_shared<SolidHelpAboutCommand>());
	vecCommands.emplace_back(std::make_shared<SolidHelpContentsCommand>());

	vecCommands.emplace_back(std::make_shared<SolidModelBlendCommand>());
	vecCommands.emplace_back(std::make_shared<SolidModelExtrudeCommand>());
	vecCommands.emplace_back(std::make_shared<SolidModelHelicalSweepCommand>());
	vecCommands.emplace_back(std::make_shared<SolidModelHoleCommand>());
	vecCommands.emplace_back(std::make_shared<SolidModelRevolveCommand>());
	vecCommands.emplace_back(std::make_shared<SolidModelRotationalBlendCommand>());
	vecCommands.emplace_back(std::make_shared<SolidModelSweepCommand>());
	vecCommands.emplace_back(std::make_shared<SolidModelSweptBlendCommand>());
	vecCommands.emplace_back(std::make_shared<SolidModelVolumeHelicalSweepCommand>());

	return vecCommands;
}
