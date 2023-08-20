#include "doctest/doctest.h"
#include <OhEngine/Utils/Precompiled.hpp>

TEST_CASE("Dictionary test") {
    OhEngine::CDictionary<int, std::string> dict{};

    // @todo: Doesn't work with subcases

//    SUBCASE("Insertion") {
        CHECK(dict.TryInsert(1, "one"));
        CHECK(dict.TryInsert(2, "two"));
        CHECK(dict.TryInsert(3, "three"));
        CHECK_FALSE(dict.TryInsert(1, "one"));
        CHECK_FALSE(dict.TryInsert(1, "zero"));
//    }

//    SUBCASE("Check container") {
        CHECK(dict.Contains(1));
        CHECK_FALSE(dict.Contains(4));
//    }

//    SUBCASE("Size") {
        CHECK(dict.Size() == 3);
        CHECK_FALSE(dict.Empty());
//    }

//    SUBCASE("Access") {
        auto item = dict.At(3);
        CHECK(item.value() == "three");

        item = dict.At(1);
        CHECK(item.value() == "one");

        item = dict.At(2);
        CHECK(item.value() == "two");

        item = dict.At(5);
        CHECK_FALSE(item);
//    }

//    SUBCASE("Extract") {
        item = dict.Extract(3);
        CHECK(item.value() == "three");
        CHECK_FALSE(dict.Contains(3));

        item = dict.Extract(3);
        CHECK_FALSE(item);

        item = dict.At(3);
        CHECK_FALSE(item);
//    }
}
