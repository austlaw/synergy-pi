//
// Created by xela on 5/3/18.
//

#pragma once

#include "synergy/KeyState.h"
#include "HIDKeyboard.h"

class HIDKeyState : public KeyState {
public:
    HIDKeyState(IEventQueue* events, synergy::KeyMap& keyMap, std::vector<String> layouts, bool isLangSyncEnabled);
    HIDKeyState(IEventQueue* events, synergy::KeyMap& keyMap, std::vector<String> layouts, bool isLangSyncEnabled,
            const std::string& keyboardDevice);
    ~HIDKeyState();

    // IKeyState overrides
    virtual bool        fakeCtrlAltDel();
    virtual KeyModifierMask pollActiveModifiers() const;
    virtual SInt32      pollActiveGroup() const;
    virtual void        pollPressedKeys(KeyButtonSet& pressedKeys) const;
    virtual void        fakeKeyDown(KeyID id, KeyModifierMask mask,
                            KeyButton button, const String& lang);
    virtual bool        fakeKeyUp(KeyButton button);

protected:
    // KeyState overrides
    virtual void        getKeyMap(synergy::KeyMap& keyMap);
    virtual void        fakeKey(const Keystroke& keystroke);

private:
    void                init();
    HIDKeyboard         m_keyboardDevice;
    std::map<KeyButton, KeyID> m_serverIDToKeyIDMap;
};

