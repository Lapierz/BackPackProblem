#pragma once
#ifndef CSaveLoad_h
#define CSaveLoad_h

#include <string>
#include <iostream>
#include <fstream>
#include "CMenuItem.h"
#include "CMenu.h"

const string S_WRONG_COMMAND = "Pod_Menu";
#define S_CSAVELOAD_DANE_TXT "dane.txt"
#define S_CSAVELOAD_DATA_EXCEPTION "BLAD: nie mozna otworzyc pliku do odczytu."
#define S_CSAVELOAD_BAD_STRING "Bledny string!"
#define S_CSAVELOAD_INTERFACE_BACK "back"
#define S_CSAVELOAD_INDEX "indeks: "
#define S_CSAVELOAD_ERROR_1 "   oczekiwano: '(' lub '[' lub ')'"
#define S_CSAVELOAD_ERROR_2 "   oczekiwano: ')'"
#define S_CSAVELOAD_ERROR_3 "   oczekiwano: ';'"
#define S_CSAVELOAD_ERROR_4 "   oczekiwano: '(' lub '[' lub ','"
#define S_CSAVELOAD_ERROR_5 "   oczekiwano: ','"
#define S_CSAVELOAD_ERROR_6 "   oczekiwano: '('"
#define S_CSAVELOAD_ERROR_7 "   oczekiwano: ']'"
#define S_CSAVELOAD_ERROR_8 "   oczekiwano: '’'"
#define S_CSAVELOAD_ERROR_9 "   oczekiwano: '‘'"
#define S_CSAVELOAD_ERROR_10 "   oczekiwano: ',' lub ')'"
#define S_CSAVELOAD_NULL ""
#define S_CSAVELOAD_CORRECT_PALE_RIGHT_OPEN ')'
#define S_CSAVELOAD_CORRECT_PALE_LEFT_OPEN '('
#define S_CSAVELOAD_CORRECT_PALE_RIGHT_CLOSE ']'
#define S_CSAVELOAD_CORRECT_PALE_LEFT_CLOSE '['
#define S_CSAVELOAD_CORRECT_COMMA ','
#define S_CSAVELOAD_CORRECT_SEMICOLON ';'
#define S_CSAVELOAD_CORRECT_APOSTROPHE_RIGHT '’'
#define S_CSAVELOAD_CORRECT_APOSTROPHE_LEFT '‘'

class CSaveLoad
{
public:
	CSaveLoad() {}
	~CSaveLoad() {}
	void vSave(CMenuItem* parent);
	void vLoad();
private:
	bool bCorrect(string s_acc);
	bool bMenuCorrect(string data, int& i, bool correct);
	bool bMenuCommandCorrect(string data, int& i, bool correct);
	void vCreateMenu(string& data);
	CMenuCommand* cMenuCommand(string& data, int& i, CMenuItem &c_item);
	CMenu* cMenu(string& data, int& i, CMenuItem &c_item);
};

#endif // !CSaveLoad_h
