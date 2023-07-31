#pragma once

extern OhEngine::CApplication *OhEngine::CreateApplication();

int main() {
    auto app = OhEngine::CreateApplication();
    app->Run();
    delete app;
    return 0;
}
