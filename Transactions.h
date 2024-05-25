#pragma once
#include <string>
#include <stack>
#include<vector>
#include <fstream>
#include <sstream>
using namespace std;
struct datee
{

	int month, year, day;
};
struct timee
{
	int hours, minutes;

};
class Transactions
{
public:
	string sender;
	string reciever;
	float amount;
	datee date;
	timee time;
public:
	Transactions();
	Transactions(string send, string recieve, float am, datee d, timee t);
	static void CashItTransactions(stack<Transactions> cashItTransactions);
	~Transactions();
};