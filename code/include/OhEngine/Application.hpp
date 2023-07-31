#pragma once

#include <OhEngine/Window/Events.hpp>

namespace OhEngine {
class CApplication : IWindowEvents {
  public:
    CApplication();
    virtual ~CApplication();

    void Run();
};

CApplication *CreateApplication();
}; // namespace OhEngine
