#include "Admin.h"
#include <iostream>
using namespace std;

Admin::Admin()
{

}
Admin::Admin(string uname, string pass)
{
    username = uname;
    password = pass;
}
void Admin::viewRegUsers(unordered_map<string, User>& users)
{
    string type;
    string userType;
    int i = 0;
    cout << "\nAll registered users:";
    for (auto it = users.begin(); it != users.end(); it++, i++)
    {
        if (!it->second.authorized)
        {
            i--;
            continue;
        }
        cout << "\n\n\nUser " << i + 1 << ":" << "\n" << "UserName:" << it->first;
        cout << ", Current Balance:" << it->second.balance << ".";
        if (it->second.transactions.empty())
        {
            cout << "\nNo Transactions.";
        }
        else
        {
            cout << "\nTransaction history:\n";
            for (auto is = it->second.transactions.rbegin(); is != it->second.transactions.rend(); is++)  //it->second.transactions returns a linked list, r is for reversed
            {
                if (is->amount < 0)
                {
                    userType = is->reciever;
                    type = "Sent Money";
                }
                else {
                    userType = is->sender;
                    type = "Received Money";
                }

                cout << "[" << "Second User: " << userType << ", Amount: " << is->amount
                    << ", Date: " << is->date.day << "-" << is->date.month << "-" << is->date.year
                    << ", Time:" << is->time.hours << ":" << is->time.minutes
                    << ", Transaction type:" << type
                    << "]\n";
            }
        }
        cout << endl;
    }
}
void Admin::editAccount(unordered_map<string, User>& users)
{
    bool flag = true;
    char respond;
    char choice;
    char x;
    do {
        cout << "\nPlease enter a number to perform the following functions:" << endl;
        cout << "1. Authorize a user account." << endl;
        cout << "2. Edit an account." << endl;
        cout << "3. Delete an account." << endl;
        cout << "4. Suspend an account." << endl;
        cout << "5. Reactivate a suspended account." << endl;
        cout << "\nEnter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case '1':
        {
          
            if (User::unAuthorizedUsers.size() == 0) cout << "\nNo users to authorize at the moment." << endl;
            else
            {
                cout << "\nChoose wheather you want to authorize those users or not:" << endl;
                for (int i = 0; i < User::unAuthorizedUsers.size(); i++)
                {
                    cout << "\nUser" << ++i << ":\n" << "Username: " << User::unAuthorizedUsers.front().username << "  National ID: " << User::unAuthorizedUsers.front().nationalId << endl;
                    do {
                        cout << "\nPlease enter a number to choose from:" << endl;
                        cout << "1. Authorize the user to use CashIt." << endl;
                        cout << "2. Deny Authorization" << endl << "Choice:";
                        cin >> x;
                        if (x != '1' && x != '2') cout << "Invalid choice\n";
                    } while (x != '1' && x != '2');
                    if (x == '1')
                    {
                        users[User::unAuthorizedUsers.front().username].authorized = true;
                        users[User::unAuthorizedUsers.front().username].suspended = false;
                    }
                    else
                    {
                        users.erase(User::unAuthorizedUsers.front().username);
                    }
                    User::unAuthorizedUsers.pop();
                }
                cout << "\nAll done!";
            }
            break;
        }
        case '2':
        {
            string userNAME;
            char choice;
            int i = 0;
            cout << "CashIt users:\n" << endl;
            for (auto it = users.begin(); it != users.end(); it++)
            {
              if(it->second.authorized)
                cout << ++i << "." << it->first << endl;
            }
            cout << "\nWrite username of user to be edited:\n" << "Username:  "; cin >> userNAME;
            while (true)
            {
                if (users.count(username))
                    cout << "This username already exists. Please try again.\n";
                else
                    break;
            }

            cout << "\nSelect what element of " << userNAME << "'s account to be edited.\n";
            cout << "Press the following:\n";
            cout << "1. Edit Username" << endl;
            cout << "2. Edit Password" << endl;

            cin >> choice;
            string newVal;
            do
            {
                if (choice == '1')
                {
                    do {
                        cout << "\nUsername:";
                        cin >> newVal;
                        if (users.count(newVal))
                            cout << "This user already exists. Please try again.";
                    } while (users.count(newVal));
                   users[userNAME].username = newVal;
                   users[newVal] = users[userNAME];
                   users.erase(userNAME);
                   cout << "\nAll done! Username updated successfully.";
                }
                else if (choice == '2')
                {
                    string password;
                    char c;
                    cout << "Enter a new password for " << userNAME << ": ";
                    password = "";
                    newVal = "";
                    while ((c = _getch()) != '\r')
                    {
                        if (c == '\b')
                        {
                            if (!password.empty())
                            {
                                cout << "\b \b";
                                password.pop_back();
                                newVal.pop_back();
                            }
                        }
                        else {
                            password += c;
                            newVal += c;
                            cout << '*';
                        }
                    }
                    users[userNAME].password = Encryptions::generateEncryption(newVal);
                    cout << "\n\nAll done! Password updated successfully!";
                }
                else cout << "Invalid choice. Please try again." << endl;
            } while (choice != '1' && choice != '2');
            break;
        }
        case '3':
        {

            int i = 0;
            string userNAME;
            cout << "CashIt users:\n" << endl;
            for (auto it = users.begin(); it != users.end(); it++)
            {
                cout << ++i<< "." << it->first << endl;
            }
            cout << "Write username of user to be deleted:\n";
            do
            {
                 cout<<"Username: "; cin >> userNAME;
                if (!users.count(userNAME))
                {
                    cout << "\nThis user doesn't exist. Please try again." << endl;
                }
            } 
            while (!users.count(userNAME));
            users.erase(userNAME);
            cout << "\nAll done! Account deleted successfully.\n";
            break;
        }
        case '4':
        {  
        string userNAME;
        int i = 0;
        cout << "Unsuspended CashIt users:\n" << endl;
        for (auto it = users.begin(); it != users.end(); it++)
        {
            if (!it->second.suspended)
                cout << ++i << "." << it->first << endl;
        }
        cout << "\nWrite username of user to be suspended:\n";
        do
        {
          cout  << "Username: "; cin >> userNAME;
            if (!users.count(userNAME))
            {
                cout << "\nThis user doesn't exist. Please try again." << endl;
            }
        } while (!users.count(userNAME));

        users[userNAME].suspended = true;
        cout << "\nAll done! Account suspended successfully\n";
        break;
        }
        case 5:
        {
            string userNAME;
            int i = 0;
            bool flag = true;
            cout << "\nSuspended CashIt users:" << endl;
            for (auto it = users.begin(); it != users.end(); it++)
            {
                if (it->second.suspended)
                {
                    flag = false;
                    cout << ++i << "." << it->first << endl;
                }
            }
            if (flag) 
                cout << "\nNo suspended users." << endl;
            else
            {
                cout << "\nWrite username of user to be re-activated:\n";
                do
                {
                     cout<< "Username:  "; cin >> userNAME;
                    if (!users.count(userNAME))
                    {
                        cout << "\nThis user doesn't exist. Please try again." << endl;
                    }
                } while (!users.count(userNAME));
                users[userNAME].suspended = false;
                cout << "\nAll done! Account activated successfully.\n";
            }
            break;
        }
        default:
        {
            cout << "Invalid choice" << endl;
            continue;
        }
        }

        cout << endl;
        do {

            cout << "\nDo you want to continue editing on users? (Y/N): ";
            cin >> respond;
            if (respond == 'n' || respond == 'N')
            {
                flag = false;
            }
            if (respond != 'Y' && respond != 'y' && respond != 'n' && respond != 'N') cout << "\nInvalid choice" << endl;
        } while (respond != 'Y' && respond != 'y' && respond != 'n' && respond != 'N');
        system("cls");
    } while (flag);
}
void Admin::adjustBalance(unordered_map<string, User>& users)
{
    string userN;
    float newBalance;
    int i = 0;
    cout << "\nUsers: \n";
    for (auto it = users.begin(); it != users.end(); it++)
        if (it->second.authorized)
            cout << ++i <<"." << it->first << endl;
    do {
        cout << "\nEnter username:";
        cin >> userN;
        if (!users.count(userN))
        {
            cout << "\nThis user doesn't exist. Please try again.";
        }
        else {
            auto is = users.find(userN);
            cout << "The adjusted balance is: ";
            cin >> newBalance;
            is->second.balance = newBalance;
            break;
        }
    } while (!users.count(userN));
    cout << "\nBalance successfully adjusted.\n\n";

}
bool Admin::performOperations(unordered_map<string, User>& users, stack<Transactions>& cashItTransaction) {
    system("cls");
    cout << "\n\nWelcome " << username << "!" << endl;
    char answer;
    char choice;
    do {
        cout << "\nPlease enter a number to perform the following operations:\n" << endl;
        cout << "1. View a list of all registered users(username, current balance, transaction history)" << endl;
        cout << "2. Edit accounts." << endl;
        cout << "3. View all transactions within the system." << endl;
        cout << "4. Adjust a user's balance." << endl;
        cout << "5. Logout." << endl;
        cout << "\nEnter your choice: ";
        cin >> choice;
        system("cls");
        switch (choice)
        {
        case '1':
            viewRegUsers(users);
            break;
        case '2':
            editAccount(users);
            break;
        case '3':
            Transactions::CashItTransactions(cashItTransaction);
            break;
        case '4':
            adjustBalance(users);
            break;
        case '5':
            system("cls");
            cout << "\033[1;32m\t\t\t\t\t\t\t\tCashIt\033[0m";
            return true;
        default:
            cout << "Invalid choice!" << endl;
            continue;
        }
        do {
            cout << "Do you want to continue using CashIt? (Y/N): ";
            cin >> answer;
            if (answer == 'n' || answer == 'N')
            {
                return false;
            }
            if (answer != 'Y' && answer != 'y' && answer != 'n' && answer != 'N') cout << "Invalid choice" << endl;

        } while (answer != 'Y' && answer != 'y' && answer != 'n' && answer != 'N');
        system("cls");
    } while (true);
}
Admin::~Admin(void)
{
}
