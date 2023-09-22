/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <OhEngine/Scene/Scene.hpp>

namespace OhEngine {
    CScene::CScene(CModel &Model)
        : m_rModel{Model} {}

    const CModel &CScene::Model() const {
        return m_rModel;
    }
}  // namespace OhEngine
