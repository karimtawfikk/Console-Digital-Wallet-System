#include "User.h"
using namespace std;
datee currentDate;
timee currentTimee;
queue<User> User::unAuthorizedUsers;

void User::calculateCurrentDate()
{
    auto now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now); //converts auto now to time_t
    tm localTime = {};
    localtime_s(&localTime, &currentTime);
    int year = localTime.tm_year + 1900;
    int month = localTime.tm_mon + 1;
    int day = localTime.tm_mday;
    currentDate.year = year;
    currentDate.month = month;
    currentDate.day = day;

    auto noww = chrono::system_clock::now();
    time_t currentTime2 = chrono::system_clock::to_time_t(noww);
    tm localTime2 = {};
    localtime_s(&localTime2, &currentTime2);
    int hours = localTime2.tm_hour;
    int minutes = localTime2.tm_min;
    
    currentTimee.hours = hours;
    currentTimee.minutes = minutes;
}
User::User()
{

}
User::User(string uname, string pass, long long id, float bal, bool sus, bool auth, list<Transactions> trans, vector<Requests> req)
{
    username = uname;
    password = pass;
    nationalId = id;
    balance = bal;
    suspended = sus;
    authorized = auth;
    transactions = trans;
    requests = req;
}
void User::sendMoney(unordered_map<string, User>& users, string username, stack<Transactions>& cashItTransactions)
{
    float amount;
    string recipient;
    cout << "\n\nChoose which user you want to send money to: " << endl;
    int i = 0;
    for (auto it = users.begin(); it != users.end(); it++)
    {
        if (!it->second.suspended && it->second.username != username)
            cout << ++i << "." << it->first << endl;
    }
    while (true)
    {
        cout << "\n\nUsername: ";
        cin >> recipient;

        if (recipient == users[username].username)
            cout << "You cannot send money to yourself. Please choose a different recipient.";
        else if (!users.count(recipient))
            cout << "This user doesn't exist. Please try again.";
        else
            break;
    }
    bool flag;
    bool validInput = false;
    do
    {
        flag = false;
        do
        {
            string input;
            cout << "Amount: ";
            cin >> input;
        try
        {
            amount = stoi(input); //checks wheather the amount is float or not
            validInput = true;
        }
        catch(invalid_argument& e)
        {
            cout << "\nInvalid amount. Please enter a valid amount.\n" << endl;
        }
        
        } while (!validInput);

        if (amount <= 0)
        {
            flag = true;
            cout << "Invalid amount. Please enter a correct amount." << endl;
        }
        else if (amount > users[username].balance)
        {
            flag = true;
            cout << "Insufficient balance." << endl;
        }
        else
        {
    
            users[username].balance -= amount;
            users[recipient].balance += amount;

            Transactions userTransaction(username, recipient, -amount, currentDate, currentTimee);
            Transactions recipientTransaction(username, recipient, amount, currentDate, currentTimee);

            users[username].transactions.push_back(userTransaction);
            users[recipient].transactions.push_back(recipientTransaction);

            cashItTransactions.push(recipientTransaction);
            cout << amount<< " EGP have been sent successfully to " << recipient << "!" << endl;
        }
    } while (flag);

    
}
void User::requestMoney(unordered_map<string, User>& users, string username)
{
    string reciever;
    float amount;
    int i = 0;
    cout << "\n\nChoose which user you want to request money from: " << endl;
    for (auto it = users.begin(); it != users.end(); it++)
    {
        if (it->first == username) continue; 
        if (!it->second.suspended && it->second.authorized)
        {
            cout << ++i << "." << it->first << endl;
        }
    }
    while (true)
    {
        cout << "\n\nUsername: ";
        cin >> reciever;
        if (reciever == users[username].username)
        {
            cout << "CAUTION:You can't type your username. Please try a different username.";
        }
        else if (!users.count(reciever))
        {
            cout << "This user doesn't exist. Please try again";
        }
        else break;
    }
    bool validInput = false;
    do {
        do
        {
            string input;
            cout << "Amount: ";
            cin >> input;
            try
            {
                amount = stoi(input); 
                validInput = true;
            }
            catch (invalid_argument& e)
            {
                cout << "\nInvalid amount. Please enter a valid amount.\n" << endl;
            }
        } while (!validInput);
        if (amount <= 0)
            cout << "Invalid amount. Please enter a correct amount." << endl;
    } while (amount <= 0);
    Requests request(amount, username, users[reciever].username);
    users[reciever].requests.push_back(request);
    cout << "\n" << amount << " EGP have been requested from " << reciever;
    cout << "\n[Your balance will increase accordingly if they accept.]";
}
void User::viewRequests(unordered_map<string, User>& users, string username, stack<Transactions>& cashItTransactions)
{
    int i = 0;
    auto userIt = users.find(username);
    char choice;
    if (userIt->second.requests.empty())
    {
        cout << "No friends' money requests.";
        return;
    }
    cout << "Friends money Requests:";
    for (auto is = userIt->second.requests.rbegin(); is != userIt->second.requests.rend(); is++) //datatype of requests is Requests
    {
        cout << "\n\nRequest " << ++i << ":" << endl;
        cout << "\n[" << "Requester:" << is->requester << ", Amount:" << is->requestAmount << "]\n";
        do {
            cout << "\nDo you want to accept this request(y/n): ";
            cin >> choice;
            if (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N')
                cout << "Invalid choice.\n";
        } while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N');
        if (choice == 'y' || choice == 'Y')
        {
            if (users[username].balance >= is->requestAmount)
            {
                users[username].balance -= is->requestAmount;
                users[is->requester].balance += is->requestAmount;

                Transactions trans(userIt->first, users[is->requester].username, -is->requestAmount, currentDate, currentTimee);
                Transactions trans2(userIt->first, users[is->requester].username, is->requestAmount, currentDate, currentTimee);

                users[username].transactions.push_back(trans);
                users[is->requester].transactions.push_back(trans2);

                cashItTransactions.push(trans2);
                cout << is->requestAmount << " EGP have been sent to " << is->requester;
            }
            else {
                cout << "\nInsufficient balance";
            }
        }
        else
            cout << "Request successfully denied";
    }
    userIt->second.requests.clear();
}
void User::editInfo(unordered_map<string, User>& users, string&username)
{
    string newUsername, passw;
    char choice;

    cout << "\n\nWhat information would you like to edit?" << endl;
    cout << "1. Username" << endl;
    cout << "2. Password" << endl;
    cout << "3. Cancel" << endl;
    do {
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case '1':
        {
            while (true)
            {
                cout << "Enter new username: ";
                cin >> newUsername;
                if (users[username].username == newUsername)
                    cout << "\nCAUTION:You can't type your username. Please try a different username.\n\n";
                else
                    break;
            }
            while (true)
            {
                if (users.count(username))
                    cout << "This username already exists. Please try again.\n";
                else break;
           }

            auto it = users.find(username);

            it->second.username = newUsername;
            User newUser = it->second;
            users.erase(username);
            username = newUsername;
            users.insert(make_pair(newUsername, newUser));
          
           
            cout << "\nUsername updated successfully." << endl;
            break; }
        case '2':
        {
            string password;
            char c;
            cout << "Enter new password: ";
            password = "";
            passw = "";
            while ((c = _getch()) != '\r')
            {
                if (c == '\b')
                {
                    if (!password.empty())
                    {
                        cout << "\b \b";
                        password.pop_back();
                        passw.pop_back();
                    }
                }
                else {
                    password += c;
                    passw += c;
                    cout << '*';
                }
            }
            users[username].password = Encryptions::generateEncryption(passw);
            cout << "\n\nPassword updated successfully." << endl;
            break; }
        case '3':
            break;
        default:
            cout << "Invalid choice. Please try again.\n" << endl;
        }
    } while (choice != '3' && choice != '1' && choice != '2');
}
void User::viewTransactionHistory(unordered_map<string, User>& users, string username)
{
    if (users[username].transactions.empty())
    {
        cout << "\nNo transaction history.";
        return;
    }
    cout << "\n\nTransaction history:\n\n ";
    for (auto it = users[username].transactions.rbegin(); it != users[username].transactions.rend(); ++it) { //r means reverse iterator to cout the end of the list then keep decrementing to the first position
        cout << "[";
        if (it->amount < 0)
        {
            cout << "To:" << it->reciever;
            cout << ", Amount:" << -it->amount;
        }
        else
        {
            cout << "From:" << it->sender;
            cout << ", Amount:" << it->amount;
        }

        cout << ", Date:" << it->date.day << "-" << it->date.month << "-" << it->date.year;
        cout << ", Time:" << it->time.hours << ":" << it->time.minutes;
        cout << "]\n";
    }
}
void User::signUp(unordered_map<string, User>& users, string userNAME, string passWORD)
{
    long long nationalID;
    string encryptedPassword;
    while (users.count(userNAME))
    {
        string password;
        cout << "\nThis username is already taken, please re-enter a new username and password:";
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
    }
    encryptedPassword = (Encryptions::generateEncryption(passWORD));
    do {
        cout << "\nNational ID: ";
        cin >> nationalID;
        if (to_string(nationalID).length() != 14) {
            cout << "\nInvalid national ID. Please enter exactly 14 digits." << endl;
        }
    } while (to_string(nationalID).length() != 14);
    cout << "\nYou've succesufully created your account. Your request is under review.\n\n";
    users[userNAME] = User(userNAME, encryptedPassword, nationalID, 0.0, true, false, {}, {});
    unAuthorizedUsers.push(users[userNAME]);
}
bool User::performOperations(unordered_map<string, User>& users, string& username, stack<Transactions>& cashItTransactions)
{
    char answer;
    char choice;
    calculateCurrentDate();
    system("cls");
    cout << "\nWelcome " << users[username].username << "!" << endl;
    do {
        cout << "\nPlease enter a number to perform the following operations:" << endl << endl;
        cout << "1. View current balance." << endl;
        cout << "2. Send money to friends" << endl;
        cout << "3. Request money from friends" << endl;
        cout << "4. Edit your profile." << endl;
        cout << "5. View your transactions history." << endl;
        cout << "6. View your friends' money request." << endl;
        cout << "7. Logout." << endl;
        cout << "\nChoice:";
        cin >> choice;

        switch (choice)
        {
        case '1': {
            cout << "\nCurrent Balance: " << users[username].balance;
            break; }
        case '2':
        {
            if (users[username].suspended)
            {
                cout << "Your account is currently suspended. Please wait till your account is under review";
                break;
            }
                if (users[username].balance != 0)
                    sendMoney(users, username, cashItTransactions);
                else
                    cout << "\nYour current balance is 0.";
            break;
        }
        case '3': {
            if (users[username].suspended)
            {
                cout << "Your account is currently suspended. Please wait till your account is under review";
                break;
            }
            requestMoney(users, username);
            break;
        }
        case '4': {
            editInfo(users, username);
            break;
        }
        case '5': {
            viewTransactionHistory(users, username);
            break; }
        case '6': {
            if (users[username].requests.empty())
                cout << "\nNo current requests.\n";
            else
                viewRequests(users, username, cashItTransactions);
            break; }
        case '7': {
            system("cls");
            cout << "\033[1;32m\t\t\t\t\t\t\t\tCashIt\033[0m";
            return true;
        }
        default:
        {
            system("cls");
            cout << "\nInvalid choice, please re-enter the correct operation number:" << endl;
           
            continue; 
        }
        }
        do {
            cout << "\n\nDo you want to continue using CashIt? (Y/N): ";
            cin >> answer;
            if (answer == 'n' || answer == 'N')
                return false;
            if (answer != 'Y' && answer != 'y') cout << "Invalid choice." << endl;
        } while (answer != 'Y' && answer != 'y');

    } while (true);
}
User::~User(void)
{

}
