#pragma once

#include <OhEngine/Events/EventBase.hpp>

namespace OhEngine {
    class CMouseMovedEvent : public CEvent {
    public:
        CMouseMovedEvent(float fX, float fY) : m_fMouseX(fX), m_fMouseY(fY) {}

        inline float GetX() const {
            return m_fMouseX;
        }
        inline float GetY() const {
            return m_fMouseY;
        }

        std::string ToString() const override {
            return fmt::format("MouseMovedEvent: [{:.4}, {:.4}];", m_fMouseX, m_fMouseY);
        }

        EVENT_CLASS_TYPE(EEventType::MouseMoved)

    private:
        float m_fMouseX, m_fMouseY;
    };

    class CMouseScrolledEvent : public CEvent {
    public:
        CMouseScrolledEvent(float fOffsetX, float fOffsetY) : m_fOffsetX(fOffsetX), m_fOffsetY(fOffsetY) {}

        inline float GetYOffset() const {
            return m_fOffsetY;
        }

        inline float GetXOffset() const {
            return m_fOffsetX;
        }

        std::string ToString() const override {
            return fmt::format("MouseScrolledEvent: xOffset={:.4}; yOffset={:.4};", m_fOffsetX, m_fOffsetY);
        }

        EVENT_CLASS_TYPE(EEventType::MouseScrolled)

    private:
        float m_fOffsetX, m_fOffsetY;
    };

    class CMouseBtnEvent : public CEvent {
    public:
        inline int GetMouseBtn() const {
            return m_nBtn;
        }

        inline float GetX() const {
            return m_fX;
        }

        inline float GetY() const {
            return m_fY;
        }

    protected:
        explicit CMouseBtnEvent(int nBtn, float fX, float fY) : m_nBtn(nBtn), m_fX(fX), m_fY(fY) {}

        int m_nBtn;
        float m_fX, m_fY;
    };

    class CMouseBtnPressedEvent : public CMouseBtnEvent {
    public:
        CMouseBtnPressedEvent(int nBtn, float fX, float fY) : CMouseBtnEvent(nBtn, fX, fY) {}

        std::string ToString() const override {
            return fmt::format("MouseButtonPressedEvent: {:#x};", m_nBtn);
        }

        EVENT_CLASS_TYPE(EEventType::MouseBtnPressed)
    };

    class CMouseBtnReleasedEvent : public CMouseBtnEvent {
    public:
        CMouseBtnReleasedEvent(int nBtn, float fX, float fY) : CMouseBtnEvent(nBtn, fX, fY) {}

        std::string ToString() const override {
            return fmt::format("MouseButtonPressedEvent: {:#x};", m_nBtn);
        }

        EVENT_CLASS_TYPE(EEventType::MouseBtnReleased)
    };
}  // namespace OhEngine
