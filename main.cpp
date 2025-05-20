#include "Product.h"
#include "Menu.h"
#include "Money.h"
#include "Order.h"
#include "Promotion.h"
#include "Invoice.h"
#include "Admin.h"  // Added new header
#include"Hotwatermachine.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <ctime>

using namespace std;

int main() {
    vector<Product> productList = {
        {"Coca", 10000, 5},
        {"7-Up", 11000, 3},
        {"C2", 12000, 2},
        {"Olong", 15000, 4},
        {"Mi ly", 10000, 6},
        {"Ca phe pha", 15000, 5},
        {"Tra gung",10000,6},
    };

    vector<PromoCode> promoList = {
        {"JULY01", 15, 1, 1688160000},
        {"DISCOUNT10", 10, 1, time(nullptr) + 7 * 24 * 3600},
    };
 HotWaterMachine waterMachine;
while (true) {
    cout << "\n==== VENDING MACHINE ====";
    cout << "\n1. View menu and purchase";
    cout << "\n2. Admin mode";
    cout << "\n3. Use hot water machine";
    cout << "\nSelect an option: ";
    
    int mainChoice;
    cin >> mainChoice;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Please enter a number.\n";
        continue;
    }

    switch (mainChoice) {
        case 1:
            if (authenticateAdmin()) {
                showAdminMenu(productList);
            }
            break;
        case 2: {
            while (true) {
                printMenu(productList);
                cout << "Enter product option (0 to cancel): ";
                int option;
                cin >> option;
                
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input! Please enter a number.\n";
                    continue;
                }
                
                if (option == 0) break;  // Thoát về menu chính
                
                orderItem(option, productList, promoList);
            }
            break;
        }
        case 3: {
            if (balance <= 0) {
                cout << "\n  Ban can nap tien truoc khi su dung may nuoc nong.\n";
                break; 
    }
            int choice;
            do {
                cout << "\n== Hot Water Machine ==";
                cout << "\n1. Set temperature";
                cout << "\n2. Boil water";
                cout << "\n3. Check current temperature";
                cout << "\n0. Return";
                cout << "\nYour choice: ";
                cin >> choice;

            if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input!\n";
                    continue;
                }

            switch (choice) {
                 case 1: {
                        int newTemp;
                        cout << "Enter desired temperature (70-100): ";
                        cin >> newTemp;
                        waterMachine.setTemperature(newTemp);
                        break;
                    }
                 case 2:

                        waterMachine.boilWater();
                        break;
                 case 3:
                        cout << "Current water temperature: " << waterMachine.getTemperature() << " C\n";
                        break;
                 case 0:
                        break;
                   default:
                        cout << "Invalid option.\n";
                }
            } while (choice != 0);
            break;
}
        
        default:
            cout << "Invalid choice. Please try again.\n";
    }
}}