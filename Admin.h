#ifndef ADMIN_H
#define ADMIN_H

#include "Product.h"
#include <vector>
#include <string>

const std::string ADMIN_PASSWORD = "admin123";

bool authenticateAdmin();
void showAdminMenu(std::vector<Product>& products);
void addProduct(std::vector<Product>& products);
void removeProduct(std::vector<Product>& products);
void modifyProduct(std::vector<Product>& products);
void viewSalesHistory();
void viewCurrentBalance();

#endif