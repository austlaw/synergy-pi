//
// Created by xela on 5/3/18.
//

#include <base/Log.h>
#include "HIDMouse.h"

/**
 * @brief Construct a new HIDMouse::HIDMouse object
 * [B]
 * [X][X]
 * [Y][Y]
 * [W][W]
 * @param path 
 */
HIDMouse::HIDMouse(
        const std::string& path) :
    HIDDevice(path, DATA_SIZE)
{

}

HIDMouse::~HIDMouse() {

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

    // X
    m_data[1] = 0x00;
    m_data[2] = 0x00;
    
    // Y
    m_data[3] = 0x00;
    m_data[4] = 0x00;

    // Wheel
    m_data[5] = 0x00;
    m_data[6] = 0x00;

    update();
}


void HIDMouse::relativeMove(SInt32 dx, SInt32 dy) {
    // Convert to SInt16
    SInt16 dx16 = (SInt16)dx;
    SInt16 dy16 = (SInt16)dy;

    LOG((CLOG_DEBUG "relativeMove: %i %i", (SInt32)dx16, (SInt32)dy16));

    // X
    m_data[1] = dx16 & 0xFF;
    m_data[2] = (dx16 >> 8) & 0xFF;

    // Y
    m_data[3] = dy16 & 0xFF;
    m_data[4] = (dy16 >> 8) & 0xFF;

    // Wheel
    m_data[5] = 0x00;
    m_data[6] = 0x00;

    update();
}


void HIDMouse::wheel(SInt32 dy) {
    // Convert to SInt16
    SInt16 dy16 = (SInt16)dy;

    // X
    m_data[1] = 0x00;
    m_data[2] = 0x00;

    // Y
    m_data[3] = 0x00;
    m_data[4] = 0x00;

    // Wheel
    m_data[5] = dy16 & 0xFF;
    m_data[6] = (dy16 >> 8) & 0xFF;

    update();
}