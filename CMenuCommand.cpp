
#include "pch.h"
#include "CMenuCommand.h"

CMenuCommand::CMenuCommand()
{
	s_command = S_DEF_COMMAND;
	s_name = S_DEF_NAME;
	pi_ccommand = nullptr;
}

CMenuCommand::CMenuCommand(string sName, string sCommand,CCommand *ccpi_command) 
{
	s_command = sCommand;
	s_name = sName;
	this->pi_ccommand = ccpi_command;
}

CMenuCommand::~CMenuCommand()
{
	delete pi_ccommand;
} 

string CMenuCommand::sGetCommand()
{
	return s_command;
}

string CMenuCommand::sGetName() 
{
	return s_name;
}

string CMenuCommand::sRun() 
{
	if (!pi_ccommand) 
	{
		cout << S_EMPTY_COMMEND << endl;
		return "";
	}
	else 
	{
		pi_ccommand->vRunCommand();
		return "";
	}
}

