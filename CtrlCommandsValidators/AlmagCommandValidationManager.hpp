#pragma once

#include <string>
#include <vector>
#include <boost/optional.hpp>

#include <Database/Database.hpp>
#include <Utils/TypeAliases.hpp>

class AlmagCommandValidationManager 
{
public:
   AlmagCommandValidationManager(Database& db);

   MaybeStrings perform(const Strings& userInput);

private:
   Database& db_;
};

