/* Temporary class */
#include "Events/Event.h"
#include "Events/KeyEvents.h"
#include "Events/MouseEvents.h"
#include "Platform/imgui_opengl.h"
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>

namespace Firefly {
class GUI {
  public:
    GUI();
    ~GUI();
    void OnUpdate(int screen_width, int screen_height);
    void OnEvent(Event& e);

  private:
    //bool OnMouseButtonPressedEvent(Event* e);
    bool OnMouseButtonReleasedEvent(const MouseButtonReleasedEvent& e);
    bool OnMouseMovedEvent(const MouseMovedEvent& e);
    bool OnKeyPressedEvent(const KeyPressedEvent& e);
    bool OnKeyReleasedEvent(const KeyReleasedEvent& e);
    bool OnKeyTypedEvent(const KeyEvent& e);
};
} // namespace Firefly