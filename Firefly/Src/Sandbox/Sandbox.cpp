#include "Firefly.h"

/* === TEMPORARY === */
#include <imgui/imgui.h>

#include <imgui/examples/imgui_impl_glfw.h>
#include <imgui/examples/imgui_impl_opengl3.h>

#include <glad/glad.h>
#include <Rendering/Buffer.h>
#include <Rendering/Shader.h>

#define FFLY Firefly::Rendering

class TriangleLayer : public Firefly::Layer {
  public:
    TriangleLayer() : Layer("Sandbox") {}
    ~TriangleLayer() override {}

    virtual void OnAttach() override {
        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);

        std::vector<FFLY::VertexAttribute> vattr = {
            FFLY::VertexAttribute("position", FFLY::VertexAttribute::AttrType::FLOAT3),
            FFLY::VertexAttribute("color", FFLY::VertexAttribute::AttrType::FLOAT3)};

        FFLY::VertexBuffer* vbuffer =
            new FFLY::VertexBuffer(m_vertices, sizeof(m_vertices), vattr);
        vbuffer->Bind();

        m_triangle_shader = Firefly::Shader::Create("./Assets/Shaders/TriangleTest");
    }

    virtual void OnDetach() override {}

    virtual void OnUpdate() override {
        m_triangle_shader->Bind();
        m_triangle_shader->SetUniform3fv("u_color",m_color.x, m_color.y, m_color.z);

        glBindVertexArray(m_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
    }

    virtual void OnImGuiDraw() override {
        ImGui::ShowStyleEditor();

        bool             show_color_picker = true;
        ImGuiWindowFlags window_flags      = 0;
        window_flags |= ImGuiWindowFlags_NoScrollbar;
        window_flags |= ImGuiWindowFlags_NoResize;

        ImGui::SetNextWindowSize(ImVec2(280, 255), ImGuiCond_FirstUseEver);
        ImGui::Begin("Color Picker", &show_color_picker, window_flags);
        {
            ImGuiColorEditFlags flags = 0;
            flags |= ImGuiColorEditFlags_NoSidePreview;
            flags |= ImGuiColorEditFlags_DisplayRGB;
            flags |= ImGuiColorEditFlags_PickerHueBar;

            ImGui::SetNextItemWidth(225);
            ImGui::ColorPicker3("", (float*)&m_color, flags);
            ImGui::SameLine();
            ImGui::ColorButton("ColorOutput", *(ImVec4*)&m_color, flags,
                               ImVec2(40, 225));
        }
        ImGui::End();
    }
    virtual void OnEvent(Firefly::Event& event) override {}

  private:
    uint32        m_VAO;
    FFLY::Shader* m_triangle_shader;
    ImVec4        m_color = ImVec4(0.4f, 0.f, 0.f, 1.f);

    float m_vertices[6 * 3] = {-0.5f, -0.5f, 0.0f, 1.f,  0.f,  0.f,  0.5f, -0.5f, 0.0f,
                               0.f,   1.f,   0.f,  0.0f, 0.5f, 0.0f, 0.f,  0.f,   1.f};
};
/* =================================================================*/

/* === SANDBOX === */

class Sandbox : public Firefly::Application {
  public:
    Sandbox() : Application() { this->PushLayer(new TriangleLayer()); }
    ~Sandbox() {}
};

Firefly::Application* CreateApplication() {
    return new Sandbox();
}