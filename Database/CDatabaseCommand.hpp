#pragma once

#include <memory>
#include <Database/Database.hpp>
#include <UserInterface/CCommand.hpp>
#include <Utils/TypeAliases.hpp>

class CDatabaseCommand : public CCommand 
{
public:
	CDatabaseCommand(Database& db, const Strings& inArgs);
  
	virtual ~CDatabaseCommand() = default;

	bool runCommand() final override;

private:
   std::unique_ptr<CCommand> command_;
};

