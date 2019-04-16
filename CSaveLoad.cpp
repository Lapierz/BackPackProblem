#include "pch.h"
#include "CSaveLoad.h"

void CSaveLoad::vSave(CMenuItem* pi_parent)
{
	ofstream save(S_CSAVELOAD_DANE_TXT);
	string s_acc;
	save << pi_parent->vSave(s_acc);
	save.close();
}

void  CSaveLoad::vLoad() {
	ifstream load(S_CSAVELOAD_DANE_TXT);
	string s_acc;
	bool b_correct=false;
	if (load)
	{
		getline(load, s_acc);
	}
	else {
		cout << S_CSAVELOAD_DATA_EXCEPTION << endl;
	}
	load.close();
	b_correct = bCorrect(s_acc);
	if (b_correct)
	{
		vCreateMenu(s_acc);
	}
	else
	{
		cout << S_CSAVELOAD_BAD_STRING << endl;
	}
}

CMenu* CSaveLoad::cMenu(string& s_data, int& i, CMenuItem &c_item)
{
	i += 2;
	string s_menu_name = S_CSAVELOAD_NULL;
	while (s_data[i] != S_CSAVELOAD_CORRECT_APOSTROPHE_RIGHT)
	{
		s_menu_name += s_data[i];
		i++;
	}
	i += 3;
	string s_menu_command = S_CSAVELOAD_NULL;
	while (s_data[i] != S_CSAVELOAD_CORRECT_APOSTROPHE_RIGHT)
	{
		s_menu_command += s_data[i];
		i++;
	}
	i += 2;
	CMenu *menu = new CMenu(s_menu_name, s_menu_command, S_WRONG_COMMAND , &c_item);
	while (s_data[i] != S_CSAVELOAD_CORRECT_PALE_RIGHT_OPEN)
	{
		if (s_data[i] == S_CSAVELOAD_CORRECT_PALE_LEFT_CLOSE)
		{
			menu->vAddCMenuItem(*cMenuCommand(s_data, i, *menu));
			i += 2;
		}
		else if (s_data[i] == S_CSAVELOAD_CORRECT_PALE_LEFT_OPEN)
		{
			menu->vAddCMenuItem(*cMenu(s_data, i, *menu));
		}
		else if (s_data[i] == S_CSAVELOAD_CORRECT_COMMA)
		{
			i++;
		}
	}
	i++;
	return menu;
}

void CSaveLoad::vCreateMenu(string& s_data)
{
	int i = 2;
	//string s_droga_null = S_CSAVELOAD_NULL;
	string s_menu_name = S_CSAVELOAD_NULL;
	while (s_data[i] != S_CSAVELOAD_CORRECT_APOSTROPHE_RIGHT)
	{
		s_menu_name += s_data[i];
		i++;
	}
	i += 3;
	string s_menu_command = S_CSAVELOAD_NULL;
	while (s_data[i] != S_CSAVELOAD_CORRECT_APOSTROPHE_RIGHT)
	{
		s_menu_command += s_data[i];
		i++;
	}
	i += 2;
	CMenu *start = new CMenu();
	while (s_data[i] != S_CSAVELOAD_CORRECT_PALE_RIGHT_OPEN)
	{
		if (s_data[i] == S_CSAVELOAD_CORRECT_PALE_LEFT_CLOSE)
		{
			start->vAddCMenuItem(*cMenuCommand(s_data, i, *start));
			i += 2;
		}
		else if (s_data[i] == S_CSAVELOAD_CORRECT_PALE_LEFT_OPEN)
		{
			start->vAddCMenuItem(*cMenu(s_data, i, *start));
		}
		else if (s_data[i] == S_CSAVELOAD_CORRECT_COMMA)
		{
			i++;
		}
	}
	start->sRun();
	delete start;
}

CMenuCommand* CSaveLoad::cMenuCommand(string& s_data, int& i, CMenuItem &c_item)
{
	i += 2;
	string s_menucommand_name = S_CSAVELOAD_NULL;
	while (s_data[i] != S_CSAVELOAD_CORRECT_APOSTROPHE_RIGHT)
	{
		s_menucommand_name += s_data[i];
		i++;
	}
	i += 3;
	string s_menucommand_command = S_CSAVELOAD_NULL;
	while (s_data[i] != S_CSAVELOAD_CORRECT_APOSTROPHE_RIGHT)
	{
		s_menucommand_command += s_data[i];
		i++;
	}
	i += 3;
	string s_menucommand_help = S_CSAVELOAD_NULL;
	while (s_data[i] != S_CSAVELOAD_CORRECT_APOSTROPHE_RIGHT)
	{
		s_menucommand_help += s_data[i];
		i++;
	}
	CMenuCommand *menu = new CMenuCommand(s_menucommand_name, s_menucommand_command, nullptr, s_menucommand_help);
	return menu;
}

bool CSaveLoad::bCorrect(string s_data) {
	int i = 0;
	bool correct = true;
	if (i < (int)s_data.length() && s_data[i] == S_CSAVELOAD_CORRECT_PALE_LEFT_OPEN)
	{
		correct = bMenuCorrect(s_data, i, correct);
	}
	else
	{
		correct = false;
		cout << S_CSAVELOAD_INDEX << i << S_CSAVELOAD_ERROR_6 << endl;
	}
	return correct;
}

bool CSaveLoad::bMenuCommandCorrect(string s_data, int& i, bool correct) {
	i++;
	if (i < (int)s_data.length() && s_data[i] == S_CSAVELOAD_CORRECT_APOSTROPHE_LEFT)
	{
		i++;
		while (i < (int)s_data.length() && s_data[i] != S_CSAVELOAD_CORRECT_APOSTROPHE_RIGHT && correct)
		{
			if (i >= (int)s_data.length() || s_data[i] == S_CSAVELOAD_CORRECT_APOSTROPHE_LEFT || s_data[i] == S_CSAVELOAD_CORRECT_COMMA || s_data[i] == S_CSAVELOAD_CORRECT_SEMICOLON || s_data[i] == S_CSAVELOAD_CORRECT_PALE_LEFT_OPEN || s_data[i] == S_CSAVELOAD_CORRECT_PALE_RIGHT_OPEN || s_data[i] == S_CSAVELOAD_CORRECT_PALE_LEFT_CLOSE || s_data[i] == S_CSAVELOAD_CORRECT_PALE_RIGHT_CLOSE) correct = false;
			else i++;
		}
		if (i < (int)s_data.length() && correct)
		{
			i++;
			if (i < (int)s_data.length() && s_data[i] == S_CSAVELOAD_CORRECT_COMMA)
			{
				i++;
				if (i < (int)s_data.length() && s_data[i] == S_CSAVELOAD_CORRECT_APOSTROPHE_LEFT)
				{
					i++;
					while (i < (int)s_data.length() && s_data[i] != S_CSAVELOAD_CORRECT_APOSTROPHE_RIGHT && correct)
					{
						if (i >= (int)s_data.length() || s_data[i] == S_CSAVELOAD_CORRECT_APOSTROPHE_LEFT || s_data[i] == S_CSAVELOAD_CORRECT_COMMA || s_data[i] == S_CSAVELOAD_CORRECT_SEMICOLON || s_data[i] == S_CSAVELOAD_CORRECT_PALE_LEFT_OPEN || s_data[i] == S_CSAVELOAD_CORRECT_PALE_RIGHT_OPEN || s_data[i] == S_CSAVELOAD_CORRECT_PALE_LEFT_CLOSE || s_data[i] == S_CSAVELOAD_CORRECT_PALE_RIGHT_CLOSE) correct = false;
						else i++;
					}
					if (i < (int)s_data.length() && correct)
					{
						i++;
						if (i < (int)s_data.length() && s_data[i] == S_CSAVELOAD_CORRECT_COMMA)
						{
							i++;
							if (i < (int)s_data.length() && s_data[i] == S_CSAVELOAD_CORRECT_APOSTROPHE_LEFT)
							{
								i++;
								while (i < (int)s_data.length() && s_data[i] != S_CSAVELOAD_CORRECT_APOSTROPHE_RIGHT && correct)
								{
									if (i >= (int)s_data.length() || s_data[i] == S_CSAVELOAD_CORRECT_APOSTROPHE_LEFT || s_data[i] == S_CSAVELOAD_CORRECT_COMMA || s_data[i] == S_CSAVELOAD_CORRECT_SEMICOLON || s_data[i] == S_CSAVELOAD_CORRECT_PALE_LEFT_OPEN || s_data[i] == S_CSAVELOAD_CORRECT_PALE_RIGHT_OPEN || s_data[i] == S_CSAVELOAD_CORRECT_PALE_LEFT_CLOSE || s_data[i] == S_CSAVELOAD_CORRECT_PALE_RIGHT_CLOSE) correct = false;
									else i++;
								}
								if (i < (int)s_data.length() && correct)
								{
									i++;
									if (i < (int)s_data.length() && s_data[i] == S_CSAVELOAD_CORRECT_PALE_RIGHT_CLOSE)
									{
										correct = true;
										i++;
										if (i < (int)s_data.length())
										{
											if (s_data[i] == S_CSAVELOAD_CORRECT_COMMA)
											{
												correct = true;
											}
											else if (s_data[i] == S_CSAVELOAD_CORRECT_PALE_RIGHT_OPEN)
											{
												i--;
												correct = true;
											}
											else
											{
												correct = false;
												cout << S_CSAVELOAD_INDEX << i << S_CSAVELOAD_ERROR_10 << endl;
											}
										}
										else
										{
											correct = false;
											cout << S_CSAVELOAD_INDEX << i << S_CSAVELOAD_ERROR_10 << endl;
										}
									}
									else
									{
										correct = false;
										cout << S_CSAVELOAD_INDEX << i << S_CSAVELOAD_ERROR_7 << endl;
									}
								}
								else
								{
									correct = false;
									cout << S_CSAVELOAD_INDEX << i << S_CSAVELOAD_ERROR_8 << endl;
								}
							}
							else
							{
								correct = false;
								cout << S_CSAVELOAD_INDEX << i << S_CSAVELOAD_ERROR_9 << endl;
							}
						}
						else
						{
							correct = false;
							cout << S_CSAVELOAD_INDEX << i << S_CSAVELOAD_ERROR_5 << endl;
						}
					}
					else
					{
						correct = false;
						cout << S_CSAVELOAD_INDEX << i << S_CSAVELOAD_ERROR_8 << endl;
					}
				}
				else
				{
					correct = false;
					cout << S_CSAVELOAD_INDEX << i << S_CSAVELOAD_ERROR_9 << endl;
				}
			}
			else
			{
				correct = false;
				cout << S_CSAVELOAD_INDEX << i << S_CSAVELOAD_ERROR_5 << endl;
			}
		}
		else
		{
			correct = false;
			cout << S_CSAVELOAD_INDEX << i << S_CSAVELOAD_ERROR_8 << endl;
		}
	}
	else
	{
		correct = false;
		cout << S_CSAVELOAD_INDEX << i << S_CSAVELOAD_ERROR_9 << endl;
	}
	return correct;
}

bool CSaveLoad::bMenuCorrect(string s_data, int &i, bool correct) {
	i++;
	if (i < (int)s_data.length() && s_data[i] == S_CSAVELOAD_CORRECT_APOSTROPHE_LEFT)
	{
		i++;
		while (i < (int)s_data.length() && s_data[i] != S_CSAVELOAD_CORRECT_APOSTROPHE_RIGHT && correct)
		{
			if (i >= (int)s_data.length() || s_data[i] == S_CSAVELOAD_CORRECT_APOSTROPHE_LEFT || s_data[i] == S_CSAVELOAD_CORRECT_COMMA || s_data[i] == S_CSAVELOAD_CORRECT_SEMICOLON || s_data[i] == S_CSAVELOAD_CORRECT_PALE_LEFT_OPEN || s_data[i] == S_CSAVELOAD_CORRECT_PALE_RIGHT_OPEN || s_data[i] == S_CSAVELOAD_CORRECT_PALE_LEFT_CLOSE || s_data[i] == S_CSAVELOAD_CORRECT_PALE_RIGHT_CLOSE) correct = false;
			else i++;
		}
		if (i < (int)s_data.length() && correct)
		{
			i++;
			if (i < (int)s_data.length() && s_data[i] == S_CSAVELOAD_CORRECT_COMMA)
			{
				i++;
				if (i < (int)s_data.length() && s_data[i] == S_CSAVELOAD_CORRECT_APOSTROPHE_LEFT)
				{
					i++;
					while (i < (int)s_data.length() && s_data[i] != S_CSAVELOAD_CORRECT_APOSTROPHE_RIGHT && correct)
					{
						if (i >= (int)s_data.length() || s_data[i] == S_CSAVELOAD_CORRECT_APOSTROPHE_LEFT || s_data[i] == S_CSAVELOAD_CORRECT_COMMA || s_data[i] == S_CSAVELOAD_CORRECT_SEMICOLON || s_data[i] == S_CSAVELOAD_CORRECT_PALE_LEFT_OPEN || s_data[i] == S_CSAVELOAD_CORRECT_PALE_RIGHT_OPEN || s_data[i] == S_CSAVELOAD_CORRECT_PALE_LEFT_CLOSE || s_data[i] == S_CSAVELOAD_CORRECT_PALE_RIGHT_CLOSE) correct = false;
						else i++;
					}
					if (i < (int)s_data.length() && correct)
					{
						i++;
						if (i < (int)s_data.length() && s_data[i] == S_CSAVELOAD_CORRECT_SEMICOLON)
						{
							i++;
							if (i < (int)s_data.length())
							{
								if (s_data[i] == S_CSAVELOAD_CORRECT_COMMA)
								{
									correct = false;
									cout << S_CSAVELOAD_INDEX << i << S_CSAVELOAD_ERROR_1 << endl;
								}
								else i--;
							}
							else
							{
								correct = false;
								cout << S_CSAVELOAD_INDEX << i << S_CSAVELOAD_ERROR_1 << endl;
							}
							while (correct&&s_data[i] != S_CSAVELOAD_CORRECT_PALE_RIGHT_OPEN)
							{
								i++;
								if (i < (int)s_data.length())
								{
									if (s_data[i] == S_CSAVELOAD_CORRECT_PALE_LEFT_OPEN)
									{
										correct = bMenuCorrect(s_data, i, correct);
										if (correct)
										{
											i++;
											if (i >= (int)s_data.length())
											{
												correct = false;
												cout << S_CSAVELOAD_INDEX << i << S_CSAVELOAD_ERROR_2 << endl;
											}
										}
									}
									else if (s_data[i] == S_CSAVELOAD_CORRECT_PALE_LEFT_CLOSE)
									{
										correct = bMenuCommandCorrect(s_data, i, correct);

									}
									else if (s_data[i] == S_CSAVELOAD_CORRECT_COMMA)
									{
										correct = true;
									}
									else if (s_data[i] == S_CSAVELOAD_CORRECT_PALE_RIGHT_OPEN)
									{
										correct = true;
									}
									else
									{
										correct = false;
										cout << S_CSAVELOAD_INDEX << i << S_CSAVELOAD_ERROR_4 << endl;
									}
								}
								else
								{
									correct = false;
									cout << S_CSAVELOAD_INDEX << i << S_CSAVELOAD_ERROR_2 << endl;
								}
							}
						}
						else
						{
							correct = false;
							cout << S_CSAVELOAD_INDEX << i << S_CSAVELOAD_ERROR_3 << endl;
						}
					}
					else
					{
						correct = false;
						cout << S_CSAVELOAD_INDEX << i << S_CSAVELOAD_ERROR_8 << endl;
					}
				}
				else
				{
					correct = false;
					cout << S_CSAVELOAD_INDEX << i << S_CSAVELOAD_ERROR_9 << endl;
				}
			}
			else
			{
				correct = false;
				cout << S_CSAVELOAD_INDEX << i << S_CSAVELOAD_ERROR_5 << endl;
			}
		}
		else
		{
			correct = false;
			cout << S_CSAVELOAD_INDEX << i << S_CSAVELOAD_ERROR_8 << endl;
		}
	}
	else
	{
		correct = false;
		cout << S_CSAVELOAD_INDEX << i << S_CSAVELOAD_ERROR_9 << endl;
	}
	return correct;
}
