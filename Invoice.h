#ifndef INVOICE_H
#define INVOICE_H

#include "Product.h"

// Hàm in chi tiết hóa đơn, bao gồm cả khuyến mãi
void printInvoiceDetails(const Product& p, int qty, int totalCost, int discount);

#endif
