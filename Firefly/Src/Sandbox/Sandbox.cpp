#include "PCH_CORE.h"
#include "Firefly.h"

class Sandbox : public Firefly::Application {
  public:
    Sandbox() {}
    ~Sandbox() {}
};

Firefly::Application *CreateApplication() {
    return new Sandbox();
}