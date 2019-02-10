#include "FFLYImgui.h"

namespace Firefly {
GUI::GUI() {
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGuiIO& io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

    io.KeyMap[ImGuiKey_Tab]        = GLFW_KEY_TAB;
    io.KeyMap[ImGuiKey_LeftArrow]  = GLFW_KEY_LEFT;
    io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
    io.KeyMap[ImGuiKey_UpArrow]    = GLFW_KEY_UP;
    io.KeyMap[ImGuiKey_DownArrow]  = GLFW_KEY_DOWN;
    io.KeyMap[ImGuiKey_PageUp]     = GLFW_KEY_PAGE_UP;
    io.KeyMap[ImGuiKey_PageDown]   = GLFW_KEY_PAGE_DOWN;
    io.KeyMap[ImGuiKey_Home]       = GLFW_KEY_HOME;
    io.KeyMap[ImGuiKey_End]        = GLFW_KEY_END;
    io.KeyMap[ImGuiKey_Insert]     = GLFW_KEY_INSERT;
    io.KeyMap[ImGuiKey_Delete]     = GLFW_KEY_DELETE;
    io.KeyMap[ImGuiKey_Backspace]  = GLFW_KEY_BACKSPACE;
    io.KeyMap[ImGuiKey_Space]      = GLFW_KEY_SPACE;
    io.KeyMap[ImGuiKey_Enter]      = GLFW_KEY_ENTER;
    io.KeyMap[ImGuiKey_Escape]     = GLFW_KEY_ESCAPE;
    io.KeyMap[ImGuiKey_A]          = GLFW_KEY_A;
    io.KeyMap[ImGuiKey_C]          = GLFW_KEY_C;
    io.KeyMap[ImGuiKey_V]          = GLFW_KEY_V;
    io.KeyMap[ImGuiKey_X]          = GLFW_KEY_X;
    io.KeyMap[ImGuiKey_Y]          = GLFW_KEY_Y;
    io.KeyMap[ImGuiKey_Z]          = GLFW_KEY_Z;

    ImGui_ImplOpenGL3_Init("#version 110");
    // ImGui_ImplOpenGL3_Init("#version 410 core");
}

void GUI::OnUpdate(int screen_width, int screen_height) {
    ImGuiIO& io    = ImGui::GetIO();
    io.DisplaySize = ImVec2(screen_width, screen_height);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    static bool a = true;
    ImGui::ShowDemoWindow(&a);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool OnMouseButtonPressedEvent(Event* e) {
    FFLY_LOG_CORE_TRACE("{0}", e->ToString());
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDown[static_cast<MouseButtonPressedEvent*>(e)->GetMouseButton()] =
        true;

    return false;
}
bool OOnMouseButtonReleasedEvent(Event* e) {
    FFLY_LOG_CORE_TRACE("{0}", e->ToString());
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDown[static_cast<MouseButtonReleasedEvent*>(e)->GetMouseButton()] =
        false;

    return false;
}

bool OOnMouseMovedEvent(Event* e) {
    FFLY_LOG_CORE_TRACE("{0}", e->ToString());
    ImGuiIO& io = ImGui::GetIO();
    io.MousePos = ImVec2(static_cast<MouseMovedEvent*>(e)->X(),
                         static_cast<MouseMovedEvent*>(e)->Y());

    return false;
}

bool OOnKeyPressedEvent(Event* e) {
    FFLY_LOG_CORE_TRACE("{0}", e->ToString());
    ImGuiIO& io = ImGui::GetIO();

    io.KeysDown[static_cast<KeyEvent*>(e)->GetKeyCode()] = true;

    io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] ||
                 io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
    io.KeyCtrl =
        io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
    io.KeyCtrl =
        io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
    io.KeyCtrl =
        io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

    return false;
}

bool OOnKeyReleasedEvent(Event* e) {
    FFLY_LOG_CORE_TRACE("{0}", e->ToString());
    ImGuiIO& io = ImGui::GetIO();

    io.KeysDown[static_cast<KeyEvent*>(e)->GetKeyCode()] = false;

    return false;
}

bool OOnKeyTypedEvent(Event* e) {
    ImGuiIO& io      = ImGui::GetIO();
    int      keycode = static_cast<KeyEvent*>(e)->GetKeyCode();
    if (keycode > 0 && keycode < 0x10000)
        io.AddInputCharacter((unsigned short)keycode);

    return false;
}

void GUI::OnEvent(Event& e) {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch(E_MOUSE_BUTTON_PRESSED, OnMouseButtonPressedEvent);
    dispatcher.Dispatch(E_MOUSE_BUTTON_RELEASED, OOnMouseButtonReleasedEvent);
    dispatcher.Dispatch(E_MOUSE_MOVED, OOnMouseMovedEvent);

    dispatcher.Dispatch(E_KEY_PRESSED, OOnKeyPressedEvent);
    dispatcher.Dispatch(E_KEY_RELEASED, OOnKeyReleasedEvent);
    dispatcher.Dispatch(E_KEY_TYPED, OOnKeyTypedEvent);
}

bool GUI::OnMouseButtonReleasedEvent(const MouseButtonReleasedEvent& e) {
}
bool GUI::OnMouseMovedEvent(const MouseMovedEvent& e) {
}
bool GUI::OnKeyPressedEvent(const KeyPressedEvent& e) {
}
bool GUI::OnKeyReleasedEvent(const KeyReleasedEvent& e) {
}
bool GUI::OnKeyTypedEvent(const KeyEvent& e) {
}

}; // namespace Firefly