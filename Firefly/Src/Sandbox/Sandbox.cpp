#include "Firefly.h"

/* === TEMPORARY === */
#include <imgui/imgui.h>

#include <imgui/examples/imgui_impl_glfw.h>
#include <imgui/examples/imgui_impl_opengl3.h>

#include <glad/glad.h>
#include <Rendering/Buffer.h>

#define FFLY Firefly::Rendering

class TriangleLayer : public Firefly::Layer {
  public:
    TriangleLayer() : Layer("Sandbox") {}
    ~TriangleLayer() override {}

    virtual void OnAttach() override {
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        std::vector<FFLY::VertexAttribute> vattr = {
            FFLY::VertexAttribute("position", FFLY::VertexAttribute::AttrType::FLOAT3),
            FFLY::VertexAttribute("color", FFLY::VertexAttribute::AttrType::FLOAT3)};

        FFLY::VertexBuffer* vbuffer =
            new FFLY::VertexBuffer(vertices, sizeof(vertices), vattr);
        vbuffer->Bind();

        int    success;
        char   infoLog[512];
        uint32 vertex_shader, fragment_shader;
        vertex_shader   = glCreateShader(GL_VERTEX_SHADER);
        fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(vertex_shader, 1, &vshader_source, NULL);
        glCompileShader(vertex_shader);
        glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                      << infoLog << std::endl;
        }

        glShaderSource(fragment_shader, 1, &fshader_source, NULL);
        glCompileShader(fragment_shader);

        glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                      << infoLog << std::endl;
        }

        program = glCreateProgram();
        glAttachShader(program, vertex_shader);
        glAttachShader(program, fragment_shader);
        glLinkProgram(program);

        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(program, 512, NULL, infoLog);
            std::cout << infoLog;
        }

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
    }

    virtual void OnDetach() override {}

    virtual void OnUpdate() override {
        glUseProgram(program);

        float color3fv[3] = {this->color.x, this->color.y, this->color.z};
        glUniform3fv(glGetUniformLocation(program, "color"), 1, color3fv);

        glBindVertexArray(VAO);
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
            ImGui::ColorPicker3("", (float*)&color, flags);
            ImGui::SameLine();
            ImGui::ColorButton("ColorOutput", *(ImVec4*)&color, flags, ImVec2(40, 225));
        }
        ImGui::End();
    }
    virtual void OnEvent(Firefly::Event& event) override {}

  private:
    uint32 VAO, VBO, program;
    ImVec4 color = ImVec4(0.4f, 0.f, 0.f, 1.f);

    float vertices[6 * 3] = {-0.5f, -0.5f, 0.0f, 1.f,  0.f,  0.f,  0.5f, -0.5f, 0.0f,
                             0.f,   1.f,   0.f,  0.0f, 0.5f, 0.0f, 0.f,  0.f,   1.f};

    const char* vshader_source = "#version 330 core\n"
                                 "layout (location =0) in vec3 a_position;\n"
                                 "void main(){\n"
                                 "gl_Position=vec4(a_position,1.f);"
                                 "}";

    const char* fshader_source = "#version 330 core\n"
                                 "uniform vec3 color;\n"
                                 "out vec4 frag_color;\n"
                                 "void main(){\n"
                                 "frag_color=vec4(color.rgb,1.f);"
                                 "}";
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