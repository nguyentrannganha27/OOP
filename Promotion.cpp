#include "Promotion.h"
#include <ctime>  // Để dùng hàm time()

// Hàm kiểm tra mã khuyến mãi còn hiệu lực không
bool PromoCode::isValid() {
    // Mã hợp lệ khi còn lượt sử dụng và chưa hết hạn (thời gian hiện tại nhỏ hơn thời gian hết hạn)
    return remainingUses > 0 && expirationTime > time(nullptr);
}

// Hàm áp dụng mã khuyến mãi nếu mã nhập đúng và còn hiệu lực
int PromoCode::applyPromoCode(const std::string& enteredCode, int productPrice, int qty) {
    if (code == enteredCode && isValid()) {
        // Tính tiền được giảm: discountPercent% của tổng giá (giá * số lượng)
        int discountAmount = (discountPercent * productPrice * qty) / 100;

        remainingUses--;  // Giảm số lượt còn lại của mã

        return discountAmount;  // Trả về số tiền giảm
    }
    return 0;  // Nếu mã không hợp lệ hoặc sai mã, trả về 0 (không giảm)
}
