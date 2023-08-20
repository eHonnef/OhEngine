#pragma once

#include <optional>
#include <vector>

namespace OhEngine {
    template<class t_cType>
    class IListView {
    public:
        virtual ~IListView() = default;
        virtual std::optional<t_cType> At(size_t uIndex) const = 0;
        virtual inline size_t Size() const = 0;
        virtual inline bool Empty() const = 0;
    };

    template<class t_cType>
    class CList : public IListView<t_cType> {
    public:
        CList() = default;
        ~CList() override = default;

        std::optional<t_cType> At(size_t uIndex) const override {
            if (uIndex >= Size() || Empty()) {
                return std::optional<t_cType>{};
            } else {
                return std::optional<t_cType>{m_Vector.at(uIndex)};
            }
        }

        inline size_t Size() const override {
            return m_Vector.size();
        }

        inline bool Empty() const override {
            return m_Vector.empty();
        }

        void Insert(const t_cType& Item) {
            Insert(Item, Size());
        }

        void Insert(const t_cType& Item, size_t uPos) {
            if (uPos >= Size()) {
                m_Vector.push_back(Item);
            } else {
                m_Vector.insert(m_Vector.begin() + uPos, Item);
            }
        }

        inline std::optional<t_cType> Pop() {
            return Pop(Size());
        }

        inline std::optional<t_cType> Pop(size_t uPos) {
            if (Empty()) {
                return std::optional<t_cType>{};
            } else {
                if (uPos >= Size()) {
                    uPos = Size() - 1;
                }

                auto item = std::optional{At(uPos)};
                m_Vector.erase(m_Vector.begin() + uPos);
                return item;
            }
        }

    private:
        std::vector<t_cType> m_Vector;
    };
}  // namespace
