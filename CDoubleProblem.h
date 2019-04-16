#pragma once
#ifndef CDoubleProblem_h
#define CDoubleProblem_h

#include "CCommand.h"
#include "CCONST.h"

class CDoubleProblem : public CCommand
{
public:
	CDoubleProblem();
	~CDoubleProblem();
	void vRunCommand();
};

#endif // !CDoubleProblem_h