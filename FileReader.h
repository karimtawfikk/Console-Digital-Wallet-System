#pragma once
#include"Admin.h"
#include <string>
#include <fstream>
#include <sstream>
#include<iostream>
class FileReader
{
public:
	static void readUserDataFromFile(unordered_map<string, User>& users);
	static void readAdminDataFromFile(unordered_map<string, Admin>& admins);
	static void readTransactionDataFromFile(stack<Transactions>& transactions);
	static datee parseDate(const string& dateStr);
	static timee parseTime(const string& timeStr);
};