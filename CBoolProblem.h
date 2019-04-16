#pragma once
#ifndef CBoolProblem_h
#define CBoolProblem_h

#include "CCommand.h"
#include "CCONST.h"

class CBoolProblem : public CCommand
{
public:
	CBoolProblem();
	~CBoolProblem();
	void vRunCommand();
};

#endif // !CBoolProblem_h
