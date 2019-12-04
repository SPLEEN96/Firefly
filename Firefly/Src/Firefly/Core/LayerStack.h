#pragma once

#include "Core/Layer.h"
#include "PCH_CORE.h"

namespace Firefly {

typedef std::vector<Layer*> Stack;

/* The class act has a stack even though it is a wrapper of a Vector */
class LayerStack {
  public:
    LayerStack();
    ~LayerStack();

    void PushLayer(Layer* layer);
    void PushOverlay(Layer* overlay);
    void PopLayer(Layer* layer);
    void PopOverlay(Layer* overlay);

    Stack::iterator Begin() { return m_layers.begin(); }
    Stack::iterator End() { return m_layers.end(); }

    Stack::const_iterator Begin() const { return m_layers.begin(); }
    Stack::const_iterator End() const { return m_layers.end(); }

  private:
    Stack  m_layers;
    uint32 m_top_index;
};
} // namespace Firefly
