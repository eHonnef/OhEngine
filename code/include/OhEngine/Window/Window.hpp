/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <OhEngine/Events/Events.hpp>
#include <OhEngine/Utils/Logger.hpp>

namespace OhEngine {
    class CWindow {
    public:
        explicit CWindow(IEventListener &EventsListener);
        virtual ~CWindow();

        void Update();
        void SetVSync(bool bEnable);

        [[nodiscard]] inline bool IsVSyncEnabled() const {
            return m_bVSyncEnabled;
        }

    private:
        static constexpr bool LOG_MODULE = true || OHENGINE_ENABLE_ALL_LOGS;

        [[maybe_unused]] IEventListener &m_EventsListener;

        bool m_bVSyncEnabled;

        class CWindowImpl;
        std::unique_ptr<CWindowImpl> m_pImpl;
    };
} // namespace OhEngine
