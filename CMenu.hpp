#pragma once

#include <functional>
#include <string>
#include <vector>

#include <Controller/CmdValidationRules/ICmdValidationManager.hpp>
#include <Controller/IController.hpp>
#include <Database/Database.hpp>
#include <Utils/UserCommandParser.hpp>

class CMenu
{
public:
   CMenu(
      const std::string& inMenuName,
      const std::string& inCommandName,
      Database& inDb,
      IKorytkoMagControllerPtr korytkomagCtrl,
      ICmdValidationManagerPtr korytkomagCmdValidationMgr,
      ICmdValidationManagerPtr databaseCmdValidationMgr
   );

   virtual ~CMenu() = default;

   bool run(const Strings& inArgs);
   bool runPredefinedCommands(const StringsMatrix& inCommands);
   void setKorytkoMagCommandsConstraints(const Strings& constraints);
   void setDatabaseCommandsConstraints(const Strings& constraints);

private:
	ReturnCode runImpl(const Strings& userInput);

   ReturnCode interpretDatabaseCommand(const Strings& userInput);
   ReturnCode interpretControllerCommand(const Strings& userInput); 

   UserCommandParser parser_;
   Database& db_;
   IKorytkoMagControllerPtr korytkomagCtrl_;
   ICmdValidationManagerPtr korytkomagCmdValidationMgr_;
   ICmdValidationManagerPtr databaseCmdValidationMgr_;
   Strings korytkomagCommandConstraints_;
   Strings databaseCommandConstraints_;
};

