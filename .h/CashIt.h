#pragma once
#include"User.h"
#include<iostream>
#include"Admin.h"
#include<conio.h>
#include"FileReader.h"
#include"FileWriter.h"
using namespace std;


class CashIt
{
public:
	static void Start();
	static int registrationChoice();
	static void Identification();
	static void readFromFiles();
	static void writeToFiles();
};
