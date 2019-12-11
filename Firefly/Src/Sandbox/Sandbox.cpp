#include "Firefly.h"

/* === TEMPORARY === */
#include <imgui/imgui.h>

#include <imgui/examples/imgui_impl_glfw.h>
#include <imgui/examples/imgui_impl_opengl3.h>

#include <glad/glad.h>

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
            FFLY::VertexAttribute("color", FFLY::VertexAttribute::AttrType::FLOAT3),
            FFLY::VertexAttribute("tex_coord", FFLY::VertexAttribute::AttrType::FLOAT2)};

        FFLY::VertexBuffer* vbuffer = Firefly::Factory::VertexBuffer::Create(
            m_quad_vertices, sizeof(m_quad_vertices), vattr);
        vbuffer->Bind();

        m_triangle_shader =
            Firefly::Factory::Shader::Create("./Assets/Shaders/TriangleTest");

        m_square_shader =
            Firefly::Factory::Shader::Create("./Assets/Shaders/TexturedQuad");

        m_texture =
            Firefly::Factory::Texture::Create("./Assets/Textures/obsidian.png", false);

        m_texture2 =
            Firefly::Factory::Texture::Create("./Assets/Textures/grey_stone.jpg", false);
    }

    virtual void OnDetach() override {}

    virtual void OnUpdate() override {
        m_square_shader->Bind();
        m_square_shader->SetUniform1i("tex", 0);
        m_texture->Bind(0);
        // m_square_shader->SetUniform1i("tex", 1);
        // m_texture2->Bind(1);

        glBindVertexArray(m_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        m_triangle_shader->Bind();
        m_triangle_shader->SetUniform3fv("u_color", m_color.x, m_color.y, m_color.z);
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
    uint32         m_VAO;
    FFLY::Shader * m_triangle_shader, *m_square_shader;
    FFLY::Texture *m_texture, *m_texture2;
    ImVec4         m_color = ImVec4(0.4f, 0.f, 0.f, 1.f);

    float m_quad_vertices[8 * 6] = {
        /* Positions */ /* Colors */ /* TexCoords */
        0.5f,
        0.5f,
        0.0f,
        1.0f,
        0.0f,
        0.0f,
        1.0f,
        1.0f, /* top right */
        0.5f,
        -0.5f,
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        1.0f,
        0.0f, /* bottom right */
        -0.5f,
        -0.5f,
        0.0f,
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        0.0f, /* bottom left */
        0.5f,
        0.5f,
        0.0f,
        1.0f,
        0.0f,
        0.0f,
        1.0f,
        1.0f, /* top right */
        -0.5f,
        0.5f,
        0.0f,
        1.0f,
        1.0f,
        0.0f,
        0.0f,
        1.0f, /* top left */
        -0.5f,
        -0.5f,
        0.0f,
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        0.0f, /* bottom left */
    };

    float m_triangle_vertices[6 * 3] = {/* Positions */ /* Colors */
                                        -0.5f,
                                        -0.5f,
                                        0.0f,
                                        1.f,
                                        0.f, /* left vertex */
                                        0.5f,
                                        -0.5f,
                                        0.0f,
                                        0.f,
                                        1.f, /* right vertex */
                                        0.0f,
                                        0.5f,
                                        0.0f,
                                        0.f,
                                        0.f}; /* top vertex */
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