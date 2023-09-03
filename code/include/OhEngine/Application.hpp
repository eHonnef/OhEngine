/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <OhEngine/Window/Window.hpp>

namespace OhEngine {
    class CApplication : IEventListener {
    public:
        CApplication();
        ~CApplication() override;

        void Run();

    protected:
        [[maybe_unused]] static constexpr bool LOG_MODULE = true || ENABLE_ALL_LOGS;

        bool m_bRunning;

        void OnEvent(CEvent& Event) override;
        bool OnWindowClose(CWindowCloseEvent &e);
        bool OnKeyPressed(CKeyPressedEvent &e);
        bool OnKeyReleased(CKeyReleasedEvent &e);
    };

    CApplication *CreateApplication();
};  // namespace OhEngine
