#pragma once

#include <string>
#include <Utils/TypeAliases.hpp>
#include "ICmdValidationManager.hpp"

class AlmagCommandValidationManager final : public ICmdValidationManager
{
public:
   explicit AlmagCommandValidationManager(Database& db);
   virtual ~AlmagCommandValidationManager() = default;
   MaybeStrings perform(const Strings& userInput) override;
};
