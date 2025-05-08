#ifndef ORDER_H
#define ORDER_H

#include "Product.h"
#include "Promotion.h"
#include <vector>

// Khai báo biến toàn cục balance
extern int balance;

// Hàm xử lý đơn hàng
void orderItem(int option, std::vector<Product>& productList, std::vector<PromoCode>& promoList);

#endif
