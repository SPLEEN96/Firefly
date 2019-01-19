#pragma once
#include "Firefly.h"

namespace Firefly {

class Application {
  public:
    Application();
    virtual ~Application();

    void Run();
};

Application *CreateApplication();

} // namespace Firefly