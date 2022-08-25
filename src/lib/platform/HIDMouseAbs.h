#pragma once

#include "core/mouse_types.h"
#include "HIDDevice.h"

class HIDMouseAbs : public HIDDevice {
public:
    HIDMouseAbs(const std::string& path);
    ~HIDMouseAbs();

    void move(float fx, float fy);

    void updateButton(ButtonID button, bool press);

private:
    static const UInt32 DATA_SIZE = 5;
    static const UInt32 LOGICAL_MAX = 0x7FFF;
};
