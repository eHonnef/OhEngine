/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <OhEngine/Core/Input.hpp>
#include <OhEngine/Events/EventBase.hpp>

namespace OhEngine {
    class OHENGINE_PUBLIC CKeyPressedEvent : public CEvent {
    public:
        CKeyPressedEvent(Keyboard::KeyScancode KeyScanCode, Keyboard::Key KeyCode, int nRepeatCount, bool bAltKeyStatus,
                         bool bShiftKeyStatus, bool bCtrlKeyStatus) :
            m_KeyStruct{KeyScanCode, KeyCode, nRepeatCount, bAltKeyStatus, bShiftKeyStatus, bCtrlKeyStatus} {}

        explicit CKeyPressedEvent(const Keyboard::SKey &KeyParams) : m_KeyStruct{KeyParams} {}

        inline const Keyboard::SKey &GetKeyProperties() const {
            return m_KeyStruct;
        }

        std::string ToString() const override {
            return std::format("KeyPressedEvent: {}", m_KeyStruct.ToString());
        }

        EVENT_CLASS_TYPE(EEventType::KeyPressed)

    private:
        Keyboard::SKey m_KeyStruct;
    };

    class OHENGINE_PUBLIC CKeyReleasedEvent : public CEvent {
    public:
        CKeyReleasedEvent(Keyboard::KeyScancode KeyScanCode, Keyboard::Key KeyCode) :
            m_KeyScanCode{KeyScanCode}, m_KeyCode{KeyCode} {}

        std::string ToString() const override {
            return std::format("KeyReleasedEvent: KeyCode={:#x}; KeyScanCode={:#x};", static_cast<int>(m_KeyCode),
                               static_cast<int>(m_KeyScanCode));
        }

        inline const Keyboard::KeyScancode &GetKeyScanCode() const {
            return m_KeyScanCode;
        }

        inline const Keyboard::Key &GetKeyCode() const {
            return m_KeyCode;
        }

        EVENT_CLASS_TYPE(EEventType::KeyReleased)

    private:
        Keyboard::KeyScancode m_KeyScanCode;
        Keyboard::Key m_KeyCode;
    };
}  // namespace OhEngine
