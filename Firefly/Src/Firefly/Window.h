#pragma once
#include "FFLY_CORE.h"
#include "PCH_CORE.h"

#include "Firefly/Events/Event.h"
#include "Firefly/Events/KeyEvents.h"
#include "Firefly/Events/MouseEvents.h"

namespace Firefly {

struct WindowData {
    friend struct Window;

    uint8       Handle;
    std::string Title;
    int         Width;
    int         Height;
    bool (*EventCallbackFn)(Event& e);

    std::function<bool(Event& e)> CallbackFn;

  private:
    union {
        /* LINUX_DATA */
        struct {
            void* Window;
        } linux;

        /* WINDOW_DATA */
        struct {
            void* Window;
        } win32;
    };
};

struct Window {
    static Window* Create(std::string title, uint16 width, uint16 height);
    void           Initialize();
    void           OnUpdate();

    void SetEventCallbackFn(bool(CallbackFn)(Event& e)) {
        Data().EventCallbackFn = CallbackFn;
    }
    void BindEventCallBackFn(std::function<bool(Event& e)> Callback) {
        Data().CallbackFn = Callback;
    }
    WindowData& Data() {
        return m_data;
        // return MemoryManager::WinData(DataHandle);
    }

  private:
    uint8      DataHandle;
    WindowData m_data;
};

} // namespace Firefly
