/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <OhEngine/Utils/Precompiled.hpp>

namespace OhEngine {
    enum class EColorMode : uint8_t {
        // Grayscale=1,
        // RGB=3,
        RGBA = 4  // There is no reason for the others now, SFML uses RGBA
    };

    class CBuffer {
    public:
        CBuffer(size_t uWidth, size_t uHeight, EColorMode eColorMode)
            : m_uColorMode{static_cast<uint8_t>(eColorMode)}
            , m_Array(uWidth * uHeight * m_uColorMode) {}

        ~CBuffer() = default;

        void Clear() {
            std::memset(m_Array.data(), 130, m_Array.size());
        }

        void Resize(size_t uWidth, size_t uHeight) {
            m_Array.resize(uWidth * uHeight * m_uColorMode);
        }

        const TVector<uint8_t> &Get() const {
            return m_Array;
        }

        void Set(int nX, int nY) {
            auto nWidth = static_cast<int>(EventState::GetWindowSize().uWidth);
            auto nHeight = static_cast<int>(EventState::GetWindowSize().uHeight);
            if (nX < 0 || nY < 0 || nX >= nWidth || nY >= nHeight) return;

            auto nOffset = static_cast<size_t>((nX + nY * nWidth) * m_uColorMode);
            if (nOffset < m_Array.size()) {
                uint8_t arColor[] = {255, 255, 255, 255};
                //
                std::memcpy(m_Array.data() + nOffset, arColor, m_uColorMode);
            } else {
                Logger::Error("Would result in out of bounds");
            }
        }

    private:
        uint8_t m_uColorMode;
        TVector<uint8_t> m_Array;
    };
}  // namespace OhEngine
