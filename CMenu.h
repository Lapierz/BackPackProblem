//Plik : CMenu.h

#pragma once
#ifndef CMenu_h
#define Cmenu_h

#include "CMenuItem.h"
#include "CMenuCommand.h"
#include "CCONST.h"

class CMenu : public virtual CMenuItem
{
public:
	~CMenu();
	CMenu();
	CMenu(string sName, string sCommand);
	string sRun();
	void vInitialize();
	void vAddCommand(string sName, string sCommand, CCommand *piCommand);
	void vAddMenu(string sName, string sCommand);
	virtual string sGetCommand();
	virtual string sGetName();
	virtual void vDeleteAll();
private:
	vector <CMenuItem*> v_piitems;
	void vPrint();
};
#endif