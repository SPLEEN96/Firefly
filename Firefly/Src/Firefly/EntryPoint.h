#pragma once

#define FF_PLATFORM_LINUX
#ifdef FF_PLATFORM_LINUX

extern Firefly::Application* CreateApplication();

int main(){
    auto app =CreateApplication();
    app->Run();
    delete app;

    return 0;
}

#endif