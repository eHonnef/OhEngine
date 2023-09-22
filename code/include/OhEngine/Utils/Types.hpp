/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <optional>

namespace OhEngine {
    template<typename t_tType>
    using TOptRef = std::optional<std::reference_wrapper<t_tType>>;

    template<typename t_tType>
    using TConstOptRef = std::optional<std::reference_wrapper<const t_tType>>;
}  // namespace OhEngine
