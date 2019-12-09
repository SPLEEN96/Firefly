#define FFLY_API_OPENGL
#ifdef FFLY_API_OPENGL
#include <glad/glad.h>

#include "Rendering/Shader.h"
#include "PCH_CORE.h"

namespace Firefly {
namespace Rendering {
void Shader::Bind() {
    glUseProgram(m_handle);
}

void Shader::Unbind() {
    glUseProgram(0);
}

void Shader::SetUniform3fv(const char* name, float x, float y, float z) {
    float value[3] = {x, y, z};
    glUniform3fv(glGetUniformLocation(m_handle, name), 1, value);
}
} // namespace Rendering

namespace Shader {
std::string ReadShadeSourceCode(const char* file_path, bool vertex = true);
void        SuccessInfo(GLenum test_type, GLuint gl_object, const char* obj_name);

Firefly::Rendering::Shader* Create(const char* file_path) {
    uint32 vertex_shader, fragment_shader, program;

    /* === Vertex === */
    vertex_shader                 = glCreateShader(GL_VERTEX_SHADER);
    std::string vertex_source_str = ReadShadeSourceCode(file_path, true);
    const char* vertex_source     = vertex_source_str.c_str();

    glShaderSource(vertex_shader, 1, &vertex_source, NULL);
    glCompileShader(vertex_shader);
    SuccessInfo(GL_COMPILE_STATUS, vertex_shader, "Vertex Shader");

    /* === Fragment === */
    fragment_shader                 = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fragment_source_str = ReadShadeSourceCode(file_path, false);
    const char* fragment_source     = fragment_source_str.c_str();

    glShaderSource(fragment_shader, 1, &fragment_source, NULL);
    glCompileShader(fragment_shader);
    SuccessInfo(GL_COMPILE_STATUS, fragment_shader, "Fragment Shader");

    /* === Program === */
    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    SuccessInfo(GL_LINK_STATUS, program, "Shader Program");

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    Firefly::Rendering::Shader* shader = new Firefly::Rendering::Shader();
    shader->SetProgram(program);
    return shader;
}

/* TMP CODE (Ideally will not use any strings) */
std::string ReadShadeSourceCode(const char* file_path, bool vertex) {
    std::string       shader_source;
    std::stringstream shader_stream;

    std::string sfile_path = file_path;
    if (vertex) {
        sfile_path += ".vert";
    } else {
        sfile_path += ".frag";
    }

    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        file.open(sfile_path);

        shader_stream << file.rdbuf();
        shader_source = shader_stream.str();

        file.close();
    } catch (std::ifstream::failure e) {
        FFLY_LOG_CORE_ERROR("Unsuccesfull read of Shader file at: {0}", sfile_path);
    }

    return shader_source;
}

void SuccessInfo(GLenum test_type, GLuint gl_object, const char* obj_name) {
    int  success;
    char info_log[512];

    if (test_type == GL_COMPILE_STATUS) {
        glGetShaderiv(gl_object, test_type, &success);

        if (!success) {
            glGetShaderInfoLog(gl_object, 512, NULL, info_log);
            FFLY_LOG_CORE_ERROR("Shader Compilation failed ({0}): {1}", obj_name,
                                info_log);
        }
    } else if (test_type == GL_LINK_STATUS) {
        glGetProgramiv(gl_object, test_type, &success);

        if (!success) {
            glGetProgramInfoLog(gl_object, 512, NULL, info_log);
            FFLY_LOG_CORE_ERROR("Program Linking failed ({0}): {1}", obj_name, info_log);
        }
    }
}
} // namespace Shader

} // namespace Firefly

#endif