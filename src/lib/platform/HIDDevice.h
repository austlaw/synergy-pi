//
// Created by xela on 5/3/18.
//

#pragma once

#include "common/basic_types.h"
#include "fstream"
#include "string"

class HIDDevice {
public:
    HIDDevice(const std::string& path, UInt32 reportSize);
    virtual ~HIDDevice();

protected:
    std::string m_path;
    size_t m_reportSize;
    void update(char* data) const;

private:
    int m_fd;
};
