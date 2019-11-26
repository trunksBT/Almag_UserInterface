#pragma once

#include <string>
#include <boost/optional.hpp>
#include <Utils/TypeAliases.hpp>

class ICommandValidationStrategy
{
public:
   virtual ~ICommandValidationStrategy() = default;

   MaybeStrings execute(Strings userInput);

protected:
   virtual MaybeStrings validateInputCorrectness(Strings userInput) = 0;
   virtual MaybeStrings modifyIfRequired(Strings validatedUserInput) = 0;
};

