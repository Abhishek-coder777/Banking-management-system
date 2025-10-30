#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <limits>
#include <cstdlib>
using namespace std;

//============================ STRUCT DEFINITION ============================
struct Account {
    int accNo;
    string name;
    string fatherName;
    double balance;
};

//============================ GLOBAL VARIABLES ============================
vector<Account> accounts;

//============================ UTILITY FUNCTIONS ============================
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void waitForEnter() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

Account* findAccount(int accNo) {
    for (auto &acc : accounts)
        if (acc.accNo == accNo)
            return &acc;
    return nullptr;
}

//============================ LOGIN FUNCTIONS ============================
bool adminLogin() {
    string user, pass;
    cout << "\nEnter Admin Username: ";
    cin >> user;
    cout << "Enter Password: ";
    cin >> pass;
    if (user == "admin" && pass == "1234") {
        cout << "\nLogin Successful!\n";
        return true;
    }
    cout << "\nInvalid Admin Credentials!\n";
    return false;
}

bool userLogin() {
    string user, pass;
    cout << "\nEnter Username: ";
    cin >> user;
    cout << "Enter Password: ";
    cin >> pass;
    if (user == "user" && pass == "0000") {
        cout << "\nLogin Successful!\n";
        return true;
    }
    cout << "\nInvalid User Credentials!\n";
    return false;
}

//============================ ACCOUNT MANAGEMENT ============================
void createAccount() {
    Account acc;
    cout << "\n--- CREATE NEW ACCOUNT ---\n";
    cout << "Enter Account Number: ";
    while (!(cin >> acc.accNo)) {
        cout << "Invalid input. Enter again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (findAccount(acc.accNo)) {
        cout << "Account already exists!\n";
        return;
    }

    cin.ignore();
    cout << "Enter Account Holder Name: ";
    getline(cin, acc.name);
    cout << "Enter Father's Name: ";
    getline(cin, acc.fatherName);
    cout << "Enter Initial Amount: ";
    while (!(cin >> acc.balance) || acc.balance < 0) {
        cout << "Invalid amount. Enter again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    accounts.push_back(acc);
    cout << "\nAccount Created Successfully!\n";
}

void displayAll() {
    cout << "\n--- ALL ACCOUNT DETAILS ---\n";
    if (accounts.empty()) {
        cout << "No accounts found.\n";
        return;
    }

    cout << left << setw(12) << "Acc No" << setw(25) << "Name" 
         << setw(25) << "Father Name" << setw(10) << "Balance" << "\n";
    cout << string(70, '-') << "\n";

    for (const auto &acc : accounts) {
        cout << left << setw(12) << acc.accNo
             << setw(25) << acc.name
             << setw(25) << acc.fatherName
             << fixed << setprecision(2) << setw(10) << acc.balance << "\n";
    }
}

void deleteAccount(int accNo) {
    for (auto it = accounts.begin(); it != accounts.end(); ++it) {
        if (it->accNo == accNo) {
            accounts.erase(it);
            cout << "\nAccount deleted successfully!\n";
            return;
        }
    }
    cout << "\nAccount not found!\n";
}

void modifyAccount(int accNo) {
    Account* acc = findAccount(accNo);
    if (!acc) {
        cout << "\nAccount not found!\n";
        return;
    }

    cin.ignore();
    cout << "\n--- MODIFY ACCOUNT ---\n";
    cout << "Enter New Name: ";
    getline(cin, acc->name);
    cout << "Enter New Father's Name: ";
    getline(cin, acc->fatherName);
    cout << "Enter New Balance: ";
    while (!(cin >> acc->balance) || acc->balance < 0) {
        cout << "Invalid balance. Enter again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "\nAccount Modified Successfully!\n";
}

//============================ USER OPERATIONS ============================
void depositWithdraw(int accNo, int option) {
    Account* acc = findAccount(accNo);
    if (!acc) {
        cout << "\nAccount not found!\n";
        return;
    }

    double amount;
    cout << "Enter Amount: ";
    while (!(cin >> amount) || amount <= 0) {
        cout << "Invalid amount. Enter again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (option == 1) { // deposit
        acc->balance += amount;
        cout << "\nDeposited Successfully! New Balance: " << acc->balance << "\n";
    } 
    else if (option == 2) { // withdraw
        if (amount > acc->balance) {
            cout << "\nInsufficient Balance!\n";
        } else {
            acc->balance -= amount;
            cout << "\nWithdrawal Successful! New Balance: " << acc->balance << "\n";
        }
    }
}

void displayAccount(int accNo) {
    Account* acc = findAccount(accNo);
    if (!acc) {
        cout << "\nAccount not found!\n";
        return;
    }

    cout << "\n--- ACCOUNT DETAILS ---\n";
    cout << "Account No: " << acc->accNo << "\n";
    cout << "Holder Name: " << acc->name << "\n";
    cout << "Father Name: " << acc->fatherName << "\n";
    cout << "Balance: " << fixed << setprecision(2) << acc->balance << "\n";
}

//============================ MAIN PROGRAM ============================
int main() {
    char choice;
    int accNo;

    while (true) {
        clearScreen();
        cout << "==============================================\n";
        cout << "         BANK ACCOUNT MANAGEMENT SYSTEM       \n";
        cout << "==============================================\n";
        cout << "1. Admin Login\n";
        cout << "2. User Login\n";
        cout << "3. Exit\n";
        cout << "----------------------------------------------\n";
        cout << "Enter Choice: ";
        cin >> choice;

        if (choice == '1' && adminLogin()) {
            char ch;
            do {
                clearScreen();
                cout << "\n--- ADMIN MENU ---\n";
                cout << "1. Create New Account\n";
                cout << "2. Display All Accounts\n";
                cout << "3. Delete an Account\n";
                cout << "4. Modify an Account\n";
                cout << "5. Back to Main Menu\n";
                cout << "--------------------\n";
                cout << "Enter Choice: ";
                cin >> ch;
                switch (ch) {
                    case '1': createAccount(); break;
                    case '2': displayAll(); break;
                    case '3': cout << "Enter Account No: "; cin >> accNo; deleteAccount(accNo); break;
                    case '4': cout << "Enter Account No: "; cin >> accNo; modifyAccount(accNo); break;
                    case '5': break;
                    default: cout << "\nInvalid Option!\n";
                }
                waitForEnter();
            } while (ch != '5');
        }
        else if (choice == '2' && userLogin()) {
            char ch;
            do {
                clearScreen();
                cout << "\n--- USER MENU ---\n";
                cout << "1. Deposit Money\n";
                cout << "2. Withdraw Money\n";
                cout << "3. Balance Inquiry\n";
                cout << "4. Back to Main Menu\n";
                cout << "--------------------\n";
                cout << "Enter Choice: ";
                cin >> ch;
                switch (ch) {
                    case '1': cout << "Enter Account No: "; cin >> accNo; depositWithdraw(accNo, 1); break;
                    case '2': cout << "Enter Account No: "; cin >> accNo; depositWithdraw(accNo, 2); break;
                    case '3': cout << "Enter Account No: "; cin >> accNo; displayAccount(accNo); break;
                    case '4': break;
                    default: cout << "\nInvalid Option!\n";
                }
                waitForEnter();
            } while (ch != '4');
        }
        else if (choice == '3') {
            cout << "\nThank You for Using Our System!\n";
            cout << "Goodbye!\n";
            break;
        }
        else {
            cout << "\nInvalid Option or Wrong Login!\n";
            waitForEnter();
        }
    }
    return 0;
}