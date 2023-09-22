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

    class CTriangles {
    private:
        using TContainer = CList<TTriangle>;
        using TConstIterator = typename TContainer::TConstIterator;
        using TIterator = typename TContainer::TIterator;

    public:
        void IndexTriangle(uint32_t v0, uint32_t v1, uint32_t v2);
        void IndexTriangle(TTriangle &&Triangle);

        TConstOptRef<TTriangle> Get(size_t uIndex);

        TConstIterator begin() const;
        TConstIterator end() const;
        TIterator begin();
        TIterator end();

    private:
        TContainer m_lstTriangles;
    };
}
