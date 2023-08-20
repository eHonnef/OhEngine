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
    };

    /*******************************************************************************************************************
     * Keyboard: The keyboard implementation section
     ******************************************************************************************************************/

    Keyboard::KeyScancode Keyboard::GetScancode(Keyboard::Key key) {
        return CTranslatorImpl::GetScancode(key);
    }

    Keyboard::Key Keyboard::GetKeycode(Keyboard::KeyScancode keyScancode) {
        return CTranslatorImpl::GetKeycode(keyScancode);
    }

    Keyboard::KeyScancode Keyboard::ToScancode(int nKeyScancode) {
        return CTranslatorImpl::ToScancode(nKeyScancode);
    }

    Keyboard::Key Keyboard::ToKeycode(int nKey) {
        return CTranslatorImpl::ToKeycode(nKey);
    }

    std::string_view Keyboard::GetKeyDescription(Keyboard::KeyScancode Key) {
        // @todo: the "to_string" of a key
        (void) Key;
        return std::string_view{};
    }
}  // namespace OhEngine
