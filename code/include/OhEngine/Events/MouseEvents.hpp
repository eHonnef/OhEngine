#pragma once

#include <OhEngine/Events/EventBase.hpp>

namespace OhEngine {
    class OHENGINE_PUBLIC CMouseMovedEvent : public CEvent {
    public:
        CMouseMovedEvent(float fX, float fY) : m_MousePos(fX, fY) {}

        inline float GetX() const {
            return m_MousePos.x;
        }

        inline float GetY() const {
            return m_MousePos.y;
        }

        inline const Mouse::SMousePosition &GetMousePos() const {
            return m_MousePos;
        }

        std::string ToString() const override {
            return fmt::format("MouseMovedEvent: [{:.4}, {:.4}];", GetX(), GetY());
        }

        EVENT_CLASS_TYPE(EEventType::MouseMoved)

    private:
        Mouse::SMousePosition m_MousePos;
    };

    class OHENGINE_PUBLIC CMouseScrolledEvent : public CEvent {
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

    class OHENGINE_PRIVATE CMouseBtnEvent : public CEvent {
    public:
        inline int GetMouseBtn() const {
            return m_nBtn;
        }

        inline float GetX() const {
            return m_MousePos.x;
        }

        inline float GetY() const {
            return m_MousePos.x;
        }

        inline const Mouse::SMousePosition &GetMousePos() const {
            return m_MousePos;
        }

    protected:
        explicit CMouseBtnEvent(int nBtn, float fX, float fY) : m_nBtn(nBtn), m_MousePos(fX, fY) {}

        int m_nBtn;
        Mouse::SMousePosition m_MousePos;
    };

    class OHENGINE_PUBLIC CMouseBtnPressedEvent : public CMouseBtnEvent {
    public:
        CMouseBtnPressedEvent(int nBtn, float fX, float fY) : CMouseBtnEvent(nBtn, fX, fY) {}

        std::string ToString() const override {
            return fmt::format("MouseButtonPressedEvent: x={:.4}; y={:.4}; {:#x};", GetX(), GetY(), m_nBtn);
        }

        EVENT_CLASS_TYPE(EEventType::MouseBtnPressed)
    };

    class OHENGINE_PUBLIC CMouseBtnReleasedEvent : public CMouseBtnEvent {
    public:
        CMouseBtnReleasedEvent(int nBtn, float fX, float fY) : CMouseBtnEvent(nBtn, fX, fY) {}

        std::string ToString() const override {
            return fmt::format("MouseButtonReleasedEvent: x={:.4}; y={:.4}; {:#x};", GetX(), GetY(), m_nBtn);
        }

        EVENT_CLASS_TYPE(EEventType::MouseBtnReleased)
    };
}  // namespace OhEngine
