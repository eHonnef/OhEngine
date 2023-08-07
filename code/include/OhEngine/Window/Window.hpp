#pragma once

#include <OhEngine/Events/Events.hpp>
#include <OhEngine/Utils/Logger.hpp>

namespace OhEngine {
    class CWindow {
    public:
        explicit CWindow(IEventListener &EventsListener);
        virtual ~CWindow();

        void Update();
        void SetVSync(bool bEnable);

        [[nodiscard]] inline bool IsVSyncEnabled() const {
            return m_bVSyncEnabled;
        }

    private:
        static constexpr bool LOG_MODULE = true || ENABLE_ALL_LOGS;

        [[maybe_unused]] IEventListener &m_EventsListener;

        bool m_bVSyncEnabled;

        class CWindowImpl;
        std::unique_ptr<CWindowImpl> m_pImpl;
    };
} // namespace OhEngine
