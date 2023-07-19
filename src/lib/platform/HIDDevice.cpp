//
// Created by xela on 5/3/18.
//

#include "base/Log.h"
#include "synergy/XScreen.h"
#include "HIDDevice.h"

#include <unistd.h>
#include <fcntl.h>

HIDDevice::HIDDevice(
        const std::string &path,
        UInt32 reportSize) :
    m_path(path),
    m_reportSize(reportSize)
{
    if ((m_fd = open(path.c_str(), O_RDWR, 0666)) == -1) {
        throw XScreenOpenFailure("failed to open HID device");
    }

    LOG((CLOG_DEBUG "HID device created: %s", path.c_str()));
}

HIDDevice::~HIDDevice()
{
    close(m_fd);
}

void HIDDevice::update(char* report) const {
    size_t written = 0;

    while (written < m_reportSize) {
        ssize_t result = write(m_fd, report + written, m_reportSize - written);
        if (result < 0) {
            LOG((CLOG_DEBUG "Failed to write to HID device: %s", m_path.c_str()));
            throw std::runtime_error("failed to write to HID device");
        }
        written += result;
    }
}
