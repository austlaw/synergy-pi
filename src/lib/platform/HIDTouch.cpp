//
// Created by xela on 8/14/18.
//

#include <base/Log.h>
#include "HIDTouch.h"

HIDTouch::HIDTouch(
        const std::string& path) :
    HIDDevice(path, DATA_SIZE)
{

}

HIDTouch::~HIDTouch() {

}

void HIDTouch::move(float fx, float fy) {

    m_data[0] = 0x02;

    auto xCoord = (UInt32) (fx * RESOLUTION);
    auto yCoord = (UInt32) (fy * RESOLUTION);

    LOG((CLOG_DEBUG "%u %u", x, y));

    m_data[1] = (x >> 8) & 0xFF;
    m_data[2] = x & 0xFF;

    m_data[3] = (y >> 8) & 0xFF;
    m_data[4] = y & 0xFF;

    LOG((CLOG_DEBUG "%u %u, %u %u", m_data[1], m_data[2], m_data[3], m_data[4]));

    update();
}

/*
void HIDTouch::move(float xFrac, float yFrac) {

    m_data[0] = 0x02;

    auto xCoord = (UInt32) (xFrac * RESOLUTION);
    auto yCoord = (UInt32) (yFrac * RESOLUTION);

    LOG((CLOG_DEBUG "%u %u", xCoord, yCoord));

    m_data[1] = xCoord & 255;
    m_data[2] = (xCoord >> 8) & 255;

    m_data[3] = yCoord & 255;
    m_data[4] = (yCoord >> 8) & 255;

    LOG((CLOG_DEBUG "%u %u, %u %u", m_data[1], m_data[2], m_data[3], m_data[4]));

    update();
}
*/
