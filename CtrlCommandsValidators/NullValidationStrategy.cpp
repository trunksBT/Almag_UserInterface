#include <UserInterface/CtrlCommandsValidators/NullValidationStrategy.hpp>
#include <Utils/Logger.hpp>

MaybeStrings NullValidationStrategy::validateInputCorrectness(Strings userInput)
{
   LOG(warning) << "***";
   return userInput;
}

MaybeStrings NullValidationStrategy::modifyIfRequired(Strings validatedUserInput)
{
   LOG(warning) << "***";
   return validatedUserInput;
}

