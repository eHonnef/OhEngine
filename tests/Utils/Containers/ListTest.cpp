/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "doctest/doctest.h"
#include <OhEngine/Utils/Precompiled.hpp>

TEST_CASE("List basic testings") {
    OhEngine::CList<int> lst{};

    CHECK_FALSE(lst.At(0));
    CHECK_FALSE(lst.At(3));
    CHECK(lst.Empty());

    lst.Insert(3);
    lst.Insert(4);
    lst.Insert(5);
    lst.Insert(6);
    // lst = [3,4,5,6]

    CHECK(lst.At(0) == 3);
    CHECK(lst.At(3) == 6);
    CHECK_FALSE(lst.Empty());

    lst.Insert(7, 2);
    // lst = [3,4,7,5,6]

    CHECK(lst.At(2) == 7);
    CHECK(lst.At(3) == 5);
    CHECK(lst.At(1) == 4);

    CHECK(lst.Size() == 5);

    lst.Assign(0, 2);
    // lst = [2,4,7,5,6]
    CHECK(lst.At(0) == 2);

    lst.Assign(lst.Size() + 5, 0);
    // lst = [2,4,7,5,6,0]
    CHECK(lst.At(lst.Size() - 1) == 0);

    lst.At(3)->get() = 3;
    // lst = [2,4,7,3,6,0]
    CHECK(lst.At(3) == 3);

    CHECK(lst.PopBack() == 0);
    // lst = [2,4,7,3,6]

    CHECK(lst.PopFront() == 2);
    // lst = [4,7,3,6]
    CHECK(lst.Size() == 4);

    CHECK(lst.PopAt(10) == 6);
    // lst = [4,7,3]
    CHECK(lst.Size() == 3);

    CHECK(lst.PopAt(1) == 7);
    // lst = [4,3]
    CHECK(lst.Size() == 2);

    CHECK(lst.PopFront() == 4);
    // lst = [3]
    CHECK(lst.Size() == 1);

    CHECK(lst.PopBack() == 3);
    // lst = []
    CHECK(lst.Size() == 0);
    CHECK(lst.Empty());

    CHECK_FALSE(lst.PopAt(0));
}

TEST_CASE("List move operations") {}
TEST_CASE("List copy operations") {}
