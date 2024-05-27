#include "Transactions.h"
#include <iostream>

Transactions::Transactions()
{ }
Transactions::Transactions(string send, string recieve, float am, datee d, timee t)
{
    sender = send;
    reciever = recieve;
    amount = am;
    date = d;
    time = t;
}
void Transactions::CashItTransactions(stack <Transactions> cashItTransactions)
{
    cout << "\nCashIt transactions:" << endl << endl;
    while (!cashItTransactions.empty())
    {
        cout << "[" << "From: " << cashItTransactions.top().sender << ", To: " << cashItTransactions.top().reciever
            << ", Amount: " << cashItTransactions.top().amount << ", Date: " << cashItTransactions.top().date.day << "-" <<
            cashItTransactions.top().date.month << "-" << cashItTransactions.top().date.year << ", Time: "
            << cashItTransactions.top().time.hours << ":" << cashItTransactions.top().time.minutes << "]\n\n";
        cashItTransactions.pop();
    }
}
Transactions::~Transactions(void)
{
}
