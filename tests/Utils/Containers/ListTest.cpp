/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "doctest/doctest.h"
#include <OhEngine/Utils/Precompiled.hpp>

TEST_CASE("List testings") {
    OhEngine::CList<int> lst{};

    CHECK_FALSE(lst.At(0));
    CHECK_FALSE(lst.At(3));
    CHECK(lst.Empty());

    lst.Insert(3);
    lst.Insert(4);
    lst.Insert(5);
    lst.Insert(6);

    CHECK(lst.At(0) == 3);
    CHECK(lst.At(3) == 6);
    CHECK_FALSE(lst.Empty());

    lst.Insert(7, 2);
    CHECK(lst.At(2) == 7);
    CHECK(lst.At(3) == 5);
    CHECK(lst.At(1) == 4);

    CHECK(lst.Size() == 5);

    lst.Assign(0, 2);
    CHECK(lst.At(0) == 2);

    lst.Assign(lst.Size() + 5, 0);
    CHECK(lst.At(lst.Size() - 1) == 0);
    
    CHECK(lst.Pop() == 0);

    CHECK(lst.Pop() == 6);
    CHECK(lst.Size() == 4);

    CHECK(lst.Pop(10) == 5);
    CHECK(lst.Size() == 3);

    CHECK(lst.Pop(0) == 2);
    CHECK(lst.Size() == 2);

    CHECK(lst.Pop(0) == 4);
    CHECK(lst.Size() == 1);

    CHECK(lst.Pop() == 7);
    CHECK(lst.Size() == 0);
    CHECK(lst.Empty());

    CHECK_FALSE(lst.Pop());
}
