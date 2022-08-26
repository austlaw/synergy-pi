
#include <base/Log.h>
#include "HIDMouseAbs.h"

HIDMouseAbs::HIDMouseAbs(
        const std::string& path) :
    HIDDevice(path, DATA_SIZE)
{

}

HIDMouseAbs::~HIDMouseAbs() {

}

// Absolute move
// 0.0 < fx <= 1.0
// 0.0 < fy <= 1.0
// Note: 0.0 is invalid
void HIDMouseAbs::move(float fx, float fy) {
    // Scale
    UInt32 x = fx * LOGICAL_MAX; // 0 is invalid
    UInt32 y = fy * LOGICAL_MAX; // 0 is invalid

    LOG((CLOG_DEBUG "absoluteMove: (%f,%f) (%u,%u)", x, y));

    // UInt16 Little Endian
    m_data[1] = x & 0xFF;
    m_data[2] = (x >> 8) & 0xFF;

    m_data[3] = y & 0xFF;
    m_data[4] = (y >> 8) & 0xFF;


    update();
}

void HIDMouseAbs::updateButton(ButtonID button, bool press) {

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
