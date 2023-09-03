/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <OhEngine/Application.hpp>
#include <OhEngine/Events/Events.hpp>
#include <OhEngine/Utils/Logger.hpp>

namespace OhEngine {

#define BIND_EVENT_FN(x)                                                                                               \
    [this](auto &&PH1) {                                                                                               \
        return x(std::forward<decltype(PH1)>(PH1));                                                                    \
    }

    CApplication::CApplication() {
        m_bRunning = true;
        // m_Window = new CWindow();
    }

    CApplication::~CApplication() = default;

    void CApplication::Run() {
        CWindow window{*this};

        while (m_bRunning) {
            window.Update();
        }
    }

    void CApplication::OnEvent(CEvent &Event) {
        CEventDispatcher d(Event);
        d.Dispatch<CWindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
        d.Dispatch<CKeyPressedEvent>(BIND_EVENT_FN(OnKeyPressed));
        d.Dispatch<CKeyReleasedEvent>(BIND_EVENT_FN(OnKeyReleased));
    }

    bool CApplication::OnWindowClose([[__maybe_unused__]] CWindowCloseEvent &e) {
        m_bRunning = false;
        return true;
    }

    bool CApplication::OnKeyPressed(CKeyPressedEvent &e) {
        OHENGINE_TRACE(e.ToString())
        return true;
    }

    bool CApplication::OnKeyReleased(CKeyReleasedEvent &e) {
        OHENGINE_TRACE(e.ToString())
        return true;
    }

}  // namespace OhEngine
