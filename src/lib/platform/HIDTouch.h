//
// Created by xela on 8/14/18.
//

#pragma once

#include "HIDDevice.h"

class HIDTouch : public HIDDevice {
public:
    HIDTouch(const std::string& path);
    ~HIDTouch();

    //void move(float xFrac, float yFrac);
    void move(UInt32 x, UInt32 y);

private:
    static const UInt32 RESOLUTION = 255;
    static const UInt32 DATA_SIZE = 5;
};
