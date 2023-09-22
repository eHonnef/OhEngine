/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once


namespace OhEngine {
    // @todo: This class should be like a facade for other kind of buffers
    // @todo: Clean this class
    class CBuffer {
    public:
        CBuffer()
            : m_uColorSize{4}
            , m_arBuffer{std::make_unique<uint8_t[]>(EventState::GetWindowSize().uWidth *
                                                     EventState::GetWindowSize().uHeight * m_uColorSize)} {}

        void Clear() {
            std::memset(m_arBuffer.get(), 0,
                        EventState::GetWindowSize().uWidth * EventState::GetWindowSize().uHeight * m_uColorSize);
        }

        void Resize(size_t uWidth, size_t uHeight) {
            m_arBuffer.reset(new uint8_t[uWidth * uHeight * m_uColorSize]);
        }

        void Set(int x, int y) {
            if (x < 0 || y < 0 || x >= static_cast<int>(EventState::GetWindowSize().uWidth) || y >= static_cast<int>(EventState::GetWindowSize().uHeight))
                return;

            uint8_t color[] = {255, 255, 255, 255};
            std::memcpy(m_arBuffer.get() + (static_cast<size_t>(x) + static_cast<size_t>(y) * EventState::GetWindowSize().uWidth) * m_uColorSize, color, m_uColorSize);
        }

        const uint8_t* Buffer() const {
            return m_arBuffer.get();
        }

    private:
        uint32_t m_uColorSize;
        std::unique_ptr<uint8_t[]> m_arBuffer;
    };
}  // namespace OhEngine
