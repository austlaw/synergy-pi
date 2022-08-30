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
    m_buttons(0x00),
    HIDDevice(path, REPORT_SIZE)
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
    if (press && (m_buttons & mask) == 0) {
        m_buttons ^= mask;
    } else if (!press && (m_buttons & mask) != 0) {
        m_buttons ^= mask;
    }

    // Report
    char report[m_reportSize];
    memset(report,0,m_reportSize);

    // Buttons
    report[0] = m_buttons;

    // X
    report[1] = 0x00;
    report[2] = 0x00;

    // Y
    report[3] = 0x00;
    report[4] = 0x00;

    // Wheel
    report[5] = 0x00;
    report[6] = 0x00;

    update(report);
}


void HIDMouse::relativeMove(SInt32 dx, SInt32 dy) const {

    // Convert to SInt16
    SInt16 dx16 = (SInt16)dx;
    SInt16 dy16 = (SInt16)dy;

    LOG((CLOG_DEBUG "HIDMouse::relativeMove(%i, %i)", (SInt32)dx16, (SInt32)dy16));

    // Report
    char report[m_reportSize];
    memset(report,0,m_reportSize);

    // Buttons
    report[0] = m_buttons;

    // X
    report[1] = dx16 & 0xFF;
    report[2] = (dx16 >> 8) & 0xFF;

    // Y
    report[3] = dy16 & 0xFF;
    report[4] = (dy16 >> 8) & 0xFF;

    // Wheel
    report[5] = 0x00;
    report[6] = 0x00;

    update(report);
}


void HIDMouse::wheel(SInt32 dy) const {
    // Convert to SInt16
    SInt16 dy16 = (SInt16)(dy/WHEEL_SCALE);

    LOG((CLOG_DEBUG "HIDMouse::wheel(%i)", (SInt32)dy16));

    // Report
    char report[m_reportSize];
    memset(report,0,m_reportSize);

    // Buttons
    report[0] = m_buttons;

    // X
    report[1] = 0x00;
    report[2] = 0x00;

    // Y
    report[3] = 0x00;
    report[4] = 0x00;

    // Wheel
    report[5] = dy16 & 0xFF;
    report[6] = (dy16 >> 8) & 0xFF;

    update(report);
}