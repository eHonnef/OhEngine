/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <OhEngine/Events/Input.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace OhEngine {
    /**
     * Static class that will translate the window's input to our input.
     */
    class CTranslatorImpl {
    public:
        static Keyboard::KeyScancode GetScancode(Keyboard::Key Key) {
            // We don't need to make the gigantic map because we are using the same enumerator as SFML
            return static_cast<Keyboard::KeyScancode>(sf::Keyboard::delocalize(static_cast<sf::Keyboard::Key>(Key)));
        }

        static Keyboard::Key GetKeycode(Keyboard::KeyScancode Key) {
            // We don't need to make the gigantic map because we are using the same enumerator as SFML
            return static_cast<Keyboard::Key>(sf::Keyboard::localize(static_cast<sf::Keyboard::Scancode>(Key)));
        }

        static Keyboard::Key ToKeycode(int nKey) {
            // We can directly cast to our enumerator since we are using the same as SFML
            return static_cast<Keyboard::Key>(nKey);
        }

        static Keyboard::KeyScancode ToScancode(int nKeyScancode) {
            // We can directly cast to our enumerator since we are using the same as SFML
            return static_cast<Keyboard::KeyScancode>(nKeyScancode);
        }

        static Mouse::Button ToButton(int nButton) {
            // We can directly cast to our enumerator since we are using the same as SFML
            return static_cast<Mouse::Button>(nButton);
        }
    };

    /*******************************************************************************************************************
     * Keyboard: The keyboard implementation section
     ******************************************************************************************************************/

    Keyboard::KeyScancode Keyboard::ToScancode(Key key) {
        return CTranslatorImpl::GetScancode(key);
    }

    Keyboard::Key Keyboard::ToKeycode(KeyScancode keyScancode) {
        return CTranslatorImpl::GetKeycode(keyScancode);
    }

    Keyboard::KeyScancode Keyboard::ToScancode(int nKeyScancode) {
        return (nKeyScancode >= static_cast<int>(KeyScancode::ScancodeCount) || nKeyScancode < 0)
                 ? KeyScancode::Unknown
                 : CTranslatorImpl::ToScancode(nKeyScancode);
    }

    Keyboard::Key Keyboard::ToKeycode(int nKey) {
        return (nKey >= static_cast<int>(Key::KeyCount) || nKey < 0) ? Key::Unknown : CTranslatorImpl::ToKeycode(nKey);
    }

    std::string_view Keyboard::GetKeyDescription(Keyboard::KeyScancode Key) {
        // @todo: the "to_string" of a key
        (void) Key;
        return std::string_view{};
    }

    /*******************************************************************************************************************
     * Mouse: The mouse implementation section
     ******************************************************************************************************************/

    Mouse::Button Mouse::ToButton(int nButton) {
        return (nButton >= static_cast<int>(Button::ButtonCount) || nButton < 0) ? Button::Unknown
                                                                                 : CTranslatorImpl::ToButton(nButton);
    }

    std::string_view Mouse::GetButtonDescription(Mouse::Button Btn) {
        switch (Btn) {
            case Mouse::Button::Left:
                return "MouseButton_Left";
            case Mouse::Button::Right:
                return "MouseButton_Right";
            case Mouse::Button::Middle:
                return "MouseButton_Middle";
            case Mouse::Button::XButton1:
                return "MouseButton_XButton_1";
            case Mouse::Button::XButton2:
                return "MouseButton_XButton_2";
            default:
                return "MouseButton_UNK";
        }
    }

}  // namespace OhEngine
