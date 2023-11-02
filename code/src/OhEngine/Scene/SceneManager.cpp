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
                TDictionary<size_t, uint32_t> hshIndexed{};  // To check if vertex was already added to this model
                bool bInsert = true;

                if (!Shape.mesh.indices.empty()) {
                    // Shape is a mesh
                    size_t uVertexIndex = 0;
                    for (auto &FaceSize: Shape.mesh.num_face_vertices) {
                        TVector<size_t> lstPolygonVerticesIndexes;
                        for (size_t i = 0; i < FaceSize; ++i) {
                            auto uPointIndexBase = size_t(Shape.mesh.indices[uVertexIndex].position_index);

                            // Check if the vertex was already added into the model
                            if (!hshIndexed.contains(uPointIndexBase)) {
                                float x = ParsedObj.attributes.positions[3 * uPointIndexBase + 0];
                                float y = ParsedObj.attributes.positions[3 * uPointIndexBase + 1];
                                float z = ParsedObj.attributes.positions[3 * uPointIndexBase + 2];

                                Model.Vertices().emplace_back(x, y, z);
                                auto uAddedVertexIndex = Model.Vertices().size() - 1;
                                lstPolygonVerticesIndexes.push_back(uAddedVertexIndex);
                                if (!hshIndexed.try_emplace(uPointIndexBase, uAddedVertexIndex).second) {
                                    Logger::Error("Could not add vertex to hash. Duplicated?");
                                }
                            } else {
                                lstPolygonVerticesIndexes.emplace_back(hshIndexed.at(uPointIndexBase));
                            }
                            uVertexIndex += 1;
                        }
                        // Add the polygon to the model
                        Model.AddPolygon(lstPolygonVerticesIndexes);
                    }
                } else if (!Shape.lines.indices.empty()) {
                    // @todo: shape is a set of polylines
                    Logger::Warning("Not implemented");
                } else if (!Shape.points.indices.empty()) {
                    // @todo: shape is a set of points
                    Logger::Warning("Not implemented");
                } else {
                    bInsert = false;
                    Logger::Error("Shape without definition? Shape will not load; ShapeName={}; FilePath={}",
                                   Shape.name, strFilePath);
                }

                if (bInsert) {
                    bResult = bResult || bInsert;  // Return true if at least one shape was loaded.
                    // Insert Model if not empty
                    m_lstModels.emplace_back(std::move(Model));
                }
            }

        } else {
            Logger::Error("Error parsing Wavefront Obj model; FilePath={}", strFilePath);
        }
        return bResult;
    }

    const TList<CModel> &CSceneManager::Models() const {
        return m_lstModels;
    }

    CScene CSceneManager::GetScene() {
        return {m_lstModels.front()};
    }
}  // namespace OhEngine
