//
// Created by xela on 8/14/18.
//

#include <base/Log.h>
#include "HIDTouch.h"

HIDTouch::HIDTouch(
        const std::string& path) :
    HIDDevice(path, REPORT_SIZE)
{

}

HIDTouch::~HIDTouch() {

}

void HIDTouch::move(float fx, float fy) {

    auto x = (UInt32) (fx * RESOLUTION);
    auto y = (UInt32) (fy * RESOLUTION);

    LOG((CLOG_DEBUG "%u %u", x, y));

    // Report
    char report[m_reportSize];
    memset(report,0,m_reportSize);

    // Butons??
    report[0] = 0x02;

    // X
    report[1] = (x >> 8) & 0xFF;
    report[2] = x & 0xFF;

    // Y
    report[3] = (y >> 8) & 0xFF;
    report[4] = y & 0xFF;

    update(report);
}
