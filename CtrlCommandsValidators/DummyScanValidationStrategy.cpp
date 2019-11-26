#include <UserInterface/CtrlCommandsValidators/DummyScanValidationStrategy.hpp>
#include <Utils/Logger.hpp>

MaybeStrings DummyScanValidationStrategy::validateInputCorrectness(Strings userInput)
{
   if (not (2 <= userInput.size()))
   {
      LOG(error) << "Requires path of port as second argument";
      return boost::none;
   }

   return userInput;
}

MaybeStrings DummyScanValidationStrategy::modifyIfRequired(Strings validatedUserInput)
{
   return validatedUserInput;
}

