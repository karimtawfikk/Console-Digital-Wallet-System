# Cash It


This project introduces a digital wallet system aimed at facilitating secure financial transactions for users. The system includes functionalities designed for both administrators and users, ensuring efficient management of accounts and transactions.

User Requirements:

Administrator Functionality:
- Record Management: Admins can perform various operations related to user accounts, ensuring smooth account management.
- Account Adjustment: Admins have the authority to make adjustments to user account balances as needed.
- Transaction Monitoring: Admins can view registered users, their balances, transaction histories, and perform necessary actions.

User Functionality:
- Account Creation: Users can sign up for the digital wallet system, providing necessary credentials for account creation.
- Financial Operations: Users can perform various financial operations such as viewing current balance, sending money to others, requesting money from others, and managing transaction histories.
- Profile Management: Users have the option to edit their profile information including usernames and passwords.

System Management:

The system includes a CashIt module responsible for user authentication, registration, and interaction. It manages the identification of users as either regular users or administrators, provides registration options, and handles data reading and writing tasks for user, admin, and transaction data.

Transaction Handling:

Transactions are managed through a dedicated class, ensuring the smooth processing of transactions between users. Details of recent transactions are provided, including sender, receiver, amount, date, and time.

File Handling:

File handling functionalities are provided through the FileReader and FileWriter classes. They facilitate the reading and writing of user data, admin data, and transaction data to respective files for data persistence and system continuity.
