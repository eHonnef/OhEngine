/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <OhEngine/Renderer/Vertex.hpp>

namespace OhEngine {
    typedef struct {
        uint32_t v0;
        uint32_t v1;
        uint32_t v2;
    } TTriangle;

    using TTriangles = TVector<TTriangle>;
}
