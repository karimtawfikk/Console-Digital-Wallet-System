#pragma once
#include"Admin.h"
#include <fstream>
#include <sstream>
#include<iostream>
#include <string>
class FileWriter
{
public:
	static void writeUsersDataToFiles(unordered_map<string, User> users);
	static void writeAdminDataToFiles(unordered_map<string, Admin> admins);
	static void writeTransactionDataToFiles(stack<Transactions> cashItTransactionStack);

};
