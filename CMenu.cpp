#include "UserInterface/CMenu.hpp"
#include <Controller/KorytkoMagControllerNull.hpp>
#include <UserInterface/Database/CDatabaseCommand.hpp>
#include <Utils/Functions.hpp>
#include <Utils/Logger.hpp>
#include <Utils/Utils.hpp>

using namespace convert;
using namespace defaultVals;
using namespace ui;

CMenu::CMenu(
   const std::string& inMenuName,
   const std::string& inCommandName,
   Database& inDB,
   IKorytkoMagControllerPtr korytkomagCtrl,
   ICmdValidationManagerPtr korytkomagCmdValidationMgr,
   ICmdValidationManagerPtr databaseCmdValidationMgr
)  : db_{inDB}, korytkomagCtrl_{korytkomagCtrl}
   , korytkomagCmdValidationMgr_{korytkomagCmdValidationMgr}
   , databaseCmdValidationMgr_{databaseCmdValidationMgr}
{}

bool CMenu::run(const Strings& inArgs)
{
   ReturnCode finalResultCode = true;

	while (finalResultCode)
      finalResultCode &= runImpl(parser_.receiveAndLex());

	return finalResultCode;
}

bool CMenu::runPredefinedCommands(const StringsMatrix& inCommands)
{
   LOG(info) << "Start";
   ReturnCode finalResultCode = true;

	for (const auto& it : inCommands)
      finalResultCode &= runImpl(it);

   LOG(info) << END;
	return finalResultCode;
}

ReturnCode CMenu::runImpl(const Strings& userInput)
{
	if (userInput.size() == 0)
	{
      LOG(error) << "Empty user input";
      LOG(info) << toString(korytkomagCommandConstraints_);
		return false;
	}
	std::string receivedCmd = userInput[idx::COMMAND_OR_ACTION_NAME];

   if (funs::anyOf(databaseCommandConstraints_, receivedCmd))
   {
      LOG(info) << receivedCmd;
		return interpretDatabaseCommand(userInput);
   }
   else if (funs::anyOf(korytkomagCommandConstraints_, receivedCmd))
   {
      LOG(info) << receivedCmd;
		return interpretControllerCommand(userInput);
   }
   else if (actions::HELP == receivedCmd)
	{
      LOG(info) << toString(korytkomagCommandConstraints_);
	   return true;
	}
   else if (actions::EXIT == receivedCmd)
   {
      return false;
   }
   LOG(info) << receivedCmd << actions::HELP_WHEN_UNKNOWN;
	return true;
}

ReturnCode CMenu::interpretControllerCommand(const Strings& userInput)
{
   LOG(debug) << "Start";
   if (const auto validatedUserInput = korytkomagCmdValidationMgr_->perform(userInput))
   {
      korytkomagCtrl_->addCommands({*validatedUserInput});
      return korytkomagCtrl_->executeCommand();
   }
   LOG(warning) << "Validation rejected the command";
   return true;
}

ReturnCode CMenu::interpretDatabaseCommand(const Strings& userInput)
{
   LOG(debug) << "Start";
   if (const auto validatedUserInput = databaseCmdValidationMgr_->perform(userInput))
   {
      CDatabaseCommand updateDatabase(db_, *validatedUserInput);
      return updateDatabase.runCommand();
   }
   LOG(warning) << "Validation rejected the command";
   return true;
}

void CMenu::setKorytkoMagCommandsConstraints(const Strings& constraints)
{
   korytkomagCommandConstraints_ = constraints;
}

void CMenu::setDatabaseCommandsConstraints(const Strings& constraints)
{
   databaseCommandConstraints_ = constraints;
}
