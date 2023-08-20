#pragma once

#include <optional>
#include <unordered_map>

namespace OhEngine {
    template<class t_cKey, class t_cType>
    class CDictionary {
    public:
        CDictionary() = default;
        virtual ~CDictionary() = default;

        inline bool Contains(const t_cKey &Key) const {
            return m_Dict.contains(Key);
        }

        inline std::optional<t_cType> At(const t_cKey &Key) {
            if (Contains(Key)) {
                return std::optional<t_cType>{m_Dict.at(Key)};
            } else {
                return std::optional<t_cType>{};
            }
        }

        inline std::optional<t_cType> Extract(const t_cKey &Key) {
            auto Node = m_Dict.extract(Key);
            if (Node) {
                return std::optional<t_cType>{Node.mapped()};
            } else {
                return std::optional<t_cType>{};
            }
        }

        inline size_t Size() const {
            return m_Dict.size();
        }

        inline bool Empty() const {
            return m_Dict.empty();
        }

        bool TryInsert(const t_cKey &Key, const t_cType &Item) {
            if (Contains(Key)) {
                return false;
            } else {
                m_Dict.emplace(std::make_pair(Key, Item));
                return true;
            }
        }

    private:
        std::unordered_map<t_cKey, t_cType> m_Dict{};
    };
}  // namespace OhEngine
