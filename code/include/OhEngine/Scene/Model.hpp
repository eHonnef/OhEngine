/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <OhEngine/Renderer/Triangle.hpp>
#include <utility>

namespace OhEngine {
    class CModel {
    public:
        CModel();
        CModel(std::string  strName);

        void AddPolygon(const TVector<size_t>& lstPolygon);

        const std::string &Name() const;
        TVertices &Vertices();
        TTriangles &Triangles();
        const TVertices &Vertices() const;
        const TTriangles &Triangles() const;

    private:
        [[maybe_unused]] static constexpr bool c_bLogModule = true;

        std::string m_strName;
        TVertices m_Vertices;
        TTriangles m_Triangles;
    };
}  // namespace OhEngine
