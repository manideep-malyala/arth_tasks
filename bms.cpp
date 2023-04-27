#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

class BankAccount {
    private:
        string name;
        string mobile;
        int pin;
        double balance;
        int accountNumber;

    public:
        BankAccount(string name, string mobile, int pin, int accountNumber) {
            this->name = name;
            this->mobile = mobile;
            this->pin = pin;
            this->accountNumber = accountNumber;
            balance = 0;
        }

        string getName() {
            return name;
        }

        string getMobile() {
            return mobile;
        }

        int getPin() {
            return pin;
        }

        double getBalance() {
            return balance;
        }

        int getAccountNumber() {
            return accountNumber;
        }

        void deposit(double amount) {
            balance += amount;
            cout << "Deposit successful. Current balance is " << balance << endl;
        }

        void withdraw(double amount) {
            if (amount > balance) {
                cout << "Insufficient balance." << endl;
            } else {
                balance -= amount;
                cout << "Withdrawal successful. Current balance is " << balance << endl;
            }
        }

        void editAccount(string name, string mobile, int pin) {
            this->name = name;
            this->mobile = mobile;
            this->pin = pin;
            cout << "Account details updated." << endl;
        }

        void deleteAccount(vector<BankAccount>& accounts) {
            int index = -1;
            for (int i = 0; i < accounts.size(); i++) {
                if (accounts[i].getAccountNumber() == accountNumber) {
                    index = i;
                    break;
                }
            }
            if (index != -1) {
                accounts.erase(accounts.begin() + index);
                cout << "Account deleted." << endl;
            }
        }
}; 

int main() {
vector<BankAccount> accounts;
int choice;
while (true) {
    cout << "\nSelect an option:\n1. Create new account\n2. Deposit\n3. Withdraw\n4. Edit account details\n5. Delete account\n6. Exit\n";
    cin >> choice;

    switch (choice) {
        case 1: {
            string name, mobile;
            int pin;
            cout << "Enter name, mobile number, and PIN separated by spaces: ";
            cin >> name >> mobile >> pin;

            int accountNumber = accounts.size() + 1;
            BankAccount account(name, mobile, pin, accountNumber);
            accounts.push_back(account);

            cout << "Account created. Account number is " << accountNumber << endl;
            break;
        }

        case 2: {
            int accountNumber;
            double amount;
            cout << "Enter account number and amount to deposit separated by spaces: ";
            cin >> accountNumber >> amount;

            int index = -1;
            for (int i = 0; i < accounts.size(); i++) {
                if (accounts[i].getAccountNumber() == accountNumber) {
                    index = i;
                    break;
                }
            }
            if (index == -1) {
                cout << "Account not found." << endl;
            } else {
                accounts[index].deposit(amount);
            }
            break;
        }

        case 3: {
            int accountNumber;
            double amount;
            cout << "Enter account number and amount to withdraw separated by spaces: ";
            cin >> accountNumber >> amount;

            int index = -1;
            for (int i = 0; i < accounts.size(); i++) {
                if (accounts[i].getAccountNumber() == accountNumber) {
                    index = i;
                    break;
                }
            }
            if (index == -1) {
                cout << "Account not found." << endl;
            } else {
                accounts[index].withdraw(amount);
            }
            break;
        }

        case 4: {
            int accountNumber, pin;
            string name, mobile;
            cout << "Enter account number: ";
            cin >> accountNumber;

            int index = -1;
            for (int i = 0; i < accounts.size(); i++) {
                if (accounts[i].getAccountNumber() == accountNumber) {
                    index = i;
                    break;
                }
            }
            if (index == -1) {
                cout << "Account not found." << endl;
            } else {
                cout << "Enter new name, mobile number, and PIN separated by spaces: ";
                cin >> name >> mobile >> pin;
                accounts[index].editAccount(name, mobile, pin);
            }
            break;
        }

        case 5: {
            int accountNumber;
            cout << "Enter account number to delete: ";
            cin >> accountNumber;

            for (int i = 0; i < accounts.size(); i++) {
                if (accounts[i].getAccountNumber() == accountNumber) {
                    accounts[i].deleteAccount(accounts);
                    break;
                }
            }
            break;
        }

        case 6:
            return 0;

        default:
            cout << "Invalid choice. Try again." << endl;
            break;
    }
}
}
