
#pragma once
#ifndef CMenuCommand_h
#define CMenuCommand_h

#include "CCommand.h"
#include "CMenuItem.h"
#include <iostream>
#include "CCONST.h"

class CMenuCommand : public virtual CMenuItem
{
public:
	CMenuCommand ();
	CMenuCommand(string sName, string sCommand, CCommand *piCommand);
	~CMenuCommand();
	string sRun();
	virtual string sGetCommand();
	virtual string sGetName();
private:
	CCommand* pi_ccommand ;
};
#endif 
