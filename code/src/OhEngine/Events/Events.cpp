#include "OhEngine/Events/EventBase.hpp"
#include <OhEngine/Events/Events.hpp>


namespace OhEngine {
    const IListView<Keyboard::SKey> &EventState::GetPressedKeys() {
        return EventState::Instance().m_lstPressedKeys;
    }

    const Mouse::SMousePosition &EventState::GetMousePosition() {
        return EventState::Instance().m_MousePos;
    }

    EventState &EventState::Instance() {
        // Singleton, will only be destroyed by the end of application
        [[clang::no_destroy]] static EventState StaticInstance{};
        return StaticInstance;
    }

    EventState::EventState() : m_lstPressedKeys(), m_MousePos{0, 0} {}

    EventState::~EventState() = default;

    void EventState::HandleEvent(CEvent &Event) {
        switch (Event.GetEventType()) {
            case EEventType::KeyPressed:
                break;
            case EEventType::KeyReleased:
                break;
            case EEventType::MouseBtnPressed:
                break;
            case EEventType::MouseBtnReleased:
                break;
            case EEventType::MouseMoved:
                m_MousePos.x = reinterpret_cast<CMouseMovedEvent*>(&Event)->GetX();
                m_MousePos.y = reinterpret_cast<CMouseMovedEvent*>(&Event)->GetY();
                break;
            default:
                break;
        }
    }
}  // namespace OhEngine
