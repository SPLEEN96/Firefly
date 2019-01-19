//#include "../Firefly.h"
#include "Application.h"
#include "Logger.h"
#include <iostream>

//#define FF_PLATFORM_LINUX
//#ifdef FF_PLATFORM_LINUX

extern Firefly::Application *CreateApplication();

int main() {
    Firefly::Logger::Init();
    int    a = 4;
    double b = 4.5;
    char   c = 'c';
    FFLY_LOG_CORE_TRACE("twagalala {0}{1}{2}", a, b, c);
    FFLY_LOG_CORE_WARN("pas tro twag u knoow{0}", b);
    FFLY_LOG_CORE_ERROR("PAS TWAG PAS TWAG D:{0}", a);
    FFLY_LOG_CORE_CRITICAL("DDDDDD:{0}", a);

    FFLY_LOG_APP_TRACE("twagalala{0}", a);
    FFLY_LOG_APP_WARN("pas tro twag u knoow{0}", a);
    FFLY_LOG_APP_ERROR("PAS TWAG PAS TWAG D:{0}", a);
    FFLY_LOG_APP_CRITICAL("DDDDDD:{0}", a);
    auto app = CreateApplication();
    app->Run();
    delete app;

    return 0;
}

//#endif