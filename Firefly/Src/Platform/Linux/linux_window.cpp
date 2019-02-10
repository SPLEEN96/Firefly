#include "Firefly/Window.h"

#define FFLY_LINUX
#ifdef FFLY_LINUX
/* ======================== LINUX IMPLEMENTATION ======================== */
//#include "Platform/imgui_opengl.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
//#include <imgui/imgui.h>

namespace Firefly {

struct MemoryManager {
    struct Factory {
        static const uint8& CreateWinData() {
            uint8 new_data_handle;
            return new_data_handle;
        }
    };
    static WindowData& WinData(uint8 win_handle) {
        return attr_list[win_handle];
    }

    static WindowData attr_list[10];
};

Window* Window::Create(std::string title, uint16 width, uint16 height) {
    // Window* win     = (Window*)std::malloc(sizeof(Window));
    // win->DataHandle = MemoryManager::Factory::CreateWinData();
    Window* win = new Window();
    // win->Data().Title  = attr.Title;
    // win->Data().Width  = attr.Width;
    // win->Data().Height = attr.Height;
    win->Data().Title  = title;
    win->Data().Width  = width;
    win->Data().Height = height;

    win->Initialize();

    return win;
}

void InitGLFWCallbacks(GLFWwindow* window);
void Window::Initialize() {
    FFLY_ASSERT(glfwInit(), "Failed to init GLFW");

    (this->Data().linux.Window) =
        glfwCreateWindow(this->Data().Width, this->Data().Height,
                         this->Data().Title.c_str(), nullptr, nullptr);
    if (this->Data().linux.Window == nullptr) {
        FFLY_LOG_CORE_CRITICAL("Failed to init nullptr with GLFWwindow");
    }
    GLFWwindow* window = static_cast<GLFWwindow*>(this->Data().linux.Window);

    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, &this->Data());
    InitGLFWCallbacks(window);

    FFLY_LOG_CORE_INFO("Created Window {0} ({1}, {2})", this->Data().Title,
                       this->Data().Width, this->Data().Height);

    FFLY_ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress),
                "Failed to initialize glad");
}

void Window::OnUpdate() {
    GLFWwindow* window = static_cast<GLFWwindow*>(this->Data().linux.Window);
    glfwPollEvents();
    glfwSwapBuffers(window);
}

void InitGLFWCallbacks(GLFWwindow* window) {
    glfwSetWindowSizeCallback(
        window, [](GLFWwindow* window, int width, int height) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.Width       = width;
            data.Height      = height;
        });

    glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
    });

    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode,
                                  int action, int modes) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        switch (action) {
        case GLFW_PRESS: {
            KeyPressedEvent e(key, 0);
            data.CallbackFn(e);
            data.EventCallbackFn(e);
            break;
        }
        case GLFW_RELEASE: {
            KeyReleasedEvent e(key);
            data.CallbackFn(e);
            data.EventCallbackFn(e);
            break;
        }
        case GLFW_REPEAT: {
            KeyPressedEvent e(key, 1);
            data.CallbackFn(e);
            data.EventCallbackFn(e);
            break;
        }
        }
    });

    glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int keycode) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
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
                data.EventCallbackFn(e);
                break;
            }
            case GLFW_RELEASE: {
                MouseButtonReleasedEvent e(button);
                data.CallbackFn(e);
                data.EventCallbackFn(e);
                break;
            }
            }
        });

    glfwSetCursorPosCallback(
        window, [](GLFWwindow* window, double xPos, double yPos) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            MouseMovedEvent e((float)xPos, (float)yPos);
            data.CallbackFn(e);
            data.EventCallbackFn(e);
        });
}
} // namespace Firefly

#endif