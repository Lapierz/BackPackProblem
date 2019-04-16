// Plik : CCommand.h

#pragma once
#ifndef CCommand_h
#define CCommand_h

#include <iostream>
#include <string>
#include <vector>
#include "CCONST.h"

using namespace std;

class CCommand 
{
public:
	virtual void vRunCommand();
};

#endif // CCommand_h
