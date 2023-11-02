/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <OhEngine/Utils/Precompiled.hpp>

namespace OhEngine {
    class OHENGINE_PUBLIC Mouse {
    public:
        enum class Button {
            Unknown = -1,  // Unhandled mouse button
            Left = 0,      // The left mouse button
            Right,         // The right mouse button
            Middle,        // The middle (wheel) mouse button
            XButton1,      // The first extra mouse button
            XButton2,      // The second extra mouse button

            ButtonCount  // Keep last -- the total number of mouse buttons
        };

        struct SMousePosition {
            float x;
            float y;
            std::string ToString() const {
                return std::format("Mouse_X={:.4}; Mouse_Y={:.4}", x, y);
            }
            SMousePosition(float fX, float fY) : x{fX}, y{fY} {}
        };

        /**
         * Translates an integer to Mouse::Button
         * @param nButton - an integer to transform into Mouse::Button
         * @return The corresponding Mouse::Button.
         */
        static Button ToButton(int nButton);

        static constexpr std::string_view GetButtonDescription(Mouse::Button Btn);

        Mouse(Mouse const &) = delete;
        void operator=(Mouse const &) = delete;
    };
}  // namespace OhEngine
