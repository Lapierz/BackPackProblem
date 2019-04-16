// Plik: CMenuTabCommand.cpp 

#include "pch.h"
#include "CMenuTabCommand.h"

string CMenuTabCommand::sUserInput() {
	string s_input;
	cin >> s_input;
	cout << endl;
	if (cin) {
		return s_input;
	}//if (cin) 
	else {
		cout << S_ERROR << endl;
		return S_ERROR;
	}//else
}//string CMenuTabCommand::sUserInput()  

int CMenuTabCommand::iUserInput(int iLeft, int iRight) {
	int i_input;
	cin >> i_input;
	cout << endl;
	if (cin && iLeft <= i_input && i_input <= iRight) {
		return i_input;
	}//if (cin && iLeft <= i_input && i_input <= iRight) 
	else {
		cout << "Wybierz cyfre od " + to_string(iLeft) + " do " + to_string(iRight) + " :)" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return iUserInput(iLeft, iRight);
	}//else
}//int CMenuTabCommand::iUserInput(int iLeft, int iRight)