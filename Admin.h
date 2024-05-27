#pragma once
#include"User.h"

using namespace std;
class Admin
{
public:
	string username, password;
	
	Admin();
	Admin(string uname, string pass);
	void viewRegUsers(unordered_map<string, User>& users);
	void editAccount(unordered_map<string, User>& users);
	void adjustBalance(unordered_map<string, User>& users);
	bool performOperations(unordered_map<string, User>& users, stack<Transactions>& cashItTransaction);
	~Admin();
};
