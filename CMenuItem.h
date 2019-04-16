//Plik: CMenuItem.h

#pragma once
#ifndef CMenuItem_h
#define CMenuItem_h

#include <string>
#include <vector>
using namespace std;

class CMenuItem
{
protected:
	string s_command;
	string s_name;
public:
	virtual ~CMenuItem() { }
	virtual string sRun() = 0;
	virtual string sGetCommand() = 0;
	virtual string sGetName() = 0;
};
#endif // !CMenuItem_h
