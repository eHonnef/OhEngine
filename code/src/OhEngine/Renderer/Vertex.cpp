/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <OhEngine/Renderer/Vertex.hpp>

namespace OhEngine {
    /*******************************************************************************************************************
     * Vertex: The Vertex implementation section
     ******************************************************************************************************************/
    CVertex::CVertex(const TPoint &Point) : m_Point(Point) {}

    const TPoint &CVertex::Coord() const {
        return m_Point;
    }

    std::string CVertex::ToString() const {
        return m_Point.ToString();
    }

    /*******************************************************************************************************************
     * Vertices: The Vertices implementation section
     ******************************************************************************************************************/

    std::optional<CVertex> CVertices::operator[](size_t uIndex) const {
        return m_lstVertices.At(uIndex);
    }

    size_t CVertices::Size() const {
        return m_lstVertices.Size();
    }

    uint32_t CVertices::AddVertex(CVertex &&Vertex) {
        m_lstVertices.Insert(Vertex);
        // Downcasting to uint32_t
        return static_cast<uint32_t>(m_lstVertices.Size() - 1);
    }

    CVertices::TConstIterator CVertices::begin() const {
        return m_lstVertices.begin();
    }

    CVertices::TConstIterator CVertices::end() const {
        return m_lstVertices.end();
    }

    CVertices::TIterator CVertices::begin() {
        return m_lstVertices.begin();
    }

    CVertices::TIterator CVertices::end() {
        return m_lstVertices.end();
    }
}  // namespace OhEngine
