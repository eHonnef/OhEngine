/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <OhEngine/Renderer/Buffers.hpp>
#include <OhEngine/Renderer/Vertex.hpp>

namespace OhEngine {
    class IDrawableArea {
    public:
        virtual ~IDrawableArea() = default;
        virtual void ClearBuffers() = 0;
        virtual void SwapBuffer(const CBuffer& Buffer) = 0;
        virtual void Show() = 0;
    };
}
