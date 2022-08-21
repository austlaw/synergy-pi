//
// Created by xela on 5/3/18.
//

#pragma once

#include "core/mouse_types.h"
#include "HIDDevice.h"

class HIDMouse : public HIDDevice {
public:
    HIDMouse(const std::string& path);
    ~HIDMouse();

    void move(float fx, float fy);
    void relativeMove(SInt32 dx, SInt32 dy);

    void updateButton(ButtonID button, bool press);

private:
    static const UInt32 DATA_SIZE = 5;
    static const UInt32 LOGICAL_MAX = 0x7FFF;
    SInt32              m_x;
    SInt32              m_y;
};
