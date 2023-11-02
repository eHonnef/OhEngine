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
    CVertex::CVertex(const TPoint &Point)
        : m_Point(Point) {}

    CVertex::CVertex(float fx, float fy, float fz)
        : m_Point(fx, fy, fz) {}

    const TPoint &CVertex::Coord() const {
        return m_Point;
    }

    std::string CVertex::ToString() const {
        return m_Point.ToString();
    }
}  // namespace OhEngine
