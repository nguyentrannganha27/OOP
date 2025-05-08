#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
public:
    std::string name;
    int price;
    int quantity;

    // Constructor to initialize a product
    Product(std::string n, int p, int q);

    // Method to calculate total value of the product in stock
    int getTotalPrice() const;
};

#endif
