#pragma once

#include <OhEngine/Events/EventBase.hpp>

namespace OhEngine {
    class CWindowResizeEvent : public CEvent {
    public:
        CWindowResizeEvent(size_t uWidth, size_t uHeight) : m_uWidth(uWidth), m_uHeight(uHeight) {}

        inline size_t GetHeight() const {
            return m_uHeight;
        }

        inline size_t GetWidth() const {
            return m_uWidth;
        }

        std::string ToString() const override {
            return fmt::format("WindowResizeEvent: W={}; H={};", m_uWidth, m_uHeight);
        }

        EVENT_CLASS_TYPE(EEventType::WindowResize)

    private:
        size_t m_uWidth, m_uHeight;
    };

    class CWindowCloseEvent : public CEvent {
    public:
        CWindowCloseEvent() = default;

        std::string ToString() const override {
            return fmt::format("WindowCloseEvent;");
        }

        EVENT_CLASS_TYPE(EEventType::WindowClose)
    };
} // namespace OhEngine