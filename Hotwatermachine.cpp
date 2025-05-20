#include "Hotwatermachine.h"
#include"Money.h"
#include <iostream>

using namespace std;

HotWaterMachine::HotWaterMachine() {
    temperature = 100; // Nuoc soi o 100 do
}
void HotWaterMachine::setTemperature(int temp) {
    if (balance <= 0) {
        cout << "Vui long nap tien truoc khi su dung may pha nuoc!\n";
        return;
    }

    if (temp >= MIN_TEMP && temp <= MAX_TEMP) {
        temperature = temp;
        cout << "Da dieu chinh nhiet do nuoc: " << temperature << " do C\n";
    } else {
        cout << "Nhiet do khong hop le! (70 - 100 do C)\n";
    }
}

int HotWaterMachine::getTemperature() const {
    return temperature;
}

void HotWaterMachine::boilWater() const {
    cout << "Dang pha nuoc o nhiet do " << temperature << " do C...\n";
}
