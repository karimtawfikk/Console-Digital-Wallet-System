#pragma once
#include<string>
using namespace std;
class Requests
{
public:
	float requestAmount;
	string requester;
	string reciever;
public:
	Requests(float req, string requesterr, string recieve);
	Requests();
	~Requests(void);
};
