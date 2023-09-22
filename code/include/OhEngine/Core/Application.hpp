/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <OhEngine/Renderer/Renderer.hpp>
#include <OhEngine/Scene/SceneManager.hpp>
#include <OhEngine/Window/Window.hpp>

namespace OhEngine {
    class CApplication : IEventListener {
    public:
        CApplication();
        ~CApplication() override;

        void Run();

    protected:
    private:
        [[maybe_unused]] static constexpr bool c_bLogModule = true;

        bool m_bRunning;

        CWindow m_Window;
        CSceneManager m_SceneManager;
        CRenderer m_Renderer;

        void OnEvent(CEvent &Event) override;
        bool OnWindowResize(CWindowResizeEvent &e);
        bool OnWindowClose(CWindowCloseEvent &e);
        bool OnKeyPressed(CKeyPressedEvent &e);
        bool OnKeyReleased(CKeyReleasedEvent &e);
    };

    CApplication *CreateApplication();
}  // namespace OhEngine
