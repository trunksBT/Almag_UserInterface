#pragma once

#include <string>
#include <memory>
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

using ICmdValidationManagerPtr = std::shared_ptr<ICmdValidationManager>;
