#ifndef ORDER_H
#define ORDER_H

#include <vector>
#include "Product.h"

// Phải bỏ const để có thể chỉnh sửa số lượng sản phẩm
void orderItem(int option, std::vector<Product>& dsSanPham);

#endif
