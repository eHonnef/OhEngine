/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <frozen/bits/hash_string.h>
#include <frozen/unordered_map.h>
#include <optional>

namespace OhEngine {
    template<typename t_tItem_1, typename t_tItem_2, size_t t_uSize>
    class CImmutableBimap {
    private:
        using value_type = std::pair<t_tItem_1, t_tItem_2>;
        using type_1_2 = std::pair<size_t, t_tItem_2>;
        using type_2_1 = std::pair<size_t, t_tItem_1>;

    public:
        CImmutableBimap(CImmutableBimap &&) = delete;
        CImmutableBimap(const CImmutableBimap &) = delete;

        template<typename... t_tValues>
        constexpr CImmutableBimap(const t_tValues &&...Args) :
            m_Dict_1_2{[&] {
                auto ArgsUnpk = {Args...};
                return Convert<type_1_2>(ArgsUnpk);
            }()},
            m_Dict_2_1{[&] {
                auto ArgsUnpk = {Args...};
                return Convert<type_2_1>(ArgsUnpk);
            }()} {}

        constexpr bool Contains(const t_tItem_1 &Key) const {
            return ContainsImpl(Key);
        }

        constexpr bool Contains(const t_tItem_2 &Key) const {
            return ContainsImpl(Key);
        }

        constexpr inline std::optional<t_tItem_1> At(const t_tItem_2 &Key) const {
            return AtImpl<t_tItem_2, t_tItem_1>(Key);
        }

        constexpr inline std::optional<t_tItem_2> At(const t_tItem_1 &Key) const {
            return AtImpl<t_tItem_1, t_tItem_2>(Key);
        }

        constexpr inline size_t Size() const {
            return t_uSize;
        }

    private:
        // hash(item_1) -> item_2
        frozen::unordered_map<size_t, t_tItem_2, t_uSize> m_Dict_1_2{};
        // hash(item_2) -> item_1
        frozen::unordered_map<size_t, t_tItem_1, t_uSize> m_Dict_2_1{};

        template<typename t_tValue>
        constexpr size_t Hash(const t_tValue &Value) const {
            if constexpr (std::is_integral<t_tValue>::value || std::is_enum<t_tValue>::value) {
                return frozen::elsa<t_tValue>{}(Value, 1234);
            } else {
                return frozen::hash_string(std::string_view{Value}, 13274);
            }
        }

        template<typename t_tKey>
        constexpr bool ContainsImpl(const t_tKey &Key) const {
            static_assert(std::is_same<t_tKey, t_tItem_1>() || std::is_same<t_tKey, t_tItem_2>(),
                          "The key should be the same type of one of this Bimap type.");

            if constexpr (std::is_same<t_tKey, t_tItem_1>()) {
                return m_Dict_1_2.contains(Hash(Key));
            } else if constexpr (std::is_same<t_tKey, t_tItem_2>()) {
                return m_Dict_2_1.contains(Hash(Key));
            } else {
                return false;
            }
        }

        template<typename t_tKey, typename t_tItem>
        constexpr inline std::optional<t_tItem> AtImpl(const t_tKey &Key) const {
            auto RtnVal = std::optional<t_tItem>{};

            if constexpr (std::is_same<t_tKey, t_tItem_1>()) {
                if (ContainsImpl(Key)) {
                    RtnVal = m_Dict_1_2.at(Hash(Key));
                }
            } else if constexpr (std::is_same<t_tKey, t_tItem_2>()) {
                if (ContainsImpl(Key)) {
                    RtnVal = m_Dict_2_1.at(Hash(Key));
                }
            }

            return RtnVal;
        }

        template<typename T>
        constexpr auto Convert(const auto args) {
            std::array<T, t_uSize> arr = {};
            size_t i = 0;
            for (auto &&it: args) {
                if constexpr (std::is_same<T, type_1_2>()) {
                    arr[i++] = std::pair{Hash(it.first), it.second};
                } else if constexpr (std::is_same<T, type_2_1>()) {
                    arr[i++] = std::pair(Hash(it.second), it.first);
                }
            }
            return arr;
        }
    };
}  // namespace OhEngine
