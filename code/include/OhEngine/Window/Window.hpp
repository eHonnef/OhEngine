/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <OhEngine/Events/Events.hpp>
#include <OhEngine/Renderer/DrawableArea.hpp>

namespace OhEngine {
    class CWindow : public IDrawableArea {
    public:
        CWindow(IEventListener &rEventsListener);
        ~CWindow() override;

        void ProcessEvents();
        void SetVSync(bool bEnable);

        inline bool IsVSyncEnabled() const {
            return m_bVSyncEnabled;
        }

    private:
        static constexpr bool LOG_MODULE = true;

        [[maybe_unused]] IEventListener &m_rEventsListener;

        bool m_bVSyncEnabled;

        void ClearBuffers() override;
        void SwapBuffer(const CBuffer &Buffer) override;
        void Show() override;

        class CWindowImpl;
        std::unique_ptr<CWindowImpl> m_pImpl;
    };
}  // namespace OhEngine
