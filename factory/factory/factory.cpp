// factory.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <windows.h>
#include <string>

using namespace std;


class AbstractBackground
{
public:
	virtual void message(HANDLE hConsole) = 0;
};

class LightBackground : public AbstractBackground
{
public:
	LightBackground(HANDLE hConsole)
	{
		SetConsoleTextAttribute(hConsole, 240);
		cout << "Making the background light" << endl;
	}

	virtual void message(HANDLE hConsole)
	{
	}
};

class DarkBackground : public AbstractBackground
{
public:
	DarkBackground(HANDLE hConsole)
	{
		SetConsoleTextAttribute(hConsole, 15);
		cout << "Making the background Dark" << endl;
	}

	virtual void message(HANDLE hConsole)
	{
	}
};

class AbstractText
{
public:
	virtual void message(HANDLE hConsole) = 0;
};

class LightText : public AbstractText
{
public:
	LightText(HANDLE hConsole)
	{
		SetConsoleTextAttribute(hConsole, 15);
		cout << "Making the text light" << endl;
	}

	virtual void message(HANDLE hConsole)
	{
	}
};

class DarkText : public AbstractText
{
public:
	DarkText(HANDLE hConsole)
	{
		SetConsoleTextAttribute(hConsole, 240);
		cout << "Making the text dark" << endl;
	}

	virtual void message(HANDLE hConsole)
	{
	}
};

class AbstractFactory
{
public:
	virtual AbstractBackground* setBackground(HANDLE hConsole) = 0;
	virtual AbstractText* getDefaultText(HANDLE hConsole) = 0;
};

class LightFactory : public AbstractFactory
{
public:
	virtual AbstractBackground* setBackground(HANDLE hConsole)	override
	{
		return new LightBackground(hConsole);
	}
	virtual AbstractText* getDefaultText(HANDLE hConsole)	override
	{
		return new DarkText(hConsole);
	}
};

class DarkFactory : public AbstractFactory
{
public:
	virtual AbstractBackground* setBackground(HANDLE hConsole)	 override
	{
		return new DarkBackground(hConsole);
	}
	AbstractText* getDefaultText(HANDLE hConsole)	override
	{
		return new LightText(hConsole);
	}
};


int main()
{
	// Configure console variables and colours
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 30);

	AbstractFactory* app = nullptr;
	int choice;

	cout << "Select a theme: " << endl;
	cout << "1: Light" << endl;
	cout << "2: Dark" << endl;
	cout << "Selection: ";
	cin >> choice;
	cout << endl;

	// Initiate the correct factory based on user input
	switch (choice)
	{
	case 1:
		app = new LightFactory;
		break;
	case 2:
		app = new DarkFactory;
		break;
	default:
		cout << "Invalid Selection" << endl;
		app = NULL;
		break;
	}

	// Get the correct objects based on factory selected
	if (app != NULL)
	{
		AbstractBackground* appBkgd = app->setBackground(hConsole);
		AbstractText *appDefaultText = app->getDefaultText(hConsole);

		appDefaultText->message(hConsole);
	}

	cout << endl;
	system("pause");
}
