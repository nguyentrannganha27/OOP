#ifndef INVOICE_H                           // Nếu chưa định nghĩa INVOICE_H thì định nghĩa (tránh khai báo lặp)
#define INVOICE_H                           // Định nghĩa INVOICE_H

#include "Product.h"                        // Bao gồm file Product.h để sử dụng lớp Product

class Invoice {                             // Định nghĩa lớp Invoice (Hóa đơn)
public:                                     // Phạm vi truy cập công khai
    static void printInvoiceDetails(        // Hàm tĩnh để in chi tiết hóa đơn
        const Product& p,                   // Tham chiếu đến sản phẩm được mua
        int qty,                            // Số lượng sản phẩm mua
        int totalCost,                      // Tổng chi phí sau giảm giá
        int discount                        // Mức giảm giá áp dụng
    );
};

#endif                                      // Kết thúc khối định nghĩa INVOICE_H

