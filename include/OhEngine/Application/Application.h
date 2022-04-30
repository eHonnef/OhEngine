#pragma once

namespace OhEngine {

class Application {
public:
  Application();
  virtual ~Application();

  void run();
};

// Client will define
Application *CreateApplication();

} // namespace OhEngine
