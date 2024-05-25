#include "CashIt.h"
unordered_map<string, User> usersTable;
unordered_map<string, Admin> adminsTable;
stack<Transactions> cashItTransactionStack;
string userNAME, passWORD, encryptedPassword;
bool wrongCredentials = false;
bool loggedInIsUser = false;
void CashIt::readFromFiles()
{
    FileReader::readUserDataFromFile(usersTable);
    FileReader::readAdminDataFromFile(adminsTable);
    FileReader::readTransactionDataFromFile(cashItTransactionStack);
}
void CashIt::writeToFiles()
{
    FileWriter::writeUsersDataToFiles(usersTable);
    FileWriter::writeAdminDataToFiles(adminsTable);
    FileWriter::writeTransactionDataToFiles(cashItTransactionStack);
}

void CashIt::Identification()
{
    if (usersTable.count(userNAME))
    {
        if (usersTable[userNAME].password != encryptedPassword)
        {
            cout << "\033[1;91m\nWrong Password. Please try again.\033[0m\n";
            wrongCredentials = true;
            return;
        }
        wrongCredentials = false; // logged in is user
        loggedInIsUser = true;
        return;
    }
    if (adminsTable.count(userNAME))
    {
        if (adminsTable[userNAME].password != encryptedPassword)
        {
            cout << "\033[1;31m\nWrong Password. Please try again.\033[0m\n";
            wrongCredentials = true;
            return;
        }
        wrongCredentials = false;
        loggedInIsUser = false;
        return;
    }
    cout << "\033[1;31m\nInvalid Credentials. Please try again.\033[0m\n";
    wrongCredentials = true;
}
int CashIt::registrationChoice()
{
    string password;
    cout << "\n\nPress:";
    cout << "\n1: Login\n2: Sign up\n";
    char choice;
    cout << "\nChoice:";
    cin >> choice;
    if (choice != '1' && choice != '2')
        return choice;
    cout << "\nUsername: ";
    cin >> userNAME;
    cout << "Password: ";
    char c;
    password = "";
    passWORD = "";
    while ((c = _getch()) != '\r')
    {
        if (c == '\b')
        {
            if (!password.empty())
            {
                cout << "\b \b";
                password.pop_back();
                passWORD.pop_back();
            }
        }
        else {
            password += c;
            passWORD += c;
            cout << '*';
        }
    }
    encryptedPassword = Encryptions::generateEncryption(passWORD);
    cout << endl;
    return choice;
}

void CashIt::Start()
{
    bool flag = false;
    char choice;
    readFromFiles();
    cout << "\033[1;32m\t\t\t\t\t\t\t\tCashIt\033[0m";
    do
    {
        choice = registrationChoice();
        switch (choice)
        {
        case '1':
        {
            Identification();
            if (loggedInIsUser && !wrongCredentials)
            {
                if (!usersTable[userNAME].authorized)
                {
                    cout << "\nYour account is still under authorization, wait for your account to be fully reviewed\n";

                }
                else
                    flag = usersTable[userNAME].performOperations(usersTable, userNAME, cashItTransactionStack);
            }
            else if (!loggedInIsUser && !wrongCredentials)
            {
                flag = adminsTable[userNAME].performOperations(usersTable, cashItTransactionStack);
            }
            break;
        }
        case '2':
        {
            User::signUp(usersTable, userNAME, passWORD);
            break;
        }
        default:
            cout << "\nInvalid choice. Please try again.";
        }

    } while ((choice != '1' && choice != '2') || (wrongCredentials == true) || flag);
    writeToFiles();
}