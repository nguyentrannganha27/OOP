#ifndef PROMOTION_H
#define PROMOTION_H

#include <string>
#include <ctime>

class PromoCode {
public:
    std::string code;
    int discountPercent;
    int remainingUses;  // Số lượng voucher còn lại
    int totalUses;      // Số lượng voucher tổng cộng đã phát hành
    time_t expirationTime;

    bool isValid();  // Declare the function here, but don't define it.
    int applyPromoCode(const std::string& enteredCode, int productPrice, int qty);  // Hàm mới để áp dụng mã khuyến mãi

    PromoCode(std::string c, int discount, int total, time_t expiry) : 
        code(c), discountPercent(discount), remainingUses(total), totalUses(total), expirationTime(expiry) {}
};

#endif
