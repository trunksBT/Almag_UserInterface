#include "UserInterface/Database/Brokers/Broker_IOPaths.hpp"
#include <string>

#include <Database/Objects/IOPaths.hpp>
#include <Utils/Utils.hpp>

using namespace defaultVals;

// validation
// conversion
// hardcodes
// idxEs

namespace
{
   const std::string PUT = "put";
   const std::string GET = "get";
   constexpr int idxOfDbCommand = 0;
   constexpr int idxOfUK = 1;
   constexpr int idxOfMemberName = 2;
   constexpr int idxOfMemberValue = 3;
}

Broker_IOPaths::Broker_IOPaths(Database& db, const Strings& inArgs)
   : db_(db)
   , inArgs_(inArgs)
{
   LOG(debug) << dbObjects::OT::IO_PATHS;
}

bool Broker_IOPaths::runCommand()
{
   if (PUT == inArgs_[idxOfDbCommand])
   {
      return handlePut(inArgs_);
   }
   else if (GET == inArgs_[idxOfDbCommand])
   {
      return handleGet(inArgs_);
   }
   return false;
}

bool Broker_IOPaths::handlePut(const Strings& inArgs)
{
   const auto& memberName = inArgs_[idxOfMemberName]; 
   const auto& memberValue = inArgs_[idxOfMemberValue]; 
   const auto objUK = db_.generateUniqueKey(inArgs_[idxOfUK]);
   const auto formerObj = db_.getObj<IOPaths>(objUK);

   IOPaths presentObj = formerObj ? std::move(*formerObj) : IOPaths();

   if (memberName == "bufferToSend")
   {
      presentObj.bufferToSend = memberValue;
      LOG(debug) << objUK << " " << memberName << " changed";
   }
   else
   {
      LOG(debug) << "Not found " << memberName << " for " << objUK;
      LOG(debug) << objUK << " not updated";
      return true;
   }

   db_.updateObj({ objUK, presentObj });
   return true;
}

bool Broker_IOPaths::handleGet(const Strings& inArgs)
{
   const auto& objUK = inArgs_[idxOfUK];

   if (const auto IOPathsObj = db_.getObj<IOPaths>(objUK))
   {
      LOG(debug) << (*IOPathsObj);
   }

   return true;
}

