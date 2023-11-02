/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <Buffers.hpp>  // From src/Platform/Renderers/Softwaresrc/Platform/Renderers/Software
#include <OhEngine/Renderer/Renderer.hpp>

namespace OhEngine {

    class CRenderer::CRendererImpl {
    public:
        CRendererImpl(IDisplayArea &rDisplayArea)
            : m_rDisplayArea{rDisplayArea}
            , m_Buffer{EventState::GetWindowSize().uWidth, EventState::GetWindowSize().uHeight, EColorMode::RGBA} {}

        void Render(const CScene &Scene) {
            m_Buffer.Clear();
            DrawWireframe(Scene);  // This should change to CModel instead of scene

            m_rDisplayArea.ClearBuffers();
            m_rDisplayArea.SwapPixelBuffer(m_Buffer.Get().data());
            m_rDisplayArea.Show();
        }

        void OnResize(size_t uWidth, size_t uHeight) {
            m_Buffer.Resize(uWidth, uHeight);
        }

    private:
        IDisplayArea &m_rDisplayArea;
        CBuffer m_Buffer;

        void DrawWireframe(const CScene &Scene) {
            for (const auto &Triangle: Scene.Model().Triangles()) {
                auto v0 = Scene.Model().Vertices()[Triangle.v0];
                auto v1 = Scene.Model().Vertices()[Triangle.v1];
                auto v2 = Scene.Model().Vertices()[Triangle.v2];

                auto w = static_cast<float>(EventState::GetWindowSize().uWidth);
                auto h = static_cast<float>(EventState::GetWindowSize().uHeight);

                int x0 = static_cast<int>((v0.Coord().X + 1.f) * w / 2.f);
                int y0 = static_cast<int>((v0.Coord().Y + 1.f) * h / 2.f);

                int x1 = static_cast<int>((v1.Coord().X + 1.f) * w / 2.f);
                int y1 = static_cast<int>((v1.Coord().Y + 1.f) * h / 2.f);

                int x2 = static_cast<int>((v2.Coord().X + 1.f) * w / 2.f);
                int y2 = static_cast<int>((v2.Coord().Y + 1.f) * h / 2.f);

                DrawLine(x0, y0, x1, y1);
                DrawLine(x1, y1, x2, y2);
                DrawLine(x2, y2, x0, y0);
            }
        }

        void DrawLine(int x0, int y0, int x1, int y1) {
            bool steep = false;
            if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
                std::swap(x0, y0);
                std::swap(x1, y1);
                steep = true;
            }
            if (x0 > x1) {
                std::swap(x0, x1);
                std::swap(y0, y1);
            }
            int dx = x1 - x0;
            int dy = y1 - y0;
            int derror2 = std::abs(dy) * 2;
            int error2 = 0;
            int y = y0;
            for (int x = x0; x <= x1; x++) {
                if (steep) {
                    m_Buffer.Set(y, x);
                } else {
                    m_Buffer.Set(x, y);
                }
                error2 += derror2;
                if (error2 > dx) {
                    y += (y1 > y0 ? 1 : -1);
                    error2 -= dx * 2;
                }
            }
        }
    };

    /*******************************************************************************************************************
     * Renderer facade class
     ******************************************************************************************************************/

    CRenderer::CRenderer(IDisplayArea &rDisplayArea)
        : m_pImpl{std::make_unique<CRendererImpl>(rDisplayArea)} {}

    CRenderer::~CRenderer() = default;

    void CRenderer::OnResize(size_t uWidth, size_t uHeight) {
        m_pImpl->OnResize(uWidth, uHeight);
    }

    void CRenderer::Render(const CScene &Scene) {
        m_pImpl->Render(Scene);
    }
}  // namespace OhEngine
