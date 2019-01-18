
#pragma once

namespace Firefly {

class Application {
   public:
    Application();
    virtual ~Application();

    void Run();
};

Application* CreateApplication();

}  // namespace Firefly