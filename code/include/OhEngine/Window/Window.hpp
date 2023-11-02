/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <OhEngine/Events/Events.hpp>
#include <OhEngine/Renderer/DisplayArea.hpp>

namespace OhEngine {
    class CWindow : public IDisplayArea {
    public:
        CWindow(IEventListener &rEventsListener);
        ~CWindow() override;

        void ProcessEvents();
        void SetVSync(bool bEnable);

        inline bool IsVSyncEnabled() const;

    private:
        static constexpr bool LOG_MODULE = true;

        bool m_bVSyncEnabled;

        void ClearBuffers() override;
        void SwapPixelBuffer(const uint8_t arPixelBuffer[]) override;
        void Show() override;

        class CWindowImpl;
        std::unique_ptr<CWindowImpl> m_pImpl;
    };
}  // namespace OhEngine
