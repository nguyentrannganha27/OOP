#ifndef ADMIN_H
#define ADMIN_H

#include "Product.h"
#include "Promotion.h"
#include <vector>
#include <string>

const std::string ADMIN_PASSWORD = "admin123";

bool authenticateAdmin();
void showAdminMenu(std::vector<Product>& products, std::vector<PromoCode>& promoList);

void addProduct(std::vector<Product>& products);
void removeProduct(std::vector<Product>& products);
void modifyProduct(std::vector<Product>& products);
void viewSalesHistory();
void viewCurrentBalance();

void addPromoCode(std::vector<PromoCode>& promoList);
void removePromoCode(std::vector<PromoCode>& promoList);
void editPromoCode(std::vector<PromoCode>& promoList);

#endif
