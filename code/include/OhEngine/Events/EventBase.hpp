/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <OhEngine/Events/Input.hpp>
#include <OhEngine/Utils/Precompiled.hpp>

namespace OhEngine {
    enum class EEventType {
        None = 0,
        /* Window events */
        WindowClose,
        WindowResize,
        /* Keyboard events */
        KeyPressed,
        KeyReleased,
        /* Mouse events */
        MouseBtnPressed,
        MouseBtnReleased,
        MouseMoved,
        MouseScrolled
    };

#define EVENT_CLASS_TYPE(eType)                                                                                        \
    static constexpr EEventType GetStaticType() {                                                                      \
        return eType;                                                                                                  \
    }                                                                                                                  \
    virtual constexpr EEventType GetEventType() const override {                                                       \
        return GetStaticType();                                                                                        \
    }
    class OHENGINE_PRIVATE CEventDispatcher;
    class CEvent {
    public:
        bool IsHandled() const {
            return m_bHandled;
        }

        virtual ~CEvent() = default;
        virtual constexpr EEventType GetEventType() const = 0;
        virtual std::string ToString() const = 0;

    protected:
        void SetHandled(bool bHandled) {
            m_bHandled = bHandled;
        }

        bool m_bHandled = false;
        friend class CEventDispatcher;
    };

    class OHENGINE_PRIVATE IEventListener {
    public:
        virtual ~IEventListener() = default;
        virtual void OnEvent(CEvent &Event) = 0;
    };

    class OHENGINE_PRIVATE CEventDispatcher {
    private:
        template<typename T>
        using TEventFn = std::function<bool(T &)>;

        CEvent &m_Event;

    public:
        explicit CEventDispatcher(CEvent &Event) : m_Event(Event) {}

        template<typename T>
        bool Dispatch(TEventFn<T> Fn) {
            if (m_Event.GetEventType() == T::GetStaticType()) {
                m_Event.SetHandled(Fn(*reinterpret_cast<T *>(&m_Event)));
                return true;
            }
            return false;
        }
    };

    class OHENGINE_PUBLIC EventState {
    public:
        EventState(EventState const &) = delete;
        void operator=(EventState const &) = delete;

        static const IListView<Keyboard::SKey>& GetPressedKeys();
        static const IListView<Mouse::Button>& GetPressedMouseButtons();
        static const Mouse::SMousePosition& GetMousePosition();

    private:
        [[maybe_unused]] static constexpr bool LOG_MODULE = true || ENABLE_ALL_LOGS;

        // list of keys
        CList<Keyboard::SKey> m_lstPressedKeys;
        // mouse position
        Mouse::SMousePosition m_MousePos;
        // list of mouse button pressed
        CList<Mouse::Button> m_lstPressedMouseButtons;

        static EventState &Instance();

        EventState();
        ~EventState();

        void HandleEvent(CEvent &Event);

        friend class CWindow; // Forward declaration to Window class
    };
}  // namespace OhEngine
