#pragma once
#ifndef CIntProblem_h
#define CIntProblem_h

#include "CCommand.h"
#include "CCONST.h"

class CIntProblem : public CCommand
{
public:
	CIntProblem();
	~CIntProblem();
	void vRunCommand();
};

#endif // !CIntProblem_h