#pragma once

int main() {
    auto app = OhEngine::CreateApplication();
    app->Run();
    delete app;
    return 0;
}
