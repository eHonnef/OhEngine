/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <OhEngine/Scene/Model.hpp>

namespace OhEngine {
    class CScene {
    public:
        CScene(CModel &Model);

        const CModel& Model() const;

    private:
        CModel &m_rModel;
    };
}  // namespace OhEngine
