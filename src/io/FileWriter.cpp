#include "FileWriter.h"
#include <fstream>
#include <sstream>
#include<iostream>
using namespace std;
const string userFiles = "Users.txt";
const string adminFiles = "Admins.txt";
const string allTransactionFiles = "AllTransactions.txt";


void FileWriter::writeUsersDataToFiles(unordered_map<string, User> users)
{
    ofstream outputFile(userFiles, ios::out | ios::trunc);


    if (!outputFile.is_open()) {
        cerr << "Error: Unable to open file for writing!" << endl;
        return;
    }
    size_t count = users.size();
    count--;

    for (const auto& pair : users)
    {
        const User& user = pair.second;

        outputFile << user.username << "," << user.password << "," << user.nationalId << ","
            << user.balance << "," << (user.suspended ? "True" : "False") << ","
            << (user.authorized ? "True" : "False") << ",";


        auto it = user.transactions.begin();
        for (int i = 0; i < user.transactions.size(); i++, ++it)
        {
            if (i == user.transactions.size() - 1)
            {
                outputFile << it->sender << ":" << it->reciever << ":" << it->amount
                    << ":" << it->date.day << "-" << it->date.month << "-" << it->date.year
                    << ":" << it->time.hours << "-" << it->time.minutes << ",";
                break;
            }
            outputFile << it->sender << ":" << it->reciever << ":" << it->amount
                << ":" << it->date.day << "-" << it->date.month << "-" << it->date.year
                << ":" << it->time.hours << "-" << it->time.minutes << ";";
        }

        for (const Requests& request : user.requests) {
            outputFile << request.requestAmount << ":" << request.requester << ":" << request.reciever << ";";
        }
        // if(users.size()!=count)
        outputFile << endl;
    }
    outputFile.close();
}
void FileWriter::writeAdminDataToFiles(unordered_map<string, Admin> admins)
{
    fstream file(adminFiles, ios::out | ios::trunc);

    if (!file.is_open()) {
        cerr << "Error: Unable to open file for writing!" << endl;
        return;
    }
    for (const auto& admin : admins) {

        file << admin.first << "," << admin.second.password << endl;
    }
    file.close();
}
void FileWriter::writeTransactionDataToFiles(stack<Transactions> cashItTransactionStack)
{
    stack<Transactions> temporary;
    while (!cashItTransactionStack.empty()) {
        temporary.push(cashItTransactionStack.top());
        cashItTransactionStack.pop();
    } //Since top of og stack is recent and we don't want it recent to be top in the files 

    ofstream outputFile(allTransactionFiles, ios::out | ios::trunc);


    if (!outputFile.is_open()) {
        cerr << "Error: Unable to open file for writing!" << endl;
        return;
    }

    // Iterate over each transaction in the vector
    while (!temporary.empty())
    {
        Transactions transaction = temporary.top();
        outputFile << transaction.sender << "," << transaction.reciever << ","
            << transaction.amount << ","
            << transaction.date.day << "-" << transaction.date.month << "-" << transaction.date.year << ","
            << transaction.time.hours << "-" << transaction.time.minutes << endl;
        temporary.pop();
    }
    outputFile.close();
}
