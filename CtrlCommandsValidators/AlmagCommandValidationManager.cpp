#include <UserInterface/CtrlCommandsValidators/AlmagCommandValidationManager.hpp>

#include <memory>
#include <UserInterface/CtrlCommandsValidators/ICommandValidationStrategy.hpp>
#include <UserInterface/CtrlCommandsValidators/DummyScanValidationStrategy.hpp>
#include <UserInterface/CtrlCommandsValidators/NullValidationStrategy.hpp>
#include <PluginCommandConstraints/AlmagConstraints.hpp>
#include <Utils/Utils.hpp>

using namespace ui;
using namespace constraints::almag;

AlmagCommandValidationManager::AlmagCommandValidationManager(Database& db)
   : db_(db) {}

MaybeStrings AlmagCommandValidationManager::perform(const Strings& userInput)
{
   const auto& ALMAG_COMMAND_NAME = userInput[idx::COMMAND_OR_ACTION_NAME];
   LOG(trace) << "BEGIN " << ALMAG_COMMAND_NAME;

   std::unique_ptr<ICommandValidationStrategy> validationStrategy_;

   if (L1::DUMMY_SCAN == ALMAG_COMMAND_NAME
      or L1::SET_LINK_SPEED == ALMAG_COMMAND_NAME
      or L2::ADDRESS_ASSIGNMENT == ALMAG_COMMAND_NAME
      or L2::LINK_ESTABLISHMENT == ALMAG_COMMAND_NAME
      or L2::THREEGPP_RELEASE_ID == ALMAG_COMMAND_NAME
      or L2::AISG_PROTOCOL_VERSION == ALMAG_COMMAND_NAME
      or L7::CALIBRATE == ALMAG_COMMAND_NAME)
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

