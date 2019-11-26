#pragma once

class CCommand
{
public:
	virtual bool runCommand() = 0;
	virtual ~CCommand() = default;
};
