//
// Created by xela on 5/3/18.
//

#include <base/Log.h>
#include "HIDMouse.h"

HIDMouse::HIDMouse(
        const std::string& path) :
    HIDDevice(path, DATA_SIZE)
{

}

HIDMouse::~HIDMouse() {

}

// void HIDMouse::move(UInt32 x, UInt32 y) {

//     LOG((CLOG_DEBUG "%i %i", x, y));

//     SInt32 dx = x - m_x;
//     SInt32 dy = y - m_y;

//     relativeMove(dx, dy);

//     update();
// }

void HIDMouse::relativeMove(SInt32 dx, SInt32 dy) {

    LOG((CLOG_DEBUG "relativeMove: %i %i", dx, dy));

    // char
    //m_data[1] = (char)dx;
    //m_data[2] = (char)dy;

    // Convert to SInt16
    SInt16 dx16 = (SInt16)dx;
    SInt16 dy16 = (SInt16)dy;

    // SInt16 Little Endian 
    m_data[1] = dx & 0xFF;
    m_data[2] = (dx >> 8) & 0xFF;

    m_data[3] = dy & 0xFF;
    m_data[4] = (dy >> 8) & 0xFF;

    update();
}

void HIDMouse::updateButton(ButtonID button, bool press) {

    UInt8 mask;

    switch (button){
    case kButtonLeft:
        mask = 0x01;
        break;

    case kButtonRight:
        mask = 0x02;
        break;

    case kButtonMiddle:
        mask = 0x04;
        break;

    default:
        mask = 0x00;
        break;
    }

    // Check if the button needs to be toggled
    if (press && (m_data[0] & mask) == 0) {
        m_data[0] ^= mask;
    } else if (!press && (m_data[0] & mask) != 0) {
        m_data[0] ^= mask;
    }

    update();
}
