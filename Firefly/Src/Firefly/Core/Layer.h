#pragma once
#include "Events/Event.h"
#include "FFLY_CORE.h"

namespace Firefly {

class Layer {
  public:
    Layer(const char* name = "Layer") : m_name(name) {}
    virtual ~Layer() {}

    virtual void OnAttach() {}
    virtual void OnDetach() {}
    virtual void OnUpdate() {}
    virtual void OnImGuiDraw() {}
    virtual void OnEvent(Event& event) {}

    const char* GetName() const { return m_name; }

  protected:
    const char* m_name;
};
} // namespace Firefly
