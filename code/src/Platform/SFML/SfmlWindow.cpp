/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <OhEngine/Utils/Precompiled.hpp>
#include <OhEngine/Window/Window.hpp>
#include <SFML/Graphics.hpp>

namespace OhEngine {
    /**
     * Class that implements the window itself.
     * This way we can hide the underlying windowing system and the user will not know about it.
     */
    class CWindow::CWindowImpl : private sf::RenderWindow {
    public:
        CWindowImpl(uint32_t uWidth, uint32_t uHeight, const std::string &strName, IEventListener &rEventsListener)
            : sf::RenderWindow(sf::VideoMode(uWidth, uHeight), strName)
            , m_rEventsListener{rEventsListener}
            , m_Sprite{} {
            this->setVerticalSyncEnabled(true);  // this will use the monitor's refresh rate

            // @todo: check the status of key pressed + mouse position on window startup

            // Update the EventState with the window's startup size
            CWindowResizeEvent event{uWidth, uHeight};
            EventState::Instance().HandleEvent(event);
            ResizeDrawArea(uWidth, uHeight);
        }

        void SetVSync(bool bEnable) {
            this->setVerticalSyncEnabled(bEnable);
        }

        void ProcessEvents() {
            sf::Event WindowEvent{};

            while (this->pollEvent(WindowEvent)) {
                if (sf::Event::EventType::Closed == WindowEvent.type) {
                    CWindowCloseEvent event{};
                    m_rEventsListener.OnEvent(event);
                } else if (sf::Event::EventType::Resized == WindowEvent.type) {
                    CWindowResizeEvent event{WindowEvent.size.width, WindowEvent.size.height};
                    ResizeDrawArea(WindowEvent.size.width, WindowEvent.size.height);
                    EventState::Instance().HandleEvent(event);
                    m_rEventsListener.OnEvent(event);
                } else if (sf::Event::EventType::KeyPressed == WindowEvent.type) {
                    CKeyPressedEvent event{Keyboard::ToScancode(WindowEvent.key.scancode),
                                           Keyboard::ToKeycode(WindowEvent.key.code),
                                           1,
                                           WindowEvent.key.alt,
                                           WindowEvent.key.shift,
                                           WindowEvent.key.control};
                    EventState::Instance().HandleEvent(event);
                    m_rEventsListener.OnEvent(event);
                } else if (sf::Event::EventType::KeyReleased == WindowEvent.type) {
                    CKeyReleasedEvent event{Keyboard::ToScancode(WindowEvent.key.scancode),
                                            Keyboard::ToKeycode(WindowEvent.key.code)};
                    EventState::Instance().HandleEvent(event);
                    m_rEventsListener.OnEvent(event);
                } else if (sf::Event::EventType::MouseButtonPressed == WindowEvent.type) {
                    CMouseBtnPressedEvent event{Mouse::ToButton(WindowEvent.mouseButton.button),
                                                static_cast<float>(WindowEvent.mouseButton.x),
                                                static_cast<float>(WindowEvent.mouseButton.y)};
                    EventState::Instance().HandleEvent(event);
                    m_rEventsListener.OnEvent(event);
                } else if (sf::Event::EventType::MouseButtonReleased == WindowEvent.type) {
                    CMouseBtnReleasedEvent event{Mouse::ToButton(WindowEvent.mouseButton.button),
                                                 static_cast<float>(WindowEvent.mouseButton.x),
                                                 static_cast<float>(WindowEvent.mouseButton.y)};
                    EventState::Instance().HandleEvent(event);
                    m_rEventsListener.OnEvent(event);
                } else if (sf::Event::EventType::MouseMoved == WindowEvent.type) {
                    CMouseMovedEvent event{static_cast<float>(WindowEvent.mouseMove.x),
                                           static_cast<float>(WindowEvent.mouseMove.y)};
                    EventState::Instance().HandleEvent(event);
                    m_rEventsListener.OnEvent(event);
                } else if (sf::Event::EventType::MouseWheelScrolled == WindowEvent.type) {
                    CMouseScrolledEvent event{static_cast<float>(WindowEvent.mouseWheelScroll.x),
                                              static_cast<float>(WindowEvent.mouseWheelScroll.y)};
                    m_rEventsListener.OnEvent(event);
                }
            }
        }

        void ClearBuffers() {
            this->clear(sf::Color::Black);
        }

        void SwapPixelBuffer(const uint8_t arPixelBuffer[]) {
            m_pDrawArea->update(arPixelBuffer);
            this->draw(m_Sprite);
        }

        void Show() {
            this->display();
        }

    private:
        IEventListener &m_rEventsListener;
        std::unique_ptr<sf::Texture> m_pDrawArea;
        sf::Sprite m_Sprite;

        void ResizeDrawArea(size_t uWidth, size_t uHeight) {
            m_pDrawArea = std::make_unique<sf::Texture>();
            m_pDrawArea->create(static_cast<uint32_t>(uWidth), static_cast<uint32_t>(uHeight));
            m_Sprite.setTexture(*m_pDrawArea);
        }
    };

    /*******************************************************************************************************************
     * Window facade class
     ******************************************************************************************************************/

    CWindow::CWindow(IEventListener &rEventsListener)
        : m_pImpl{std::make_unique<CWindowImpl>(800, 600, "blah", rEventsListener)} {
        m_bVSyncEnabled = true;
    }

    CWindow::~CWindow() = default;

    void CWindow::ProcessEvents() {
        m_pImpl->ProcessEvents();
    }

    void CWindow::SetVSync(bool bEnable) {
        //@todo: improve this vsync logic
        if (m_bVSyncEnabled != bEnable) {
            m_pImpl->SetVSync(bEnable);
            m_bVSyncEnabled = bEnable;
        }
    }

    void CWindow::ClearBuffers() {
        m_pImpl->ClearBuffers();
    }

    void CWindow::SwapPixelBuffer(const uint8_t arPixelBuffer[]) {
        m_pImpl->SwapPixelBuffer(arPixelBuffer);
    }

    void CWindow::Show() {
        m_pImpl->Show();
    }

    bool CWindow::IsVSyncEnabled() const {
        return m_bVSyncEnabled;
    }
}  // namespace OhEngine
