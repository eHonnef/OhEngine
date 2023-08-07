#include <OhEngine/Application.hpp>
#include <OhEngine/Events/Events.hpp>
#include <OhEngine/Utils/Logger.hpp>

namespace OhEngine {

#define BIND_EVENT_FN(x) [this](auto && PH1) { return x(std::forward<decltype(PH1)>(PH1)); }

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
        d.Dispatch<CMouseMovedEvent>(BIND_EVENT_FN(OnMouseMove));

        TRACE("{}", Event.IsHandled())
    }

    bool CApplication::OnWindowClose([[__maybe_unused__]] CWindowCloseEvent &e) {
        m_bRunning = false;
        return true;
    }

    bool CApplication::OnMouseMove(CMouseMovedEvent &e) {
        TRACE(e.ToString())
        return true;
    }

} // namespace OhEngine
