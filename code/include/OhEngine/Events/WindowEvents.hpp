/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <OhEngine/Events/EventBase.hpp>

namespace OhEngine {
    class OHENGINE_PUBLIC CWindowResizeEvent : public CEvent {
    public:
        CWindowResizeEvent(size_t uWidth, size_t uHeight) : m_WindowSize{uWidth, uHeight} {}

        inline size_t GetHeight() const {
            return m_WindowSize.uWidth;
        }

        inline size_t GetWidth() const {
            return m_WindowSize.uHeight;
        }

        inline TWindowSize GetSize() const {
            return m_WindowSize;
        }

        std::string ToString() const override {
            return fmt::format("WindowResizeEvent: {};", m_WindowSize.ToString());
        }

        EVENT_CLASS_TYPE(EEventType::WindowResize)

    private:
        TWindowSize m_WindowSize;
    };

    class OHENGINE_PUBLIC CWindowCloseEvent : public CEvent {
    public:
        CWindowCloseEvent() = default;

        std::string ToString() const override {
            return fmt::format("WindowCloseEvent;");
        }

        EVENT_CLASS_TYPE(EEventType::WindowClose)
    };
}  // namespace OhEngine
