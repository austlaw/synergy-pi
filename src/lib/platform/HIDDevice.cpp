//
// Created by xela on 5/3/18.
//

#include "base/Log.h"
#include "core/XScreen.h"
#include "HIDDevice.h"

#include <unistd.h>
#include <fcntl.h>

HIDDevice::HIDDevice(
        const std::string &path,
        UInt32 dataSize) :
    m_path(path),
    m_dataSize(dataSize)
{
    if ((m_fd = open(path.c_str(), O_RDWR, 0666)) == -1) {
        throw XScreenOpenFailure("failed to open HID device");
    }

    LOG((CLOG_DEBUG "hid device created: %s", path));

    m_data = new char[m_dataSize];
    memset(m_data, 0, m_dataSize);
}

HIDDevice::~HIDDevice()
{
    close(m_fd);
    delete m_data;
}

void HIDDevice::update() {
    size_t written = 0;

    while (written < m_dataSize) {
        ssize_t result = write(m_fd, m_data + written, m_dataSize - written);
        if (result < 0) {
            LOG((CLOG_DEBUG "Failed to write to HID device: %s", m_path));
            throw std::runtime_error("failed to write to HID device");
        }
        written += result;
    }
}
