/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <OhEngine/Scene/SceneManager.hpp>
#include <OhEngine/Utils/Precompiled.hpp>

namespace OhEngine {

    CSceneManager::CSceneManager()
        : m_lstModels{} {}

    bool CSceneManager::LoadModelFrom_WavefrontObjFile(const std::string &strFilePath) {
        bool bResult = false;
        auto ParsedObj = rapidobj::ParseFile(strFilePath);

        if (!ParsedObj.error) {
            for (auto &Shape: ParsedObj.shapes) {
                CModel Model{Shape.name};
                CDictionary<size_t, uint32_t> hshIndexed{};  // To check if vertex was already added to this model
                bool bInsert = true;

                if (!Shape.mesh.indices.empty()) {
                    // Shape is a mesh
                    size_t uVertexIndex = 0;
                    for (auto &FaceSize: Shape.mesh.num_face_vertices) {
                        CList<size_t> lstPolygonVerticesIndexes;
                        for (size_t i = 0; i < FaceSize; ++i) {
                            auto uPointIndexBase = size_t(Shape.mesh.indices[uVertexIndex].position_index);
                            // Check if the vertex was already added into the model
                            auto Item = hshIndexed.At(uPointIndexBase);

                            if (!Item) {
                                auto x = ParsedObj.attributes.positions[3 * uPointIndexBase + 0];
                                auto y = ParsedObj.attributes.positions[3 * uPointIndexBase + 1];
                                auto z = ParsedObj.attributes.positions[3 * uPointIndexBase + 2];

                                auto uAddedVertexIndex = Model.Vertices().AddVertex({{x, y, z}});
                                lstPolygonVerticesIndexes.Insert(uAddedVertexIndex);
                                if (!hshIndexed.TryInsert(uPointIndexBase, uAddedVertexIndex)) {
                                    OHENGINE_ERROR("Could not add vertex to hash. Duplicated?")
                                }
                            } else {
                                lstPolygonVerticesIndexes.Insert(*Item);
                            }
                            uVertexIndex += 1;
                        }
                        // Add the polygon to the model
                        Model.AddPolygon(lstPolygonVerticesIndexes);
                    }
                } else if (!Shape.lines.indices.empty()) {
                    // @todo: shape is a set of polylines
                    OHENGINE_TRACE("Not implemented")
                } else if (!Shape.points.indices.empty()) {
                    // @todo: shape is a set of points
                    OHENGINE_TRACE("Not implemented")
                } else {
                    bInsert = false;
                    OHENGINE_ERROR("Shape without definition? Shape will not load; ShapeName={}; FilePath={}",
                                   Shape.name, strFilePath)
                }

                if (bInsert) {
                    bResult = bResult || bInsert;  // Return true if at least one shape was loaded.
                    // Insert Model if not empty
                    m_lstModels.Insert(std::move(Model));
                }
            }

        } else {
            OHENGINE_ERROR("Error parsing Wavefront Obj model; FilePath={}", strFilePath)
        }
        return bResult;
    }

    const IListView<CModel> &CSceneManager::Models() {
        return m_lstModels;
    }

    CScene CSceneManager::GetScene() {
        return {m_lstModels.At(0)->get()};
    }
}  // namespace OhEngine
