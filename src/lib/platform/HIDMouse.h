//
// Created by xela on 5/3/18.
//

#pragma once

#include "synergy/mouse_types.h"
#include "HIDDevice.h"

class HIDMouse : public HIDDevice {
public:
    HIDMouse(const std::string& path);
    ~HIDMouse();

    void updateButton(ButtonID button, bool press);
    void relativeMove(SInt32 dx, SInt32 dy) const;
    void wheel(SInt32 dy) const;

private:
    static const UInt32 REPORT_SIZE = 7;
    static const UInt32 LOGICAL_MAX = 0x7FFF;
    static const UInt32 WHEEL_SCALE = 64;
    char m_buttons;
};
