/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <OhEngine/Scene/Model.hpp>
#include <OhEngine/Utils/Precompiled.hpp>
#include <utility>

namespace OhEngine {
    CModel::CModel() = default;

    CModel::CModel(std::string strName)
        : m_strName{std::move(strName)} {}

    void CModel::AddPolygon(const CList<size_t> &lstPolygon) {
        if (lstPolygon.Size() < 3) {
            OHENGINE_ERROR("Not a polygon, less than 3 vertices given")
            return;
        }
        //@todo: we just assume a triangle, later we triangularize the polygon here
        auto v0 = static_cast<uint32_t>(lstPolygon.At(0)->get());
        auto v1 = static_cast<uint32_t>(lstPolygon.At(1)->get());
        auto v2 = static_cast<uint32_t>(lstPolygon.At(2)->get());
//        OHENGINE_TRACE("{} {} {}", v0, v1, v2)

        m_Triangles.IndexTriangle(v0, v1, v2);
    }

    const std::string &CModel::Name() const {
        return m_strName;
    }

    CVertices &CModel::Vertices() {
        return m_Vertices;
    }

    CTriangles &CModel::Triangles() {
        return m_Triangles;
    }

    const CVertices &CModel::Vertices() const {
        return m_Vertices;
    }

    const CTriangles &CModel::Triangles() const {
        return m_Triangles;
    }
}  // namespace OhEngine
