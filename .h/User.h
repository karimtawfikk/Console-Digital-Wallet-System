#pragma once
#include<list>
#include<unordered_map>
#include<queue>
#include"Transactions.h"
#include"Requests.h"
#include"Encryptions.h"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <conio.h>
#include<windows.h>
using namespace std;
class User
{
public:
	string username, password;
	long long nationalId;
	float balance;
	bool suspended;
	bool authorized;
	list <Transactions> transactions;
	vector <Requests> requests;
	static queue<User> unAuthorizedUsers;
public:
	User();
	User(string uname, string pass, long long id, float bal, bool sus, bool auth, list<Transactions> trans, vector<Requests> req);
	void sendMoney(unordered_map<string, User>& users, string username, stack<Transactions>& cashItTransactions);
	void requestMoney(unordered_map<string, User>& users, string username);
	void editInfo(unordered_map<string, User>& users, string& u);
	void viewTransactionHistory(unordered_map<string, User>& users, string username);
	bool performOperations(unordered_map<string, User>& users, string& username, stack<Transactions>& cashItTransactions);
	void viewRequests(unordered_map<string, User>& users, string username, stack<Transactions>& cashItTransactions);
	static void signUp(unordered_map<string, User>& users, string userNAME, string passWORD);
	void calculateCurrentDate();
	~User(void);
};