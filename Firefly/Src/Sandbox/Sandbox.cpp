#include "Firefly.h"

/* === TEMPORARY === */
#include <imgui/imgui.h>

#include <imgui/examples/imgui_impl_glfw.h>
#include <imgui/examples/imgui_impl_opengl3.h>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define FFLY Firefly::Rendering

class TriangleLayer : public Firefly::Layer {
  public:
    TriangleLayer() : Layer("Sandbox") {}
    ~TriangleLayer() override {}

    virtual void OnAttach() override {
        m_VAO = Firefly::Factory::VertexArray::Create();
        m_VAO->Bind();

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

        m_view = glm::translate(glm::mat4(1.f), glm::vec3(0.0f, 0.0f, -3.0f));
        m_projection =
            glm::perspective(glm::radians(45.0f), 1280.f / 960.f, 0.1f, 100.0f);
    }

    virtual void OnDetach() override {}

    virtual void OnUpdate() override {
        m_square_shader->Bind();
        m_square_shader->SetVector1i("tex", 0);
        m_texture->Bind(0);

        m_transform.SetPosition(m_position);
        m_transform.Rotate(m_rotation_angle, new float[3]{0.f, 0.f, 1.f});
        m_model = m_transform.GetTransformMatrix();

        m_square_shader->SetMatrix4f("model", &m_model[0][0]);
        m_square_shader->SetMatrix4f("view", &m_view[0][0]);
        m_square_shader->SetMatrix4f("projection", &m_projection[0][0]);

        m_VAO->Bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);

        m_triangle_shader->Bind();
        m_triangle_shader->SetVector3f("u_color", m_color.x, m_color.y, m_color.z);
        m_VAO->Bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);
    }

    virtual void OnImGuiDraw() override {
        // ImGui::ShowStyleEditor();

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

        bool show_transform = true;
        ImGui::SetNextWindowSize(ImVec2(120, 330), ImGuiCond_FirstUseEver);
        ImGui::Begin("Transform", &show_transform, window_flags);
        {
            ImGui::PushID("Position");
            for (int i = 0; i < 3; i++) {
                ImGui::SameLine();
                ImGui::PushID(i);
                ImGui::PushStyleColor(ImGuiCol_FrameBg,
                                      (ImVec4)ImColor::HSV(i / 7.0f, 0.5f, 0.5f));
                ImGui::PushStyleColor(ImGuiCol_FrameBgHovered,
                                      (ImVec4)ImColor::HSV(float(i) / 7.0f, 0.6f, 0.3f));
                ImGui::PushStyleColor(ImGuiCol_FrameBgActive,
                                      (ImVec4)ImColor::HSV(float(i) / 7.0f, 0.7f, 0.4f));
                if (i < 2) {
                    ImGui::VSliderFloat("##", ImVec2(18, 300), &m_position[i], -4.0f,
                                        4.0f, "");
                } else {
                    ImGui::VSliderFloat("##", ImVec2(18, 300), &m_position[i], -15.0f,
                                        4.0f, "");
                }
                if (ImGui::IsItemActive() || ImGui::IsItemHovered())
                    ImGui::SetTooltip("%.1f", m_position[i]);

                ImGui::PopStyleColor(3);
                ImGui::PopID();
            }
            ImGui::PopID();

            ImGui::SameLine();

            ImGui::PushID("Rotation");
            {
                ImGui::PushID(0);
                ImGui::PushStyleColor(ImGuiCol_FrameBg,
                                      (ImVec4)ImColor::HSV(0.7f, 0.2f, 0.5f));
                ImGui::PushStyleColor(ImGuiCol_FrameBgHovered,
                                      (ImVec4)ImColor::HSV(0.7f, 0.4f, 0.5f));
                ImGui::PushStyleColor(ImGuiCol_FrameBgActive,
                                      (ImVec4)ImColor::HSV(0.7f, 0.6f, 0.7f));

                ImGui::VSliderFloat("##", ImVec2(18, 300), &m_rotation_angle, -180.0f,
                                    180.0f, "");
                if (ImGui::IsItemActive() || ImGui::IsItemHovered())
                    ImGui::SetTooltip("%.3f", m_rotation_angle);

                ImGui::PopStyleColor(3);
                ImGui::PopID();
            }
            ImGui::PopID();
        }
        ImGui::End();
    }

    virtual void OnEvent(Firefly::Event& event) override {}

  private:
    // uint32         m_VAO;
    FFLY::VertexArray* m_VAO;
    FFLY::Shader *     m_triangle_shader, *m_square_shader;
    FFLY::Texture *    m_texture, *m_texture2;
    ImVec4             m_color = ImVec4(0.4f, 0.f, 0.f, 1.f);

    float           m_position[3]    = {0.f};
    float           m_rotation_angle = 0.f;
    FFLY::Transform m_transform;
    glm::mat4       m_model;
    glm::mat4       m_view;
    glm::mat4       m_projection;

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