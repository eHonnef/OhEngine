/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <OhEngine/Core/Application.hpp>
#include <OhEngine/Utils/Precompiled.hpp>

namespace OhEngine {

#define BIND_EVENT_FN(x)                                                                                               \
    [this](auto &&PH1) {                                                                                               \
        return x(std::forward<decltype(PH1)>(PH1));                                                                    \
    }

    CApplication::CApplication()
        : m_bRunning(true)
        , m_Window{std::make_unique<CWindow>(*this)}
        , m_SceneManager{std::make_unique<CSceneManager>()}
        , m_Renderer{std::make_unique<CRenderer>(*m_Window)} {}

    CApplication::~CApplication() = default;

    void CApplication::Run() {
        if (m_SceneManager->LoadModelFrom_WavefrontObjFile(
              "/home/bhonnef/projects/OhEngine/app/Sample/african_head.obj")) {
            //            for (auto &model: m_SceneManager.m_Models) {
            //                OHENGINE_INFO(model.Name())
            //                OHENGINE_INFO(model.EdgesToString())
            //            }
        } else {
            Logger::Error("Could not load wavefront obj file");
        }

        while (m_bRunning) {
            m_Window->ProcessEvents();
            // @todo: update scene
            m_Renderer->Render(m_SceneManager->GetScene());
        }
    }

    void CApplication::OnEvent(CEvent &Event) {
        CEventDispatcher d(Event);
        d.Dispatch<CWindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
        d.Dispatch<CKeyPressedEvent>(BIND_EVENT_FN(OnKeyPressed));
        d.Dispatch<CKeyReleasedEvent>(BIND_EVENT_FN(OnKeyReleased));
        d.Dispatch<CWindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));
    }

    bool CApplication::OnWindowClose(CWindowCloseEvent & /*e*/) {
        Logger::Trace<c_bLogModule>("Window close event: Shutting down");
        m_bRunning = false;
        return true;
    }

    bool CApplication::OnKeyPressed(CKeyPressedEvent &e) {
        Logger::Trace<c_bLogModule>(e.ToString());
        return true;
    }

    bool CApplication::OnKeyReleased(CKeyReleasedEvent &e) {
        Logger::Trace<c_bLogModule>(e.ToString());
        return true;
    }

    bool CApplication::OnWindowResize(CWindowResizeEvent &e) {
        m_Renderer->OnResize(e.GetWidth(), e.GetHeight());
        return false;
    }

}  // namespace OhEngine
