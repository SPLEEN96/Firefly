#include "Firefly/Window.h"

#define FFLY_LINUX
#ifdef FFLY_LINUX
/* ======================== LINUX IMPLEMENTATION ======================== */
/* IMGUI */
#include <GLFW/glfw3.h>

namespace Firefly {

static void GLFWWindowCallback(int error, const char* description) {
    FFLY_LOG_CORE_ERROR("{0}", description);
}

Window* Window::Create(std::string title, uint16 width, uint16 height) {
    Window* win = new Window();

    win->Data().Title  = title;
    win->Data().Width  = width;
    win->Data().Height = height;

    win->Initialize();

    return win;
}

void InitGLFWCallbacks(GLFWwindow* window);
void Window::Initialize() {
    FFLY_ASSERT(glfwInit(), "Failed to init GLFW");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    (this->Data().linux.Window) =
        glfwCreateWindow(this->Data().Width, this->Data().Height,
                         this->Data().Title.c_str(), nullptr, nullptr);
    if (this->Data().linux.Window == nullptr) {
        FFLY_LOG_CORE_CRITICAL("Failed to init nullptr with GLFWwindow");
    }
    GLFWwindow* window = static_cast<GLFWwindow*>(this->Data().linux.Window);

    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, &this->Data());
    glfwSetErrorCallback(GLFWWindowCallback);
    InitGLFWCallbacks(window);

    FFLY_LOG_CORE_INFO("Created Window {0} ({1}, {2})", this->Data().Title,
                       this->Data().Width, this->Data().Height);
}

void Window::OnUpdate() {
    GLFWwindow* window = static_cast<GLFWwindow*>(this->Data().linux.Window);
    glfwPollEvents();

    glfwSwapBuffers(window);
}

bool Window::ShouldClose() {
    if (glfwWindowShouldClose(static_cast<GLFWwindow*>(this->Data().linux.Window))) {
        return true;
    }
    return false;
}

void* Window::GetPlatformWindow() {
    return this->Data().linux.Window;
}

void InitGLFWCallbacks(GLFWwindow* window) {
    glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        data.Width       = width;
        data.Height      = height;
    });

    glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
    });

    glfwSetKeyCallback(
        window, [](GLFWwindow* window, int key, int scancode, int action, int modes) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            switch (action) {
            case GLFW_PRESS: {
                KeyPressedEvent e(key, 0);
                data.CallbackFn(e);
                break;
            }
            case GLFW_RELEASE: {
                KeyReleasedEvent e(key);
                data.CallbackFn(e);
                break;
            }
            case GLFW_REPEAT: {
                KeyPressedEvent e(key, 1);
                data.CallbackFn(e);
                break;
            }
            }
        });

    glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int keycode) {
        WindowData&   data = *(WindowData*)glfwGetWindowUserPointer(window);
        KeyTypedEvent e(keycode);
        data.CallbackFn(e);
    });

    glfwSetMouseButtonCallback(
        window, [](GLFWwindow* window, int button, int action, int modes) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            switch (action) {
            case GLFW_PRESS: {
                MouseButtonPressedEvent e(button);
                data.CallbackFn(e);
                break;
            }
            case GLFW_RELEASE: {
                MouseButtonReleasedEvent e(button);
                data.CallbackFn(e);
                break;
            }
            }
        });

    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos) {
        WindowData&     data = *(WindowData*)glfwGetWindowUserPointer(window);
        MouseMovedEvent e((float)xPos, (float)yPos);
        data.CallbackFn(e);
    });
}
} // namespace Firefly

#endif