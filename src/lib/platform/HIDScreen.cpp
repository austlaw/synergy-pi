//
// Created by xela on 5/1/18.
//

#include "base/Log.h"
#include "base/TMethodEventJob.h"
#include "HIDScreen.h"

HIDScreen::HIDScreen(
        const std::string& keyboardDevice,
        const std::string& mouseDevice,
        const std::string& mouseAbsDevice,
        SInt32 screenWidth,
        SInt32 screenHeight,
        SInt32 screenX,
        SInt32 screenY,
        std::vector<String> layouts,
        bool isLangSyncEnabled,
        IEventQueue *events
        ) :
    PlatformScreen(events),
    m_mouseDevice(mouseDevice),
    m_mouseAbsDevice(mouseAbsDevice),
    m_width(screenWidth),
    m_height(screenHeight),
    m_x(screenX),
    m_y(screenY),
    m_mouseX(-1),
    m_mouseY(-1),
    m_events(events),
    m_keyState(nullptr)
{
    m_keyState = new HIDKeyState(events, m_keyMap, layouts, isLangSyncEnabled, keyboardDevice);

    // install event handlers
    m_events->adoptHandler(Event::kSystem, m_events->getSystemTarget(),
                           new TMethodEventJob<HIDScreen>(this,
                               &HIDScreen::handleSystemEvent));

    LOG((CLOG_DEBUG "HIDScreen created"));

}

HIDScreen::~HIDScreen()
{
    // TODO
    delete m_keyState;

    m_events->removeHandler(Event::kSystem, m_events->getSystemTarget());
}

void *HIDScreen::getEventTarget() const
{
    return const_cast<HIDScreen*>(this);
}

bool HIDScreen::getClipboard(ClipboardID /*unused*/, IClipboard* /*unused*/) const
{
    // Not supported
    return false;
}

void HIDScreen::getShape(SInt32 &x, SInt32 &y, SInt32 &w, SInt32 &h) const
{
    x = 0;
    y = 0;
    w = m_width;
    h = m_height;
}

void HIDScreen::getCursorPos(SInt32 &x, SInt32 &y) const
{
    x = m_mouseX;
    y = m_mouseY;
}

void HIDScreen::reconfigure(UInt32 /*unused*/)
{
    // Not supported
}

void HIDScreen::warpCursor(SInt32 /*unused*/, SInt32 /*unused*/)
{
    // Not supported
}

UInt32 HIDScreen::registerHotKey(KeyID /*unused*/, KeyModifierMask /*unused*/)
{
    // Not supported
    return 0;
}

void HIDScreen::unregisterHotKey(UInt32 /*unused*/)
{
    // Not supported
}

void HIDScreen::fakeInputBegin()
{
    // Not supported
}

void HIDScreen::fakeInputEnd()
{
    // Not supported
}

SInt32 HIDScreen::getJumpZoneSize() const
{
    // Not supported
    return 0;
}

bool HIDScreen::isAnyMouseButtonDown(UInt32 &buttonID) const
{
    // Not supported
    return false;
}

void HIDScreen::getCursorCenter(SInt32 &x, SInt32 &y) const
{
    // Not supported
}

void HIDScreen::fakeMouseButton(ButtonID button, bool press)
{
    LOG((CLOG_DEBUG "fakeMouseButton: (%d %d)", button, press));
    m_mouseDevice.updateButton(button, press);
}

void HIDScreen::fakeMouseMove(SInt32 x, SInt32 y)
{
    LOG((CLOG_DEBUG "fakeMouseMove: (%i %i)", x, y));

    // Absolute movement
    m_mouseAbsDevice.move((float)x/m_width, (float)y/m_height);

    // Store new position
    m_mouseX = x;
    m_mouseY = y;
}

void HIDScreen::fakeMouseRelativeMove(SInt32 dx, SInt32 dy) const
{
    LOG((CLOG_DEBUG "fakeMouseRelativeMove: (%i %i)", dx, dy));

    // Relative movement
    m_mouseDevice.relativeMove(dx, dy);
}

void HIDScreen::fakeMouseWheel(SInt32 xDelta, SInt32 yDelta) const
{
    m_mouseDevice.wheel(yDelta);
}

void HIDScreen::enable()
{
    // Do nothing
}

void HIDScreen::disable()
{
    // Do nothing
}

void HIDScreen::enter()
{
    // Move the pointer to the center the primary screen
    //m_mouseX = m_x;
    //m_mouseY = m_y;
    //m_mouseAbsDevice.move(0.5, 0.5);
}

bool HIDScreen::leave()
{
    return true;
}

bool HIDScreen::setClipboard(ClipboardID, const IClipboard *)
{
    // Not supported
    return false;
}

void HIDScreen::checkClipboards()
{
    // Not supported
}

void HIDScreen::openScreensaver(bool /*unused*/)
{
    // Not supported
}

void HIDScreen::closeScreensaver()
{
    // Not supported
}

void HIDScreen::screensaver(bool /*unused*/)
{
    // Not supported
}

void HIDScreen::resetOptions()
{
    // TODO
}

void HIDScreen::setOptions(const OptionsList &options)
{
    // TODO
}

void HIDScreen::setSequenceNumber(UInt32)
{
    // TODO
}

bool HIDScreen::isPrimary() const
{
    return false;
}

String
HIDScreen::getSecureInputApp() const
{
	// ignore on Linux
	return "";
}

void HIDScreen::handleSystemEvent(const Event &, void *)
{
    // TODO
}

void HIDScreen::updateButtons()
{
    // TODO
}

IKeyState *HIDScreen::getKeyState() const
{
    return m_keyState;
}
