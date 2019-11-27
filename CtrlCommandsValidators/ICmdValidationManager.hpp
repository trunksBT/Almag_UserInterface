#pragma once

#include <string>
#include <Database/Database.hpp>
#include <Utils/TypeAliases.hpp>

class ICmdValidationManager
{
public:
   ICmdValidationManager(Database& db) : db_{db} {};
   virtual ~ICmdValidationManager() = default;

   virtual MaybeStrings perform(const Strings& userInput) = 0;
protected:
   Database& db_;
};
