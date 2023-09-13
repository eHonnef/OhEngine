/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <OhEngine/Core/Input.hpp>

namespace OhEngine {

    /*******************************************************************************************************************
     * Keyboard: The keyboard implementation section
     ******************************************************************************************************************/

    constexpr std::string_view Keyboard::GetKeyScancodeDescription(Keyboard::KeyScancode Key) {
        // clang-format off
        switch (Key) {
            case KeyScancode::Unknown: return "Unknown";
            case KeyScancode::A: return "A";
            case KeyScancode::B: return "B";
            case KeyScancode::C: return "C";
            case KeyScancode::D: return "D";
            case KeyScancode::E: return "E";
            case KeyScancode::F: return "F";
            case KeyScancode::G: return "G";
            case KeyScancode::H: return "H";
            case KeyScancode::I: return "I";
            case KeyScancode::J: return "J";
            case KeyScancode::K: return "K";
            case KeyScancode::L: return "L";
            case KeyScancode::M: return "M";
            case KeyScancode::N: return "N";
            case KeyScancode::O: return "O";
            case KeyScancode::P: return "P";
            case KeyScancode::Q: return "Q";
            case KeyScancode::R: return "R";
            case KeyScancode::S: return "S";
            case KeyScancode::T: return "T";
            case KeyScancode::U: return "U";
            case KeyScancode::V: return "V";
            case KeyScancode::W: return "W";
            case KeyScancode::X: return "X";
            case KeyScancode::Y: return "Y";
            case KeyScancode::Z: return "Z";
            case KeyScancode::Num1: return "Num1";
            case KeyScancode::Num2: return "Num2";
            case KeyScancode::Num3: return "Num3";
            case KeyScancode::Num4: return "Num4";
            case KeyScancode::Num5: return "Num5";
            case KeyScancode::Num6: return "Num6";
            case KeyScancode::Num7: return "Num7";
            case KeyScancode::Num8: return "Num8";
            case KeyScancode::Num9: return "Num9";
            case KeyScancode::Num0: return "Num0";
            case KeyScancode::Enter: return "Enter";
            case KeyScancode::Escape: return "Escape";
            case KeyScancode::Backspace: return "Backspace";
            case KeyScancode::Tab: return "Tab";
            case KeyScancode::Space: return "Space";
            case KeyScancode::Hyphen: return "Hyphen";
            case KeyScancode::Equal: return "Equal";
            case KeyScancode::LBracket: return "LBracket";
            case KeyScancode::RBracket: return "RBracket";
            case KeyScancode::Backslash: return "Backslash";
            case KeyScancode::Semicolon: return "Semicolon";
            case KeyScancode::Apostrophe: return "Apostrophe";
            case KeyScancode::Grave: return "Grave";
            case KeyScancode::Comma: return "Comma";
            case KeyScancode::Period: return "Period";
            case KeyScancode::Slash: return "Slash";
            case KeyScancode::F1: return "F1";
            case KeyScancode::F2: return "F2";
            case KeyScancode::F3: return "F3";
            case KeyScancode::F4: return "F4";
            case KeyScancode::F5: return "F5";
            case KeyScancode::F6: return "F6";
            case KeyScancode::F7: return "F7";
            case KeyScancode::F8: return "F8";
            case KeyScancode::F9: return "F9";
            case KeyScancode::F10: return "F10";
            case KeyScancode::F11: return "F11";
            case KeyScancode::F12: return "F12";
            case KeyScancode::F13: return "F13";
            case KeyScancode::F14: return "F14";
            case KeyScancode::F15: return "F15";
            case KeyScancode::F16: return "F16";
            case KeyScancode::F17: return "F17";
            case KeyScancode::F18: return "F18";
            case KeyScancode::F19: return "F19";
            case KeyScancode::F20: return "F20";
            case KeyScancode::F21: return "F21";
            case KeyScancode::F22: return "F22";
            case KeyScancode::F23: return "F23";
            case KeyScancode::F24: return "F24";
            case KeyScancode::CapsLock: return "CapsLock";
            case KeyScancode::PrintScreen: return "PrintScreen";
            case KeyScancode::ScrollLock: return "ScrollLock";
            case KeyScancode::Pause: return "Pause";
            case KeyScancode::Insert: return "Insert";
            case KeyScancode::Home: return "Home";
            case KeyScancode::PageUp: return "PageUp";
            case KeyScancode::Delete: return "Delete";
            case KeyScancode::End: return "End";
            case KeyScancode::PageDown: return "PageDown";
            case KeyScancode::Right: return "Right";
            case KeyScancode::Left: return "Left";
            case KeyScancode::Down: return "Down";
            case KeyScancode::Up: return "Up";
            case KeyScancode::NumLock: return "NumLock";
            case KeyScancode::NumpadDivide: return "NumpadDivide";
            case KeyScancode::NumpadMultiply: return "NumpadMultiply";
            case KeyScancode::NumpadMinus: return "NumpadMinus";
            case KeyScancode::NumpadPlus: return "NumpadPlus";
            case KeyScancode::NumpadEqual: return "NumpadEqual";
            case KeyScancode::NumpadEnter: return "NumpadEnter";
            case KeyScancode::NumpadDecimal: return "NumpadDecimal";
            case KeyScancode::Numpad1: return "Numpad1";
            case KeyScancode::Numpad2: return "Numpad2";
            case KeyScancode::Numpad3: return "Numpad3";
            case KeyScancode::Numpad4: return "Numpad4";
            case KeyScancode::Numpad5: return "Numpad5";
            case KeyScancode::Numpad6: return "Numpad6";
            case KeyScancode::Numpad7: return "Numpad7";
            case KeyScancode::Numpad8: return "Numpad8";
            case KeyScancode::Numpad9: return "Numpad9";
            case KeyScancode::Numpad0: return "Numpad0";
            case KeyScancode::NonUsBackslash: return "NonUsBackslash";
            case KeyScancode::Application: return "Application";
            case KeyScancode::Execute: return "Execute";
            case KeyScancode::ModeChange: return "ModeChange";
            case KeyScancode::Help: return "Help";
            case KeyScancode::Menu: return "Menu";
            case KeyScancode::Select: return "Select";
            case KeyScancode::Redo: return "Redo";
            case KeyScancode::Undo: return "Undo";
            case KeyScancode::Cut: return "Cut";
            case KeyScancode::Copy: return "Copy";
            case KeyScancode::Paste: return "Paste";
            case KeyScancode::VolumeMute: return "VolumeMute";
            case KeyScancode::VolumeUp: return "VolumeUp";
            case KeyScancode::VolumeDown: return "VolumeDown";
            case KeyScancode::MediaPlayPause: return "MediaPlayPause";
            case KeyScancode::MediaStop: return "MediaStop";
            case KeyScancode::MediaNextTrack: return "MediaNextTrack";
            case KeyScancode::MediaPreviousTrack: return "MediaPreviousTrack";
            case KeyScancode::LControl: return "LControl";
            case KeyScancode::LShift: return "LShift";
            case KeyScancode::LAlt: return "LAlt";
            case KeyScancode::LSystem: return "LSystem";
            case KeyScancode::RControl: return "RControl";
            case KeyScancode::RShift: return "RShift";
            case KeyScancode::RAlt: return "RAlt";
            case KeyScancode::RSystem: return "RSystem";
            case KeyScancode::Back: return "Back";
            case KeyScancode::Forward: return "Forward";
            case KeyScancode::Refresh: return "Refresh";
            case KeyScancode::Stop: return "Stop";
            case KeyScancode::Search: return "Search";
            case KeyScancode::Favorites: return "Favorites";
            case KeyScancode::HomePage: return "HomePage";
            case KeyScancode::LaunchApplication1: return "LaunchApplication1";
            case KeyScancode::LaunchApplication2: return "LaunchApplication2";
            case KeyScancode::LaunchMail: return "LaunchMail";
            case KeyScancode::LaunchMediaSelect: return "LaunchMediaSelect";
            case KeyScancode::ScancodeCount: return "Unknown"; // Not handled
        }
        // clang-format on
        return "Unknown";
    }

    constexpr std::string_view Keyboard::GetKeyDescription(Keyboard::Key Key) {
        // clang-format off
        switch (Key) {
            case Key::Unknown: return "Unknown";
            case Key::A: return "A";
            case Key::B: return "B";
            case Key::C: return "C";
            case Key::D: return "D";
            case Key::E: return "E";
            case Key::F: return "F";
            case Key::G: return "G";
            case Key::H: return "H";
            case Key::I: return "I";
            case Key::J: return "J";
            case Key::K: return "K";
            case Key::L: return "L";
            case Key::M: return "M";
            case Key::N: return "N";
            case Key::O: return "O";
            case Key::P: return "P";
            case Key::Q: return "Q";
            case Key::R: return "R";
            case Key::S: return "S";
            case Key::T: return "T";
            case Key::U: return "U";
            case Key::V: return "V";
            case Key::W: return "W";
            case Key::X: return "X";
            case Key::Y: return "Y";
            case Key::Z: return "Z";
            case Key::Num0: return "Num0";
            case Key::Num1: return "Num1";
            case Key::Num2: return "Num2";
            case Key::Num3: return "Num3";
            case Key::Num4: return "Num4";
            case Key::Num5: return "Num5";
            case Key::Num6: return "Num6";
            case Key::Num7: return "Num7";
            case Key::Num8: return "Num8";
            case Key::Num9: return "Num9";
            case Key::Escape: return "Escape";
            case Key::LControl: return "LControl";
            case Key::LShift: return "LShift";
            case Key::LAlt: return "LAlt";
            case Key::LSystem: return "LSystem";
            case Key::RControl: return "RControl";
            case Key::RShift: return "RShift";
            case Key::RAlt: return "RAlt";
            case Key::RSystem: return "RSystem";
            case Key::Menu: return "Menu";
            case Key::LBracket: return "LBracket";
            case Key::RBracket: return "RBracket";
            case Key::Semicolon: return "Semicolon";
            case Key::Comma: return "Comma";
            case Key::Period: return "Period";
            case Key::Apostrophe: return "Apostrophe";
            case Key::Slash: return "Slash";
            case Key::Backslash: return "Backslash";
            case Key::Grave: return "Grave";
            case Key::Equal: return "Equal";
            case Key::Hyphen: return "Hyphen";
            case Key::Space: return "Space";
            case Key::Enter: return "Enter";
            case Key::Backspace: return "Backspace";
            case Key::Tab: return "Tab";
            case Key::PageUp: return "PageUp";
            case Key::PageDown: return "PageDown";
            case Key::End: return "End";
            case Key::Home: return "Home";
            case Key::Insert: return "Insert";
            case Key::Delete: return "Delete";
            case Key::Add: return "Add";
            case Key::Subtract: return "Subtract";
            case Key::Multiply: return "Multiply";
            case Key::Divide: return "Divide";
            case Key::Left: return "Left";
            case Key::Right: return "Right";
            case Key::Up: return "Up";
            case Key::Down: return "Down";
            case Key::Numpad0: return "Numpad0";
            case Key::Numpad1: return "Numpad1";
            case Key::Numpad2: return "Numpad2";
            case Key::Numpad3: return "Numpad3";
            case Key::Numpad4: return "Numpad4";
            case Key::Numpad5: return "Numpad5";
            case Key::Numpad6: return "Numpad6";
            case Key::Numpad7: return "Numpad7";
            case Key::Numpad8: return "Numpad8";
            case Key::Numpad9: return "Numpad9";
            case Key::F1: return "F1";
            case Key::F2: return "F2";
            case Key::F3: return "F3";
            case Key::F4: return "F4";
            case Key::F5: return "F5";
            case Key::F6: return "F6";
            case Key::F7: return "F7";
            case Key::F8: return "F8";
            case Key::F9: return "F9";
            case Key::F10: return "F10";
            case Key::F11: return "F11";
            case Key::F12: return "F12";
            case Key::F13: return "F13";
            case Key::F14: return "F14";
            case Key::F15: return "F15";
            case Key::Pause: return "Pause";
            case Key::KeyCount: return "Unknown"; // Unhandled
        }
        // clang-format on
        return "Unknown";
    }

    /*******************************************************************************************************************
     * Mouse: The mouse implementation section
     ******************************************************************************************************************/

    constexpr std::string_view Mouse::GetButtonDescription(Mouse::Button Btn) {
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
}
