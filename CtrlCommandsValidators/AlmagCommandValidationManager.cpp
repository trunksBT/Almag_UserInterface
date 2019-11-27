#include "UserInterface/CtrlCommandsValidators/AlmagCommandValidationManager.hpp"
#include <memory>
#include <UserInterface/CtrlCommandsValidators/ICommandValidationStrategy.hpp>
#include <UserInterface/CtrlCommandsValidators/DummyScanValidationStrategy.hpp>
#include <UserInterface/CtrlCommandsValidators/NullValidationStrategy.hpp>
#include <PluginConstraints/AlmagConstraints.hpp>
#include <Utils/Utils.hpp>
#include <Utils/Logger.hpp>
#include <Utils/Functions.hpp>

using namespace constraints::almag;

AlmagCommandValidationManager::AlmagCommandValidationManager(Database& db)
   : ICmdValidationManager{db} {}

MaybeStrings AlmagCommandValidationManager::perform(const Strings& userInput)
{
   const auto& ALMAG_COMMAND_NAME = userInput[idx::COMMAND_OR_ACTION_NAME];
   LOG(trace) << "BEGIN " << ALMAG_COMMAND_NAME;

   std::unique_ptr<ICommandValidationStrategy> validationStrategy_;
   if (funs::anyOf(
   {constraints::almag::values.begin(), constraints::almag::values.end()}, ALMAG_COMMAND_NAME))
   {
      validationStrategy_ = std::make_unique<DummyScanValidationStrategy>();
   }
   else if (command::START_POOLING == ALMAG_COMMAND_NAME)
   {
      validationStrategy_ = std::make_unique<NullValidationStrategy>();
   }

   if (validationStrategy_)
   {
      return validationStrategy_->execute(userInput);
   }
   else
   {
      LOG(warning) << "Unknown almag command " << ALMAG_COMMAND_NAME;
      return boost::none;
   }
}
