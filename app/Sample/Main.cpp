/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <OhEngine.hpp>

class CSample : public OhEngine::CApplication {
public:
    CSample() : OhEngine::CApplication() {}
    ~CSample() override = default;
};

OhEngine::CApplication *OhEngine::CreateApplication() {
    return new CSample();
}
