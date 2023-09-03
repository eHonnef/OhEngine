/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <OhEngine/Window/Window.hpp>
#include <SFML/Graphics.hpp>

namespace OhEngine {
    /**
     * Class that implements the window itself.
     * This way we can hide the underlying windowing system and the user doesn't need to compile it himself.
     */
    class CWindow::CWindowImpl : private sf::RenderWindow {
    private:
        IEventListener &m_EventsListener;

    public:
        CWindowImpl(unsigned int uWidth, unsigned int uHeight, const std::string &strName,
                    IEventListener &EventsListener) :
            sf::RenderWindow(sf::VideoMode(uWidth, uHeight), strName),
            m_EventsListener{EventsListener} {
            this->setVerticalSyncEnabled(true);  // this will use the monitor's refresh rate

            // @todo: check the status of key pressed + mouse position on window startup
        }

        void SetVSync(bool bEnable) {
            this->setVerticalSyncEnabled(bEnable);
        }

        void Update() {
            sf::CircleShape shape(100.f);
            shape.setFillColor(sf::Color::Green);

            sf::Event WindowEvent{};
            while (this->pollEvent(WindowEvent)) {
                if (WindowEvent.type == sf::Event::EventType::Closed) {
                    CWindowCloseEvent event{};
                    m_EventsListener.OnEvent(event);
                } else if (WindowEvent.type == sf::Event::EventType::Resized) {
                    CWindowResizeEvent event{WindowEvent.size.width, WindowEvent.size.height};
                    m_EventsListener.OnEvent(event);
                } else if (WindowEvent.type == sf::Event::EventType::KeyPressed) {
                    CKeyPressedEvent event{Keyboard::ToScancode(WindowEvent.key.scancode),
                                           Keyboard::ToKeycode(WindowEvent.key.code),
                                           1,
                                           WindowEvent.key.alt,
                                           WindowEvent.key.shift,
                                           WindowEvent.key.control};
                    EventState::Instance().HandleEvent(event);
                    m_EventsListener.OnEvent(event);
                } else if (WindowEvent.type == sf::Event::EventType::KeyReleased) {
                    CKeyReleasedEvent event{Keyboard::ToScancode(WindowEvent.key.scancode),
                                            Keyboard::ToKeycode(WindowEvent.key.code)};
                    EventState::Instance().HandleEvent(event);
                    m_EventsListener.OnEvent(event);
                } else if (WindowEvent.type == sf::Event::EventType::MouseButtonPressed) {
                    CMouseBtnPressedEvent event{Mouse::ToButton(WindowEvent.mouseButton.button),
                                                static_cast<float>(WindowEvent.mouseButton.x),
                                                static_cast<float>(WindowEvent.mouseButton.y)};
                    EventState::Instance().HandleEvent(event);
                    m_EventsListener.OnEvent(event);
                } else if (WindowEvent.type == sf::Event::EventType::MouseButtonReleased) {
                    CMouseBtnReleasedEvent event{Mouse::ToButton(WindowEvent.mouseButton.button),
                                                 static_cast<float>(WindowEvent.mouseButton.x),
                                                 static_cast<float>(WindowEvent.mouseButton.y)};
                    EventState::Instance().HandleEvent(event);
                    m_EventsListener.OnEvent(event);
                } else if (WindowEvent.type == sf::Event::EventType::MouseMoved) {
                    CMouseMovedEvent event{static_cast<float>(WindowEvent.mouseMove.x),
                                           static_cast<float>(WindowEvent.mouseMove.y)};
                    EventState::Instance().HandleEvent(event);
                    m_EventsListener.OnEvent(event);
                } else if (WindowEvent.type == sf::Event::EventType::MouseWheelScrolled) {
                    CMouseScrolledEvent event{static_cast<float>(WindowEvent.mouseWheelScroll.x),
                                              static_cast<float>(WindowEvent.mouseWheelScroll.y)};
                    m_EventsListener.OnEvent(event);
                }
            }
            this->clear();
            this->draw(shape);
            this->display();
        }
    };

    /*******************************************************************************************************************
     * Window facade class
     ******************************************************************************************************************/

    CWindow::CWindow(IEventListener &EventsListener) :
        m_EventsListener{EventsListener}, m_pImpl{std::make_unique<CWindowImpl>(800, 600, "blah", EventsListener)} {
        m_bVSyncEnabled = true;
    }

    CWindow::~CWindow() = default;

    void CWindow::Update() {
        m_pImpl->Update();
    }

    void CWindow::SetVSync(bool bEnable) {
        if (m_bVSyncEnabled != bEnable) {
            m_pImpl->SetVSync(bEnable);
            m_bVSyncEnabled = bEnable;
        }
    }
}  // namespace OhEngine
