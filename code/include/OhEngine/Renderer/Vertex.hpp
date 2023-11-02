/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <OhEngine/Utils/Precompiled.hpp>
#include <ostream>

namespace OhEngine {
    typedef struct TPoint {
        float X;
        float Y;
        float Z;

        TPoint(float x, float y, float z)
            : X(x)
            , Y(y)
            , Z(z) {}

        std::string ToString() const {
            return std::format("Point: X={:.4}; Y={:.4}; Z={:.4}", X, Y, Z);
        }
    } TPoint;

    class OHENGINE_PRIVATE CVertex {
    public:
        CVertex(const TPoint &Point);
        CVertex(float fx, float fy, float fz);

        const TPoint &Coord() const;
        std::string ToString() const;

    private:
        TPoint m_Point;
    };

    using TVertices = TVector<CVertex>;
}  // namespace OhEngine
