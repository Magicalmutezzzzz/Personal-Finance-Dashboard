#include <iostream>      // for input/output
#include <vector>        // to use std::vector to store transactions
#include <fstream>       // for reading/writing files
#include <sstream>       // for splitting strings when loading from CSV
#include <iomanip>       // for formatting output (like setw)
#include <string>        // to use std::string
#include <cstdlib>       // for atof() to convert string to double
using namespace std;
struct Transaction {
    string date;
    string type;
    string category;
    double amount;
};

vector<Transaction> transactions;

void addTransaction() {
    Transaction t;
    cout << "Enter date (YYYY-MM-DD): ";
    cin >> t.date;
    cout << "Enter type (income/expense): ";
    cin >> t.type;
    cout << "Enter category: ";
    cin >> t.category;
    cout << "Enter amount: ";
    cin >> t.amount;

    transactions.push_back(t);
    cout << "Transaction added successfully!\n";

    // Show all transactions after adding

}

void viewTransactions() {
    cout << "\n--- All Transactions ---\n";
    cout << left << setw(12) << "Date" << setw(10) << "Type"
         << setw(15) << "Category" << setw(10) << "Amount\n";
    cout << "-----------------------------------------------------\n";
    for (size_t i = 0; i < transactions.size(); i++) {
        Transaction t = transactions[i];
        cout << left << setw(12) << t.date
             << setw(10) << t.type
             << setw(15) << t.category
             << setw(10) << t.amount << "\n";
    }
}

void viewBalance() {
    double balance = 0.0;
    for (size_t i = 0; i < transactions.size(); i++) {
        Transaction t = transactions[i];
        if (t.type == "income") balance += t.amount;
        else if (t.type == "expense") balance -= t.amount;
    }
    cout << "\nCurrent Balance: ?" << balance << "\n";
}

void saveToFile() {
    ofstream file("transactions.csv");
    for (size_t i = 0; i < transactions.size(); i++) {
        Transaction t = transactions[i];
        file << t.date << "," << t.type << "," << t.category << "," << t.amount << "\n";
    }
    file.close();
    cout << "Transactions saved to 'transactions.csv'\n";
}

void loadFromFile() {
    transactions.clear();
    ifstream file("transactions.csv");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Transaction t;
        string amountStr;
        getline(ss, t.date, ',');
        getline(ss, t.type, ',');
        getline(ss, t.category, ',');
        getline(ss, amountStr, ',');
        t.amount = atof(amountStr.c_str()); // works in C++98
        transactions.push_back(t);
    }
    file.close();
    cout << "Transactions loaded from 'transactions.csv'\n";
}

void showMenu() {
    cout << "\n--- Personal Finance Dashboard ---\n";
    cout << "1. Add Transaction\n";
    cout << "2. View Transactions\n";
    cout << "3. View Balance\n";
    cout << "4. Save Transactions to File\n";
    cout << "5. Load Transactions from File\n";
    cout << "6. Exit\n";
    cout << "Choose an option: ";
}

int main() {
    int choice;
    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1: addTransaction(); break;
            case 2: viewTransactions(); break;
            case 3: viewBalance(); break;
            case 4: saveToFile(); break;
            case 5: loadFromFile(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid option. Try again.\n";
        }
    } while (choice != 6);

    return 0;
}
