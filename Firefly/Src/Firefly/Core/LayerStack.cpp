#include "Core/LayerStack.h"

namespace Firefly {

LayerStack::LayerStack() {
    m_top_index = 0;
}
LayerStack::~LayerStack() {
    for (Layer* layer : m_layers) {
        layer->OnDetach();
        delete layer;
    }
}

void LayerStack::PushLayer(Layer* layer) {
    m_layers.insert(this->Begin() + m_top_index, layer);

    m_top_index++;
    layer->OnAttach();
}
void LayerStack::PushOverlay(Layer* overlay) {
    m_layers.push_back(overlay);
    overlay->OnAttach();
}
void LayerStack::PopLayer(Layer* layer) {
    auto it = std::find(this->Begin(), this->Begin() + m_top_index, layer);
    if (it != this->Begin() + m_top_index) {
        layer->OnDetach();
        m_layers.erase(it);
        m_top_index--;
    }
}
void LayerStack::PopOverlay(Layer* overlay) {
    auto it = std::find(this->Begin() + m_top_index, this->End(), overlay);
    if (it != this->End()) {
        overlay->OnDetach();
        m_layers.erase(it);
    }
}

} // namespace Firefly