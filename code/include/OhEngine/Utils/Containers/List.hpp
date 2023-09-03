/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <optional>
#include <vector>

namespace OhEngine {
    template<class t_cType>
    class IListView {
    protected:
        using TContainer = std::vector<t_cType>;
        using TConstIterator = typename TContainer::const_iterator;
        using TIterator = typename TContainer::iterator;

    public:
        virtual ~IListView() = default;
        virtual std::optional<t_cType> At(size_t uIndex) const = 0;
        virtual inline size_t Size() const = 0;
        virtual inline bool Empty() const = 0;
        virtual TConstIterator begin() const = 0;
        virtual TConstIterator end() const = 0;
    };

    template<class t_cType>
    class CList : public IListView<t_cType> {
    private:
        using TConstIterator = typename IListView<t_cType>::TConstIterator;
        using TIterator = typename IListView<t_cType>::TIterator;
        using TContainer = typename IListView<t_cType>::TContainer;

    public:
        CList() = default;
        ~CList() override = default;

        std::optional<t_cType> At(size_t uIndex) const override {
            auto Rtn = std::optional<t_cType>{};
            if (Size() > uIndex) {
                Rtn = m_Container.at(uIndex);
            }
            return Rtn;
        }

        TConstIterator begin() const override {
            return m_Container.begin();
        }

        TConstIterator end() const override {
            return m_Container.end();
        }

        TIterator begin() {
            return m_Container.begin();
        }

        TIterator end() {
            return m_Container.end();
        }

        void Assign(size_t uIndex, const t_cType &Item) {
            if (Size() <= uIndex) {
                Insert(Item);
            } else {
                m_Container.at(uIndex) = Item;
            }
        }

        inline size_t Size() const override {
            return m_Container.size();
        }

        inline bool Empty() const override {
            return Size() == 0;
        }

        void Insert(const t_cType &Item) {
            Insert(Item, Size());
        }

        void Insert(const t_cType &Item, size_t uIndex) {
            if (uIndex >= Size()) {
                m_Container.push_back(Item);
            } else {
                m_Container.insert(m_Container.begin() + uIndex, Item);
            }
        }

        inline std::optional<t_cType> Pop() {
            return Pop(Size());
        }

        inline std::optional<t_cType> Pop(size_t uIndex) {
            auto Rtn = std::optional<t_cType>{};
            if (!Empty()) {
                if (uIndex >= Size()) {
                    uIndex = Size() - 1;
                }

                Rtn = m_Container.at(uIndex);
                m_Container.erase(m_Container.begin() + uIndex);
            }
            return Rtn;
        }

    private:
        TContainer m_Container;
    };
}  // namespace OhEngine
