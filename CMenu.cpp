#include "UserInterface/CMenu.hpp"
#include <CommandPattern/AlmagControllerNull.hpp>
#include <UserInterface/Database/Brokers/Broker_IOPaths.hpp>
#include <UserInterface/Database/CDatabaseCommand.hpp>
#include <PluginConstraints/DatabaseConstraints.hpp> // TO REMOVE
#include <Utils/Functions.hpp>
#include <Utils/Utils.hpp>
#include <Utils/Logger.hpp>

using namespace defaultVals;
using namespace ui;
using namespace constraints;

CMenu::CMenu(
   const std::string&  inMenuName, const std::string& inCommandName,
   Database& inDB, IAlmagControllerPtr almagCtrl)
   : db_(inDB)
   , almagCtrl_(almagCtrl)
   , almagCommandValidationMgr_(db_)
{}

bool CMenu::run(const Strings& inArgs)
{
   ReturnCode finalResultCode = true;

	while (finalResultCode)
	{
	   Strings userInput = parser_.receiveAndLex();
      finalResultCode &= runImpl(userInput);
	}
	return finalResultCode;
}

bool CMenu::runPredefinedCommands(const StringsMatrix& inCommands)
{
   LOG(info) << "Zaczynam tworzyc predifiniowane menu";
   ReturnCode finalResultCode = true;

	for (const auto& it : inCommands)
	{
      finalResultCode &= runImpl(it);
	}
   LOG(info) << "Skonczylem tworzyc predifiniowane menu";
	return finalResultCode;
}

ReturnCode CMenu::runImpl(const Strings& userInput)
{
	if (userInput.size() == 0)
	{
      LOG(error) << "Empty user input";
		LOG(debug) << actionHelp();
		return false;
	}
	std::string receivedCmd = userInput[idx::COMMAND_OR_ACTION_NAME];

   if (funs::anyOf(databaseCommandConstraints_, receivedCmd))
   {
      LOG(info) << receivedCmd;
		return interpretDatabaseCommand(userInput);
   }
   else if (funs::anyOf(almagCommandConstraints_, receivedCmd))
   {
      LOG(info) << receivedCmd;
		return interpretControllerCommand(userInput);
   }
   else if (actions::HELP == receivedCmd)
	{
	   LOG(info) << actionHelp();
	   return true;
	}
   else if (actions::EXIT == receivedCmd)
   {
      return false;
   }
	else
	{
      LOG(info) << receivedCmd << actions::HELP_WHEN_UNKNOWN;
		return true;
	}
}

ReturnCode CMenu::interpretControllerCommand(const Strings& userInput)
{
   LOG(debug) << "Przed wykonaniem komendy";

   if (const auto validatedUserInput = almagCommandValidationMgr_.perform(userInput))
   {
      almagCtrl_->addCommands({*validatedUserInput});
      almagCtrl_->executeCommand();
		return true;
   }
   else
   {
      LOG(warning) << "Validation rejected the command";
		return true;
   }
}

ReturnCode CMenu::interpretDatabaseCommand(const Strings& userInput)
{
   LOG(info) << "Przed wykonaniem komendy";
	const std::string& dbAction = userInput[idx::COMMAND_OR_ACTION_NAME];

   if (database::GET == dbAction)
   {
      if (validateUserInput(userInput, reqNumOfArgsFor::db::GET))
      {
         LOG(info)
            << userInput[0] << " "
            << userInput[1];
         CDatabaseCommand updateDatabase(db_, userInput);
         updateDatabase.runCommand();
		   return true;
      }
   }
   else if (database::PUT == dbAction)
   {
      if (validateUserInput(userInput, reqNumOfArgsFor::db::PUT))
      {
         LOG(info)
            << userInput[0] << " "
            << userInput[1] << " "
            << userInput[2] << " "
            << userInput[3];
         CDatabaseCommand updateDatabase(db_, userInput);
         updateDatabase.runCommand();
         return true;
      }
   }
   LOG(info) << "Po wykonaniu komendy";
   return true;
}

void CMenu::setAlmagCommandsConstraints(const Strings& constraints)
{
   almagCommandConstraints_ = constraints;
}

void CMenu::setDatabaseCommandsConstraints(const Strings& constraints)
{
   databaseCommandConstraints_ = constraints;
}
