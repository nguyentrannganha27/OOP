#ifndef HOTWATERMACHINE_H
#define HOTWATERMACHINE_H

class HotWaterMachine {
private:
    int temperature; // Nhiet do nuoc hien tai
    const int MIN_TEMP = 70;
    const int MAX_TEMP = 100;

public:
    HotWaterMachine(); // Constructor
    void setTemperature(int temp);
    int getTemperature() const;
    void boilWater() const; // Ham dun nuoc
};

#endif