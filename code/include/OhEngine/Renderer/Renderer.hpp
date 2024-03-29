/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <OhEngine/Renderer/DisplayArea.hpp>
#include <OhEngine/Scene/Scene.hpp>

namespace OhEngine {
    class CRenderer {
    public:
        CRenderer(IDisplayArea &rDisplayArea);
        ~CRenderer();

        void Render(const CScene &Scene);
        void OnResize(size_t uWidth, size_t uHeight);

    private:
        [[maybe_unused]] static constexpr bool c_bLogModule = true;

        class CRendererImpl;
        std::unique_ptr<CRendererImpl> m_pImpl;
    };
}  // namespace OhEngine
