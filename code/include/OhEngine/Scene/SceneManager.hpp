/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <OhEngine/Scene/Scene.hpp>

namespace OhEngine {
    class OHENGINE_PRIVATE CSceneManager {
    public:
        CSceneManager();
        bool LoadModelFrom_WavefrontObjFile(const std::string &strFilePath);

        const IListView<CModel> &Models();

        CScene GetScene();

    private:
        [[maybe_unused]] static constexpr bool c_bLogModule = true;

        CList<CModel> m_lstModels;
    };
}  // namespace OhEngine
