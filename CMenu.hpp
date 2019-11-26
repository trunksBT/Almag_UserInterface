#pragma once

#include <functional>
#include <string>
#include <vector>

#include <CommandPattern/IAlmagController.hpp>
#include <Database/Database.hpp>
#include <UserInterface/CtrlCommandsValidators/AlmagCommandValidationManager.hpp>
#include <Utils/UserCommandParser.hpp>

class CMenu
{
public:
   CMenu(const std::string& inMenuName, const std::string& inCommandName,
      Database& inDb, IAlmagControllerPtr almagCtrl);

   virtual ~CMenu() = default;

   bool run(const Strings& inArgs);
   bool runPredefinedCommands(const StringsMatrix& inCommands);

private:
	ReturnCode runImpl(const Strings& userInput);

   bool isAction(const std::string& zeroArgOfUserInput);
   bool isDatabaseCommand(const std::string& zeroArgOfUserInput);
   bool isAlmagControllerCommand(const std::string& zeroArgOfUserInput);

   ReturnCode interpretAction(const Strings& userInput);
   ReturnCode interpretDatabaseCommand(const Strings& userInput);
   ReturnCode interpretControllerCommand(const Strings& userInput); 

   UserCommandParser parser_;
   Database& db_;
   IAlmagControllerPtr almagCtrl_;
   AlmagCommandValidationManager almagCommandValidationMgr_;
};

