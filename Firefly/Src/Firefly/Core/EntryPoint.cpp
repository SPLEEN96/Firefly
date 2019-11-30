#include "FFLY_CORE.h"
#include "Core/Application.h"
#include "PCH_CORE.h"

//#define FF_PLATFORM_LINUX
//#ifdef FF_PLATFORM_LINUX

extern Firefly::Application* CreateApplication();

int main() {
    Firefly::Logger::Init();

    auto app = CreateApplication();
    app->Run();
    delete app;

    return 0;
}

//#endif

