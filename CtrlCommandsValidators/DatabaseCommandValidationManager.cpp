#include "UserInterface/CtrlCommandsValidators/DatabaseCommandValidationManager.hpp"
#include <UserInterface/CtrlCommandsValidators/ICommandValidationStrategy.hpp>
#include <UserInterface/CtrlCommandsValidators/NullValidationStrategy.hpp>
#include <Database/DatabaseConstraints.hpp>

#include <Utils/Utils.hpp>
#include <Utils/Logger.hpp>

using namespace constraints;
using namespace ui;

DatabaseCommandValidationManager::DatabaseCommandValidationManager(Database& db)
   : ICmdValidationManager{db} {}

MaybeStrings DatabaseCommandValidationManager::perform(const Strings& userInput)
{
   const std::string& dbAction = userInput[idx::COMMAND_OR_ACTION_NAME];
   if (database::GET == dbAction)
   {
      if (validateUserInput(userInput, reqNumOfArgsFor::db::GET))
      {
         LOG(info)
            << userInput[0] << " "
            << userInput[1];
         return userInput;
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
         return userInput;
      }
   }
   return {};
}
