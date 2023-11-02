/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <OhEngine/Events/Events.hpp>


namespace OhEngine {
    const TList<Keyboard::SKey> &EventState::GetPressedKeys() {
        return EventState::Instance().m_lstPressedKeys;
    }

    const TList<Mouse::Button> &EventState::GetPressedMouseButtons() {
        return EventState::Instance().m_lstPressedMouseButtons;
    }

    const Mouse::SMousePosition &EventState::GetMousePosition() {
        return EventState::Instance().m_MousePos;
    }

    const TWindowSize &EventState::GetWindowSize() {
        return EventState::Instance().m_WindowSize;
    }

    EventState &EventState::Instance() {
        // Singleton, will only be destroyed by the end of application
#ifdef __clang__
        //!<-- to avoid -Wexit-time-destructors -->
        [[clang::no_destroy]] static EventState StaticInstance{};
#else
        static EventState StaticInstance{};
#endif
        return StaticInstance;
    }

    EventState::EventState()
        : m_lstPressedKeys()
        , m_MousePos{0, 0}
        , m_WindowSize{0, 0} {}

    EventState::~EventState() = default;

    template<class t_cClass>
    inline const t_cClass &Caster(CEvent &Event) {
        return *reinterpret_cast<t_cClass *>(&Event);
    }

    void EventState::HandleEvent(CEvent &Event) {
        switch (Event.GetEventType()) {
            case EEventType::KeyPressed: {
                bool bFound = false;
                auto CurKey = Caster<CKeyPressedEvent>(Event).GetKeyProperties();

                for (auto &it: m_lstPressedKeys) {
                    if (it.KeyScanCode == CurKey.KeyScanCode) {
                        it = CurKey;
                        bFound = true;
                        break;
                    }
                }

                if (!bFound) {
                    m_lstPressedKeys.push_back(Caster<CKeyPressedEvent>(Event).GetKeyProperties());
                }

                break;
            }
            case EEventType::KeyReleased: {
                auto CurEvent = Caster<CKeyReleasedEvent>(Event);

                auto uCount = m_lstPressedKeys.remove_if([&](Keyboard::SKey &Key) {
                    return Key.KeyScanCode == CurEvent.GetKeyScanCode();
                });

                //                for (size_t i = 0; i < m_lstPressedKeys.size(); ++i) {
                //                    auto item = m_lstPressedKeys.at(i);
                //                    if (item && item->get().KeyScanCode == CurEvent.GetKeyScanCode()) {
                //                        m_lstPressedKeys.erase(i);
                //                        bFound = true;
                //                        break;
                //                    }
                //                }

                if (uCount == 0) {
                    Logger::Error("Key release not found in the list. Event={}", CurEvent.ToString());
                }
                break;
            }
            case EEventType::MouseBtnPressed: {
                bool bFound = false;
                auto CurBtn = Caster<CMouseBtnPressedEvent>(Event).GetMouseBtn();

                for (auto &it: m_lstPressedMouseButtons) {
                    if (it == CurBtn) {
                        it = CurBtn;
                        bFound = true;
                        break;
                    }
                }

                if (!bFound) {
                    m_lstPressedMouseButtons.push_back(CurBtn);
                }
                break;
            }
            case EEventType::MouseBtnReleased: {
                //                bool bFound = false;
                auto CurEvent = Caster<CMouseBtnReleasedEvent>(Event);
                auto uCount = m_lstPressedMouseButtons.remove_if([&](Mouse::Button &Btn) {
                    return Btn == CurEvent.GetMouseBtn();
                });

                //                for (size_t i = 0; i < m_lstPressedMouseButtons.Size(); ++i) {
                //                    auto item = m_lstPressedMouseButtons.At(i);
                //                    if (item && item.value() == CurEvent.GetMouseBtn()) {
                //                        m_lstPressedMouseButtons.PopAt(i);
                //                        bFound = true;
                //                        break;
                //                    }
                //                }

                if (uCount == 0) {
                    Logger::Error("Mouse button release not found in the list. Event={}", CurEvent.ToString());
                }

                break;
            }
            case EEventType::MouseMoved: {
                m_MousePos = Caster<CMouseMovedEvent>(Event).GetMousePos();
                break;
            }
            case EEventType::WindowResize: {
                m_WindowSize = Caster<CWindowResizeEvent>(Event).GetSize();
                break;
            }
            default:
                Logger::Error("Event not handled: {}", Event.ToString());
                break;
        }
    }
}  // namespace OhEngine
