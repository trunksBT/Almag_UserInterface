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
   void setAlmagCommandsConstraints(const Strings& constraints);

private:
	ReturnCode runImpl(const Strings& userInput);

   bool isDatabaseCommand(const std::string& zeroArgOfUserInput);

   ReturnCode interpretDatabaseCommand(const Strings& userInput);
   ReturnCode interpretControllerCommand(const Strings& userInput); 

   UserCommandParser parser_;
   Database& db_;
   IAlmagControllerPtr almagCtrl_;
   AlmagCommandValidationManager almagCommandValidationMgr_;
   Strings almagCommandConstraints_;
};

