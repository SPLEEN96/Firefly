#pragma once
#include "Firefly/Events/Event.h"
#include "PCH_CORE.h"

namespace Firefly {

struct WinAttributes {
    WinAttributes(const std::string& title = "Firefly",
                  const ui32& width = 1280, const ui32& height = 720)
        : Title(title), Width(width), Height(height) {}

    std::string Title;
    ui32        Width;
    ui32        Height;
};

/* Platform independant Window Interface */
class Window {
  public:
    virtual ~Window() {}

    virtual void Initialize() = 0;
    virtual void OnUpdate()   = 0;

    virtual void SetEventCallbackFn(bool (CallbackFn)(const Event& e)) = 0;

    virtual const ui32& GetWidth() const  = 0;
    virtual const ui32& GetHeight() const = 0;

    static Window* Create(const WinAttributes& attributes = WinAttributes());
};

} // namespace Firefly