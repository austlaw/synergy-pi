
#include <base/Log.h>
#include "HIDMouseAbs.h"

HIDMouseAbs::HIDMouseAbs(
        const std::string& path) :
    m_buttons(0x00),
    HIDDevice(path, REPORT_SIZE)
{

}

HIDMouseAbs::~HIDMouseAbs() {

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



// Absolute move
// 0.0 < fx <= 1.0
// 0.0 < fy <= 1.0
// Note: 0.0 is invalid
void HIDMouseAbs::move(float fx, float fy) {
    // Scale
    UInt32 x = fx * LOGICAL_MAX; // 0 is invalid
    UInt32 y = fy * LOGICAL_MAX; // 0 is invalid

    LOG((CLOG_DEBUG "absoluteMove: (%f,%f) (%u,%u)", fx, fy, x, y));

    // Report
    char report[m_reportSize];
    memset(report,0,m_reportSize);

    // Buttons
    report[0] = m_buttons;

    // X
    m_data[1] = x & 0xFF;
    m_data[2] = (x >> 8) & 0xFF;

    // Y
    m_data[3] = y & 0xFF;
    m_data[4] = (y >> 8) & 0xFF;

    // Wheel
    report[5] = 0x00;
    report[6] = 0x00;

    update(report);
}