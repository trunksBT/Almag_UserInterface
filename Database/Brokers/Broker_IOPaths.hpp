#pragma once

#include <Database/Database.hpp>
#include <UserInterface/CCommand.hpp>
#include <Utils/TypeAliases.hpp>

class Broker_IOPaths final : public CCommand
{
public:
   Broker_IOPaths(Database& db, const Strings& inArgs);

   bool runCommand() final override;

private:
   bool handlePut(const Strings& inArgs);
   bool handleGet(const Strings& inArgs);

   Database& db_;
   const Strings& inArgs_;
};

