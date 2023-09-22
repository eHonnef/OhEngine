/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <OhEngine/Utils/Types.hpp>
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
        virtual TConstOptRef<t_cType> At(size_t uIndex) const = 0;
        virtual inline size_t Size() const = 0;
        virtual inline bool Empty() const = 0;
        virtual TConstIterator begin() const = 0;
        virtual TConstIterator end() const = 0;
    };

    template<class t_cType>
    class CList : public IListView<t_cType> {
    public:
        using TConstIterator = typename IListView<t_cType>::TConstIterator;
        using TIterator = typename IListView<t_cType>::TIterator;
        using TContainer = typename IListView<t_cType>::TContainer;

    public:
        CList() : m_Container{} {}
        ~CList() override = default;

        TConstOptRef<t_cType> At(size_t uIndex) const override {
            auto Rtn = TConstOptRef<t_cType>{};
            if (Size() > uIndex) {
                Rtn = m_Container.at(uIndex);
            }
            return Rtn;
        }

        TOptRef<t_cType> At(size_t uIndex) {
            auto Rtn = TOptRef<t_cType>{};
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

        /**
         * Reassign an existing item at uIndex with provided Item value.
         * If uIndex is bigger than Size(), it will be inserted in the end.
         * @param uIndex Item index to be reassigned. If bigger than Size(), it will call Insert().
         * @param Item The new Item to be reassigned or inserted (if uIndex > Size()).
         */
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

        /**
         * Copy Insert
         * @param Item The item to put inside the container. Item should meet the requirement of CopyInsertable.
         */
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

        /**
         * Movable insert
         * @param Item The item to put inside the container. Item should meet the requirement of MoveInsertable.
         */
        void Insert(t_cType &&Item) {
            Insert(Item, Size());
        }

        void Insert(t_cType &&Item, size_t uIndex) {
            if (uIndex >= Size()) {
                m_Container.emplace_back(std::move(Item));
            } else {
                m_Container.insert(m_Container.begin() + uIndex, std::move(Item));
            }
        }

        std::optional<t_cType> PopBack() {
            return PopAt(Size());
        }

        std::optional<t_cType> PopFront() {
            return PopAt(0);
        }

        std::optional<t_cType> PopAt(size_t uIndex) {
            auto Rtn = std::optional<t_cType>{};
            if (!Empty()) {
                if (uIndex >= Size()) {
                    uIndex = Size() - 1;
                }

                Rtn.emplace(std::move(m_Container.at(uIndex)));
                m_Container.erase(m_Container.begin() + uIndex);
            }
            return Rtn;
        }

    private:
        TContainer m_Container;
    };
}  // namespace OhEngine
