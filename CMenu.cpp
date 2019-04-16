
#include "pch.h"
#include "CMenu.h"
#include "CBoolProblem.h"
#include "CIntProblem.h"
#include "CDoubleProblem.h"

CMenu::CMenu(string sName, string sCommand) 
{
	s_command = sCommand;
	s_name = sName;
}  

CMenu::CMenu() 
{
	s_command = S_MENU_COMMAND;
	s_name = S_MENU;
}

CMenu::~CMenu() 
{
	vDeleteAll();
} 

void CMenu::vInitialize() 
{
	CBoolProblem* pi_bool = new CBoolProblem();
	CIntProblem* pi_int = new CIntProblem();
	CDoubleProblem* pi_double = new CDoubleProblem();

	vAddCommand(S_BOOL, S_BOOL_COMMAND, pi_bool);
	vAddCommand(S_INT, S_INT_COMMAND, pi_int);
	vAddCommand(S_DOUBLE, S_DOUBLE_COMMAND, pi_double);
}

void CMenu::vAddMenu(string sName, string sCommand) 
{
	bool b_check = true;
	for (int i = 0; i < (int)v_piitems.size(); i++) 
	{
		CMenuItem *pi_temp = v_piitems.at(i);
		if (pi_temp->sGetCommand() == sCommand || pi_temp->sGetName() == sName)
		{
			b_check = false;
		}
	}
	if (b_check) 
	{
		CMenuItem *pi_temp = new  CMenu(sName, sCommand);
		v_piitems.push_back(pi_temp);
	}
	else 
	{
		cout << S_ERROR << endl;
	} 
}

void CMenu::vAddCommand(string sName, string sCommand, CCommand *piCommand) 
{
	bool b_check = true;
	for (int i = 0; i < (int)v_piitems.size(); i++) 
	{
		CMenuItem *pi_temp = v_piitems.at(i);
		if (pi_temp->sGetCommand() == sCommand || pi_temp->sGetName() == sName) 
		{
			b_check = false;
		} 
	}
	if (b_check)
	{
		CMenuItem *pi_temp = new  CMenuCommand(sName, sCommand, piCommand);
		v_piitems.push_back(pi_temp);
	}
	else 
	{
		cout << S_ERROR << endl;
	}
}


void CMenu::vDeleteAll() 
{
	for (int i = 0; i < v_piitems.size(); i++) 
	{
		CMenuItem* pi_item= v_piitems.at(i);
		delete pi_item;
	}
	cout << S_DELETE_ALL + this->sGetName() << endl;
}

string CMenu::sGetCommand() 
{
	return s_command;
}

string CMenu::sGetName()
{
	return s_name;
}

void CMenu::vPrint() 
{
	cout << endl << s_name + S_COLON + s_command << endl;
	for (int i = 0; i < (int)v_piitems.size(); i++) 
	{
		cout << to_string(i) + S_SPACE + v_piitems.at(i)->sGetName() 
			+ S_OPEN_BRACKET + v_piitems.at(i)->sGetCommand() 
			+ S_CLOSED_BRACKET << endl;
	}
	cout << endl;
}

string CMenu::sRun()
{
	string s_string;
	bool b_com = false;
	vPrint();
	getline(cin, s_string);
	while (s_string != S_BACK) 
	{
		b_com = false;
		for (int i = 0; i < (int)v_piitems.size(); i++) 
		{
			if (s_string == v_piitems.at(i)->sGetCommand()) 
			{
				string s_string_return = v_piitems.at(i)->sRun();
				vPrint();
				b_com = true;
			}
		} 
		if (!b_com) {
			cout << S_WRONG_COMM << endl << endl;;
		}
		getline(cin, s_string);
	}
	return S_QU;
}

