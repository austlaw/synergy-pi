//
// Created by xela on 5/3/18.
//

#pragma once

#include "core/mouse_types.h"
#include "HIDDevice.h"

class HIDMouseAbs : public HIDDevice {
public:
    HIDMouse(const std::string& path);
    ~HIDMouse();

    void move(float fx, float fy);

    void updateButton(ButtonID button, bool press);

private:
    static const UInt32 DATA_SIZE = 5;
    static const UInt32 LOGICAL_MAX = 0x7FFF;
};
