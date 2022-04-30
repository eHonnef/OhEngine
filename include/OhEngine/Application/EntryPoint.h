#pragma once

#define UNUSED(x) (void)(x)

#include "Application.h"

extern OhEngine::Application *OhEngine::CreateApplication();

int main(int argc, char const *argv[]) {
  UNUSED(argc);
  UNUSED(argv);

  auto app = OhEngine::CreateApplication();
  app->run();
  delete app;
  return 0;
}
