#include <OhEngine.hpp>

class CSample : public OhEngine::CApplication {
public:
    CSample() : OhEngine::CApplication() {}
    ~CSample() override = default;
};

OhEngine::CApplication *OhEngine::CreateApplication() {
    return new CSample();
}
