#include <OhEngine/Window/Window.hpp>
#include <SFML/Graphics.hpp>

namespace OhEngine {
    class CWindow::CWindowImpl : private sf::RenderWindow {
    private:
        IEventListener &m_EventsListener;

    public:
        CWindowImpl(unsigned int uWidth, unsigned int uHeight, const std::string &strName,
                    IEventListener &EventsListener) :
            sf::RenderWindow(sf::VideoMode(uWidth, uHeight), strName),
            m_EventsListener{EventsListener} {
            this->setVerticalSyncEnabled(true);  // this will use the monitor's refresh rate
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
                    CKeyPressedEvent event{WindowEvent.key.scancode, WindowEvent.key.code,  1,
                                           WindowEvent.key.alt,      WindowEvent.key.shift, WindowEvent.key.control};
                    m_EventsListener.OnEvent(event);
                } else if (WindowEvent.type == sf::Event::EventType::KeyReleased) {
                    CKeyReleasedEvent event{WindowEvent.key.scancode, WindowEvent.key.code};
                    m_EventsListener.OnEvent(event);
                } else if (WindowEvent.type == sf::Event::EventType::MouseButtonPressed) {
                    CMouseBtnPressedEvent event{WindowEvent.mouseButton.button,
                                                static_cast<float>(WindowEvent.mouseButton.x),
                                                static_cast<float>(WindowEvent.mouseButton.y)};
                    m_EventsListener.OnEvent(event);
                } else if (WindowEvent.type == sf::Event::EventType::MouseButtonReleased) {
                    CMouseBtnReleasedEvent event{WindowEvent.mouseButton.button,
                                                 static_cast<float>(WindowEvent.mouseButton.x),
                                                 static_cast<float>(WindowEvent.mouseButton.y)};
                    m_EventsListener.OnEvent(event);
                } else if (WindowEvent.type == sf::Event::EventType::MouseMoved) {
                    CMouseMovedEvent event{static_cast<float>(WindowEvent.mouseMove.x),
                                           static_cast<float>(WindowEvent.mouseMove.y)};
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
