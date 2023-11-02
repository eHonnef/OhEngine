/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <array>
#include <list>
#include <optional>
#include <unordered_map>
#include <vector>

namespace OhEngine {
    template<typename t_tType>
    using TAllocator = std::allocator<t_tType>;

    template<typename t_tType>
    using TOptRef = std::optional<std::reference_wrapper<t_tType>>;

    template<typename t_tType>
    using TConstOptRef = std::optional<std::reference_wrapper<const t_tType>>;

    template<typename t_tType>
    using TVector = std::vector<t_tType, TAllocator<t_tType>>;

    template<typename t_tType>
    using TList = std::list<t_tType, TAllocator<t_tType>>;

    template<typename t_tType, size_t t_uSize>
    using TArray = std::array<t_tType, t_uSize>;

    template<typename t_tKey, typename t_tValue>
    using TDictionary = std::unordered_map<t_tKey, t_tValue>;

}  // namespace OhEngine
