#pragma once

#include <functional>
#include <string>
#include <vector>

#include <Controller/IController.hpp>
#include <Database/Database.hpp>
#include <UserInterface/CtrlCommandsValidators/ICmdValidationManager.hpp>
#include <Utils/UserCommandParser.hpp>

class CMenu
{
public:
   CMenu(const std::string& inMenuName, const std::string& inCommandName, Database& inDb, IAlmagControllerPtr almagCtrl,
      ICmdValidationManagerPtr almagCmdValidationMgr, ICmdValidationManagerPtr databaseCmdValidationMgr);

   virtual ~CMenu() = default;

   bool run(const Strings& inArgs);
   bool runPredefinedCommands(const StringsMatrix& inCommands);
   void setAlmagCommandsConstraints(const Strings& constraints);
   void setDatabaseCommandsConstraints(const Strings& constraints);

private:
	ReturnCode runImpl(const Strings& userInput);

   ReturnCode interpretDatabaseCommand(const Strings& userInput);
   ReturnCode interpretControllerCommand(const Strings& userInput); 

   UserCommandParser parser_;
   Database& db_;
   IAlmagControllerPtr almagCtrl_;
   ICmdValidationManagerPtr almagCmdValidationMgr_;
   ICmdValidationManagerPtr databaseCmdValidationMgr_;
   Strings almagCommandConstraints_;
   Strings databaseCommandConstraints_;
};

