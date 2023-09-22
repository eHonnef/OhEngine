/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <OhEngine/Renderer/Triangle.hpp>

namespace OhEngine {
    void CTriangles::IndexTriangle(uint32_t v0, uint32_t v1, uint32_t v2) {
        m_lstTriangles.Insert({v0, v1, v2});
    }

    void CTriangles::IndexTriangle(TTriangle &&Triangle) {
        m_lstTriangles.Insert(Triangle);
    }

    TConstOptRef<TTriangle> CTriangles::Get(size_t uIndex) {
        return m_lstTriangles.At(uIndex);
    }
    CTriangles::TConstIterator CTriangles::begin() const {
        return m_lstTriangles.begin();
    }
    CTriangles::TConstIterator CTriangles::end() const {
        return m_lstTriangles.end();
    }
    CTriangles::TIterator CTriangles::begin() {
        return m_lstTriangles.begin();
    }
    CTriangles::TIterator CTriangles::end() {
        return m_lstTriangles.end();
    }
}  // namespace OhEngine
