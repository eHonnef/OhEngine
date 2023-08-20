#include "doctest/doctest.h"
#include <OhEngine/Utils/Precompiled.hpp>

TEST_CASE("Immutable Bimap testing, runtime") {
    OhEngine::CImmutableBimap<int, std::string, 5> DictTest{
      // @todo: This cannot be deduced by the compiler, check on this
      // {1, "1"},
      // {2, "2"},
      // {3, "3"},
      // {4, "4"},
      // {5, "5"}
      std::make_pair(1, "1"), std::make_pair(2, "2"), std::make_pair(3, "3"), std::make_pair(4, "4"),
      std::make_pair(5, "5")};

    CHECK(DictTest.Size() == 5);

    auto item = DictTest.At(2);
    CHECK(item == "2");

    item = DictTest.At(6);
    CHECK_FALSE(item);

    auto item_2 = DictTest.At("2");
    CHECK(item_2 == 2);

    item_2 = DictTest.At("6");
    CHECK_FALSE(item_2);

    CHECK(DictTest.Contains(std::string("1")));
    CHECK(DictTest.Contains(std::string("2")));
    CHECK(DictTest.Contains(std::string("3")));
    CHECK(DictTest.Contains(std::string("4")));
    CHECK(DictTest.Contains(std::string("5")));
    CHECK(DictTest.Contains(1));
    CHECK(DictTest.Contains(2));
    CHECK(DictTest.Contains(3));
    CHECK(DictTest.Contains(4));
    CHECK(DictTest.Contains(5));
}

TEST_CASE("Immutable Bimap testing, compile time") {
    constexpr OhEngine::CImmutableBimap<int, std::string_view, 5> DictTest = {
      std::make_pair(1, "1"), std::make_pair(2, "2"), std::make_pair(3, "3"), std::make_pair(4, "4"),
      std::make_pair(5, "5")};

    CHECK(DictTest.Size() == 5);
    static_assert(DictTest.Size() == 5);

    CHECK(DictTest.At(2) == "2");
    static_assert(DictTest.At(2) == "2");

    CHECK_FALSE(DictTest.At(6));
    static_assert(!DictTest.At(6));

    constexpr auto item = DictTest.At("2");
    CHECK(item == 2);
    static_assert(item == 2);

    constexpr auto item_2 = DictTest.At("6");
    CHECK_FALSE(DictTest.At("6"));
    static_assert(!item_2);

    CHECK(DictTest.Contains(std::string("1")));
    CHECK(DictTest.Contains(std::string("1")));
    CHECK(DictTest.Contains(std::string("2")));
    CHECK(DictTest.Contains(std::string("3")));
    CHECK(DictTest.Contains(std::string("4")));
    CHECK(DictTest.Contains(std::string("5")));
    CHECK(DictTest.Contains(1));
    CHECK(DictTest.Contains(2));
    CHECK(DictTest.Contains(3));
    CHECK(DictTest.Contains(4));
    CHECK(DictTest.Contains(5));

    static_assert(DictTest.Contains(std::string("1")));
    static_assert(DictTest.Contains(std::string("1")));
    static_assert(DictTest.Contains(std::string("2")));
    static_assert(DictTest.Contains(std::string("3")));
    static_assert(DictTest.Contains(std::string("4")));
    static_assert(DictTest.Contains(std::string("5")));
    static_assert(DictTest.Contains(1));
    static_assert(DictTest.Contains(2));
    static_assert(DictTest.Contains(3));
    static_assert(DictTest.Contains(4));
    static_assert(DictTest.Contains(5));
}
