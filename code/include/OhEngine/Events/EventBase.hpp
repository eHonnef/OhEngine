#pragma once

#include <OhEngine/Utils/Precompiled.hpp>
#include <functional>

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
    class CEventDispatcher;
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

    class IEventListener {
    public:
        virtual ~IEventListener() = default;
        virtual void OnEvent(CEvent &Event) = 0;
    };

    class CEventDispatcher {
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
}  // namespace OhEngine
