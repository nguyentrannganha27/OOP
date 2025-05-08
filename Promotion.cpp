#include "Promotion.h"
#include <ctime>

bool PromoCode::isValid() {
    return remainingUses > 0 && expirationTime > time(nullptr);  // Kiểm tra mã khuyến mãi có hợp lệ không
}

int PromoCode::applyPromoCode(const std::string& enteredCode, int productPrice, int qty) {
    if (code == enteredCode && isValid()) {
        int discountAmount = (discountPercent * productPrice * qty) / 100;
        remainingUses--;  // Giảm số lượng mã khuyến mãi còn lại
        return discountAmount;
    }
    return 0;  // Nếu mã không hợp lệ, trả về 0
}
