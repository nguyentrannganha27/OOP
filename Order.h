#ifndef ORDER_H
#define ORDER_H

#include <vector>
#include "Product.h"

// Must not use 'const' so the product quantities can be modified
void orderItem(int option, std::vector<Product>& productList);

#endif // ORDER_H
