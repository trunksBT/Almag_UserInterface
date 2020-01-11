#include <UserInterface/Database/CDatabaseCommand.hpp>
#include <boost/algorithm/string.hpp>
#include <UserInterface/Database/Brokers/Broker_IOPaths.hpp>
#include <Utils/Utils.hpp>

using namespace defaultVals;
using namespace dbObjects::OT;

CDatabaseCommand::CDatabaseCommand(Database& db, const Strings& inArgs)
{
   if (boost::contains(inArgs[idx::OBJECT_NAME], IO_PATHS))
      command_ = std::make_unique<Broker_IOPaths>(db, inArgs);
}

bool CDatabaseCommand::runCommand()
{
	if (not command_)
		LOG(warning) << "Empty command";
	else
		command_->runCommand();

	return true;
}

