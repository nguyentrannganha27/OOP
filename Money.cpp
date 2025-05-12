// Tien.cpp
#include "Money.h"
#include <iostream>
using namespace std;
int totalRevenue = 0; 
int balance = 0;  // Global variable to store current balance

// Function to insert money
int getMoney() {
    int inputAmount;
    cout << "\nEnter the amount to insert ( >= 10000):  ";
    cin >> inputAmount;
    if (cin.fail() || inputAmount < 10000) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << " Invalid amount, please try again.\n";
        return 0;
    }
    balance += inputAmount;
    cout << " Successfully inserted " << inputAmount << " VND.\n";
    return balance;
}

// Function to print current balance
void printCurrentBalance() {
    cout << "\n Current balance: " << balance << " VND\n";
}

// Function to return money
void returnMoney() {
    if (balance == 0) {
        cout << "  Error: No money to return!\n";
    } else {
        cout << "\n Returning: " << balance << " VND\n";
        cout << " Change returned successfully.\n";
        balance = 0;  // Reset balance after returning
    }
}
