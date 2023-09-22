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

        TPoint(float x, float y, float z) : X(x), Y(y), Z(z) {}

        std::string ToString() const {
            return fmt::format("Point: X={:.4}; Y={:.4}; Z={:.4}", X, Y, Z);
        }
    } TPoint;

    class OHENGINE_PRIVATE CVertex {
    public:
        CVertex(const TPoint &Point);

        const TPoint &Coord() const;
        std::string ToString() const;

    private:
        TPoint m_Point;
    };

    class OHENGINE_PRIVATE CVertices {
    private:
        using TContainer = CList<CVertex>;
        using TConstIterator = typename TContainer::TConstIterator;
        using TIterator = typename TContainer::TIterator;

    public:
        TConstIterator begin() const;
        TConstIterator end() const;
        TIterator begin();
        TIterator end();

        std::optional<CVertex> operator[](size_t uIndex) const;

        size_t Size() const;

        /**
         * Insert a Vertex (move operation) inside the Vertex array and returns the Vertex index.
         * @param Vertex The object to be inserted.
         * @return The added vertex index.
         */
        uint32_t AddVertex(CVertex &&Vertex);

    private:
        TContainer m_lstVertices;
    };
}  // namespace OhEngine
