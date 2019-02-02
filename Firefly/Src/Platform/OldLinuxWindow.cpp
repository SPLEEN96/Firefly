// #include "LinuxWindow.h"

// namespace Firefly {

// static void GLFWErrorCallback(int error, const char* description) {
//     FFLY_LOG_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
// }

// Window* Window::Create(const WinAttributes& attributes) {
//     return new LinuxWindow(attributes);
// }

// LinuxWindow::LinuxWindow(const WinAttributes& attributes) {
//     m_data.Title  = attributes.Title;
//     m_data.Width  = attributes.Width;
//     m_data.Height = attributes.Height;

//     this->Initialize();
//     this->InitGLFWCallbacks();
// }

// LinuxWindow::~LinuxWindow() {
//     glfwDestroyWindow(m_window);
// }

// void LinuxWindow::Initialize() {
//     FFLY_ASSERT(glfwInit(), "Failed to init GLFW");

//     m_window = glfwCreateWindow(m_data.Width, m_data.Height,
//                                 m_data.Title.c_str(), nullptr, nullptr);
//     glfwMakeContextCurrent(m_window);

//     FFLY_LOG_CORE_INFO("Created Window {0} ({1}, {2})", m_data.Title,
//                        m_data.Width, m_data.Height);

//     glfwSetWindowUserPointer(m_window, &m_data);
// }

// void LinuxWindow::OnUpdate() {
//     glfwPollEvents();
//     glfwSwapBuffers(m_window);
// }





















// void LinuxWindow::InitGLFWCallbacks() {
//     glfwSetErrorCallback(GLFWErrorCallback);

//     glfwSetWindowSizeCallback(
//         m_window, [](GLFWwindow* window, int width, int height) {
//             WinData& data = *(WinData*)glfwGetWindowUserPointer(window);
//             data.Width    = width;
//             data.Height   = height;

//             // WindowResizeEvent e(width, height);
//             // data.EventCallbackFn(e);
//         });

//     glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
//         WinData& data = *(WinData*)glfwGetWindowUserPointer(window);
//         // WindowCloseEvent e;
//         // data.EventCallbackFn(e);
//     });

//     glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode,
//                                     int action, int modes) {
//         WinData& data = *(WinData*)glfwGetWindowUserPointer(window);
//         switch (action) {
//         case GLFW_PRESS: {
//             KeyPressedEvent e(key, 0);
//             data.EventCallbackFn(e);
//             break;
//         }
//         case GLFW_RELEASE: {
//             KeyReleasedEvent e(key);
//             data.EventCallbackFn(e);
//             break;
//         }
//         case GLFW_REPEAT: {
//             KeyPressedEvent e(key, 1);
//             data.EventCallbackFn(e);
//             break;
//         }
//         }
//     });

//     glfwSetMouseButtonCallback(
//         m_window, [](GLFWwindow* window, int button, int action, int modes) {
//             WinData& data = *(WinData*)glfwGetWindowUserPointer(window);
//             // switch (action) {
//             // case GLFW_PRESS:
//             //     MouseButtonPressedEvent e(button);
//             //     data.EventCallbackFn(e);
//             //     break;
//             // case GLFW_RELEASE:
//             //     MouseButtonReleasedEvent e(button);
//             //     data.EventCallbackFn(e);
//             //     break;
//             // }
//         });

//     glfwSetScrollCallback(
//         m_window, [](GLFWwindow* window, double xOffset, double yOffset) {
//             WinData& data = *(WinData*)glfwGetWindowUserPointer(window);
//             // MouseScrolledEvent e((float)xOffset, (float)yOffset);
//             // data.EventCallbackFn(e);
//         });

//     glfwSetCursorPosCallback(
//         m_window, [](GLFWwindow* window, double xPos, double yPos) {
//             WinData& data = *(WinData*)glfwGetWindowUserPointer(window);
//             // MouseMovedEvent e((float)xPos, (float)yPos);
//             // data.EventCallbackFn(e);
//         });
// }

// } // namespace Firefly