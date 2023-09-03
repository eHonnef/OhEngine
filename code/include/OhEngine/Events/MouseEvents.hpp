/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

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
        inline Mouse::Button GetMouseBtn() const {
            return m_Btn;
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

        inline std::string ToString() const override {
            return fmt::format("{}; Btn={:#x};", m_MousePos.ToString(), static_cast<int>(GetMouseBtn()));
        }

    protected:
        explicit CMouseBtnEvent(Mouse::Button Btn, float fX, float fY) : m_Btn(Btn), m_MousePos(fX, fY) {}

        Mouse::Button m_Btn;
        Mouse::SMousePosition m_MousePos;
    };

    class OHENGINE_PUBLIC CMouseBtnPressedEvent : public CMouseBtnEvent {
    public:
        CMouseBtnPressedEvent(Mouse::Button Btn, float fX, float fY) : CMouseBtnEvent(Btn, fX, fY) {}

        std::string ToString() const override {
            return fmt::format("MouseButtonPressedEvent: {}", CMouseBtnEvent::ToString());
        }

        EVENT_CLASS_TYPE(EEventType::MouseBtnPressed)
    };

    class OHENGINE_PUBLIC CMouseBtnReleasedEvent : public CMouseBtnEvent {
    public:
        CMouseBtnReleasedEvent(Mouse::Button Btn, float fX, float fY) : CMouseBtnEvent(Btn, fX, fY) {}

        std::string ToString() const override {
            return fmt::format("MouseButtonReleasedEvent: {}", CMouseBtnEvent::ToString());
        }

        EVENT_CLASS_TYPE(EEventType::MouseBtnReleased)
    };
}  // namespace OhEngine
