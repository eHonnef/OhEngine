#pragma once

//#include <OhEngine/Events/Input.hpp>
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
            return fmt::format(
              "KeyPressedEvent: KeyCode={:#x}; ScanCode={:#x}; Repeat={}; AltPressed={}; ShiftKey={}; CtrlKey={};",
              static_cast<int>(m_KeyStruct.KeyCode), static_cast<int>(m_KeyStruct.KeyScanCode), m_KeyStruct.RepeatCount,
              m_KeyStruct.AltKeyStatus, m_KeyStruct.ShiftKeyStatus, m_KeyStruct.CtrlKeyStatus);
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
            return fmt::format("KeyReleasedEvent: KeyCode={:#x}; KeyScanCode={:#x};", static_cast<int>(m_KeyCode),
                               static_cast<int>(m_KeyScanCode));
        }

        EVENT_CLASS_TYPE(EEventType::KeyReleased)

    private:
        Keyboard::KeyScancode m_KeyScanCode;
        Keyboard::Key m_KeyCode;
    };
}  // namespace OhEngine
