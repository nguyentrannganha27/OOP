#include "Invoice.h"
#include <iostream>

using namespace std;
extern int balance;
void printInvoiceDetails(const Product& p, int qty, int totalCost, int discount) {
    int amountPaid = totalCost - discount;  // Tính số tiền thực tế đã trả
    cout << "\n===== Invoice =====\n";
    cout << "Product: " << p.name << "\n";
    cout << "Quantity: " << qty << "\n";
    cout << "Price per item: " << p.price << " VND\n";
    cout << "Total cost (before discount): " << totalCost << " VND\n";
    cout << "Discount: " << discount << " VND\n";
    cout << "Amount paid: " << amountPaid << " VND\n";
    cout << "Remaining balance: " << balance << " VND\n";
    cout << "===================\n";
}
