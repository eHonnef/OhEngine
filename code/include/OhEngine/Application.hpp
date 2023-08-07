#pragma once

#include "OhEngine/Window/Window.hpp"

namespace OhEngine {
    class CApplication : IEventListener {
    public:
        CApplication();
        virtual ~CApplication() override;

        void Run();

    protected:
        [[maybe_unused]] static constexpr bool LOG_MODULE = true || ENABLE_ALL_LOGS;

        bool m_bRunning;

        void OnEvent(CEvent& Event) override;
        bool OnWindowClose(CWindowCloseEvent &e);
        bool OnMouseMove(CMouseMovedEvent &e);
    };

    CApplication *CreateApplication();
};  // namespace OhEngine
