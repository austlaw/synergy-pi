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

void HIDMouse::move(SInt32 dx, SInt32 dy) {

    LOG((CLOG_DEBUG "%i %i", dx, dy));

    // TODO: Send multiple moves if the move is greater than 1 byte
    m_data[1] = (char)dx;
    m_data[2] = (char)dy;

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
