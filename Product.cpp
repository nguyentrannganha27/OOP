#include "Product.h"

// Constructor
Product::Product(std::string n, int p, int q) : name(n), price(p), quantity(q) {}

// Method to calculate the total value of this product in stock
int Product::getTotalPrice() const {
    return price * quantity;
}
