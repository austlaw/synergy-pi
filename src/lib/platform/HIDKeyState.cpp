//
// Created by xela on 5/3/18.
//

#include <base/Log.h>
#include "HIDKeyState.h"

HIDKeyState::HIDKeyState(
        IEventQueue* events,
        synergy::KeyMap& keyMap,
        std::vector<String> layouts,
        bool isLangSyncEnabled
        ) :
        KeyState(events, keyMap, layouts, isLangSyncEnabled),
        m_keyboardDevice("/dev/null")
{
    init();
}

HIDKeyState::HIDKeyState(
        IEventQueue *events,
        synergy::KeyMap& keyMap,
        std::vector<String> layouts,
        bool isLangSyncEnabled,
        const std::string& keyboardDevice
        ) :
        KeyState(events, keyMap, layouts, isLangSyncEnabled),
        m_keyboardDevice(keyboardDevice)
{
    init();
}

HIDKeyState::~HIDKeyState()
{
    // TODO
}

void HIDKeyState::init()
{
    // TODO
}

bool HIDKeyState::fakeCtrlAltDel()
{
    return false;
}

KeyModifierMask HIDKeyState::pollActiveModifiers() const
{
    // TODO
    return 0;
}

SInt32 HIDKeyState::pollActiveGroup() const
{
    // TODO
    return 0;
}

void HIDKeyState::pollPressedKeys(IKeyState::KeyButtonSet &pressedKeys) const
{
    // TODO
}

void HIDKeyState::getKeyMap(synergy::KeyMap &keyMap)
{
    // TODO
}

void HIDKeyState::fakeKeyDown(KeyID id, KeyModifierMask mask, KeyButton button, const String& lang)
{
    LOG((CLOG_DEBUG "fakeKeyDown (0x%x, 0x%x)", button, id));
    m_serverIDToKeyIDMap[button] = id;
    m_keyboardDevice.pressKey(id);
}


bool HIDKeyState::fakeKeyUp(KeyButton button) {
    LOG((CLOG_DEBUG "fakeKeyUp (0x%x)", button));
    auto id = m_serverIDToKeyIDMap.find(button);
    if (id == m_serverIDToKeyIDMap.end()) {
        return false;
    } else {
        m_keyboardDevice.releaseKey(id->second);
        m_serverIDToKeyIDMap.erase(button);
        return true;
    }
}

void HIDKeyState::fakeKey(const KeyState::Keystroke &keystroke)
{
    // TODO
}
