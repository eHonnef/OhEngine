#pragma once

#include <OhEngine/Events/EventBase.hpp>

namespace OhEngine {
    class CKeyPressedEvent : public CEvent {
    public:
        struct SKey {
            int KeyScanCode;
            int KeyCode;
            int RepeatCount;
            bool AltKeyStatus;
            bool ShiftKeyStatus;
            bool CtrlKeyStatus;
            SKey(int nKeyScanCode, int nKeyCode, int nRepeatCount, bool bAltKeyStatus, bool bShiftKeyStatus,
                 bool bCtrlKeyStatus) :
                KeyScanCode(nKeyScanCode),
                KeyCode(nKeyCode), RepeatCount(nRepeatCount), AltKeyStatus(bAltKeyStatus),
                ShiftKeyStatus(bShiftKeyStatus), CtrlKeyStatus(bCtrlKeyStatus) {}
        };

        CKeyPressedEvent(int nKeyScanCode, int nKeyCode, int nRepeatCount, bool bAltKeyStatus, bool bShiftKeyStatus,
                         bool bCtrlKeyStatus) :
            m_KeyStruct(nKeyScanCode, nKeyCode, nRepeatCount, bAltKeyStatus, bShiftKeyStatus, bCtrlKeyStatus) {}

        explicit CKeyPressedEvent(const SKey &KeyParams) : m_KeyStruct{KeyParams} {}

        inline const SKey &GetKeyProperties() const {
            return m_KeyStruct;
        }

        std::string ToString() const override {
            return fmt::format(
              "KeyPressedEvent: {:#x}; ScanCode: {:#x}; Repeat: {}; AltPressed: {}; ShiftKey: {}; CtrlKey: {};",
              m_KeyStruct.KeyCode, m_KeyStruct.KeyScanCode, m_KeyStruct.RepeatCount, m_KeyStruct.AltKeyStatus,
              m_KeyStruct.ShiftKeyStatus, m_KeyStruct.CtrlKeyStatus);
        }

        EVENT_CLASS_TYPE(EEventType::KeyPressed)

    private:
        SKey m_KeyStruct;
    };

    class CKeyReleasedEvent : public CEvent {
    public:
        CKeyReleasedEvent(int nKeyScanCode, int nKeyCode) : m_nKeyScanCode(nKeyScanCode), m_nKeyCode(nKeyCode) {}

        std::string ToString() const override {
            return fmt::format("KeyReleasedEvent: KeyCode={:#x}; KeyScanCode={:#x};", m_nKeyCode, m_nKeyScanCode);
        }

        EVENT_CLASS_TYPE(EEventType::KeyReleased)

    private:
        int m_nKeyScanCode;
        int m_nKeyCode;
    };
} // namespace OhEngine
