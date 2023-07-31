#include <OhEngine/Application.hpp>
#include <OhEngine/Utils/Logger.hpp>

namespace OhEngine {

CApplication::CApplication() {}

CApplication::~CApplication() {}

void CApplication::Run() {
    TRACE("running here {} with some formatting", 1324);
    DEBUG("running here {} with some formatting", 1324);
    INFO("running here {} with some formatting", 1324);
    IMPORTANT("running here {} with some formatting", 1324);
    WARNING("running here {} with some formatting", 1324);
    ERROR("running here {} with some formatting", 1324);
    CRITICAL("running here {} with some formatting", 1324);
    FATAL("running here {} with some formatting", 1324);

    // while (true) {
    //     continue;
    // }
}

}; // namespace OhEngine
