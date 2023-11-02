/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

namespace OhEngine {
    class IDisplayArea {
    public:
        //
        virtual ~IDisplayArea() = default;
        virtual void ClearBuffers() = 0;
        // @todo: only if we are using the software renderer
        virtual void SwapPixelBuffer(const uint8_t arPixelBuffer[]) = 0;
        virtual void Show() = 0;
    };
}
