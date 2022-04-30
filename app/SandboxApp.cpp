#include <OhEngine/OhEngine.h>

class Sandbox : public OhEngine::Application {
public:
  Sandbox() {}
  ~Sandbox() {}
};

OhEngine::Application *OhEngine::CreateApplication() { return new Sandbox(); }