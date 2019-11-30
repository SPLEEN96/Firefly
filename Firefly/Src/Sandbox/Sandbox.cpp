#include "PCH_CORE.h"
#include "FFLY_CORE.h"
#include "Core/Application.h"

class Sandbox : public Firefly::Application {
  public:
    Sandbox() {}
    ~Sandbox() {}
};

Firefly::Application *CreateApplication() {
    return new Sandbox();
}