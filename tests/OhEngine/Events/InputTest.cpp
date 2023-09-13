/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "OhEngine/Core/Input.hpp"
#include "doctest/doctest.h"

TEST_CASE("Keyboard Keyboard::Key code translation testings") {
    using namespace OhEngine;

    CHECK(Keyboard::ToKeycode(-1) == Keyboard::Key::Unknown);
    CHECK(Keyboard::ToKeycode(-8917246) == Keyboard::Key::Unknown);
    CHECK(Keyboard::ToKeycode(178926) == Keyboard::Key::Unknown);
    CHECK(Keyboard::ToKeycode(101) == Keyboard::Key::Unknown);

    CHECK(Keyboard::ToKeycode(100) == Keyboard::Key::Pause);
    CHECK(Keyboard::ToKeycode(0) == Keyboard::Key::A);

    // @todo: one for each key
}

TEST_CASE("Keyboard Keyboard::KeyScancode code translation testings") {
    using namespace OhEngine;

    CHECK(Keyboard::ToScancode(-1) == Keyboard::KeyScancode::Unknown);
    CHECK(Keyboard::ToScancode(-8917246) == Keyboard::KeyScancode::Unknown);
    CHECK(Keyboard::ToScancode(178926) == Keyboard::KeyScancode::Unknown);
    CHECK(Keyboard::ToScancode(146) == Keyboard::KeyScancode::Unknown);

    CHECK(Keyboard::ToScancode(145) == Keyboard::KeyScancode::LaunchMediaSelect);
    CHECK(Keyboard::ToScancode(0) == Keyboard::KeyScancode::A);

    // @todo: one for each key
}

//TEST_CASE("Keyboard conversion Keyboard::KeyScancode -> Keyboard::Key") {
//    // @todo: one for each key
//}
//
//TEST_CASE("Keyboard conversion Keyboard::KeyScancode -> Keyboard::Key") {
//    // @todo: one for each key
//}

TEST_CASE("Mouse translation testings") {
    using namespace OhEngine;

    CHECK(Mouse::ToButton(-1) == Mouse::Button::Unknown);
    CHECK(Mouse::ToButton(-127893) == Mouse::Button::Unknown);
    CHECK(Mouse::ToButton(127893) == Mouse::Button::Unknown);
    CHECK(Mouse::ToButton(5) == Mouse::Button::Unknown);

    CHECK(Mouse::ToButton(0) == Mouse::Button::Left);
    CHECK(Mouse::ToButton(1) == Mouse::Button::Right);
    CHECK(Mouse::ToButton(2) == Mouse::Button::Middle);
    CHECK(Mouse::ToButton(3) == Mouse::Button::XButton1);
    CHECK(Mouse::ToButton(4) == Mouse::Button::XButton2);
}
