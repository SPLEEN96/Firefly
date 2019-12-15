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

void Shader::SetVector1i(const char* name, const float& x) {
    glUniform1i(glGetUniformLocation(m_handle, name), x);
}

void Shader::SetVector1f(const char* name, const float& x) {
    float value[1] = {x};
    glUniform1fv(glGetUniformLocation(m_handle, name), 1, value);
}

void Shader::SetVector2f(const char* name, const float& x, const float& y) {
    float value[2] = {x, y};
    glUniform2fv(glGetUniformLocation(m_handle, name), 1, value);
}

void Shader::SetVector3f(const char* name, const float& x, const float& y,
                         const float& z) {
    float value[3] = {x, y, z};
    glUniform3fv(glGetUniformLocation(m_handle, name), 1, value);
}

void Shader::SetVector4f(const char* name, const float& x, const float& y,
                         const float& z, const float& w) {
    float value[4] = {x, y, z, w};
    glUniform4fv(glGetUniformLocation(m_handle, name), 1, value);
}

void Shader::SetMatrix4f(const char* name, float* mat) {
    glUniformMatrix4fv(glGetUniformLocation(m_handle, name), 1, GL_FALSE, mat);
}

} // namespace Rendering

/* === FACTORY === */
namespace Factory {
namespace Shader {
std::string ReadShadeSourceCode(const char* file_path, const bool& vertex = true);
void        SuccessInfo(GLenum test_type, const GLuint& gl_primitive,
                        const char* primitive_name);

Rendering::Shader* Create(const char* file_path) {
    uint32 vertex_shader_handle, fragment_shader_handle, program_handle;

    /* === Vertex === */
    vertex_shader_handle          = glCreateShader(GL_VERTEX_SHADER);
    std::string vertex_source_str = ReadShadeSourceCode(file_path, true);
    const char* vertex_source     = vertex_source_str.c_str();

    glShaderSource(vertex_shader_handle, 1, &vertex_source, NULL);
    glCompileShader(vertex_shader_handle);
    SuccessInfo(GL_COMPILE_STATUS, vertex_shader_handle, "Vertex Shader");

    /* === Fragment === */
    fragment_shader_handle          = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fragment_source_str = ReadShadeSourceCode(file_path, false);
    const char* fragment_source     = fragment_source_str.c_str();

    glShaderSource(fragment_shader_handle, 1, &fragment_source, NULL);
    glCompileShader(fragment_shader_handle);
    SuccessInfo(GL_COMPILE_STATUS, fragment_shader_handle, "Fragment Shader");

    /* === Program === */
    program_handle = glCreateProgram();
    glAttachShader(program_handle, vertex_shader_handle);
    glAttachShader(program_handle, fragment_shader_handle);
    glLinkProgram(program_handle);
    SuccessInfo(GL_LINK_STATUS, program_handle, "Shader Program");

    glDeleteShader(vertex_shader_handle);
    glDeleteShader(fragment_shader_handle);

    Rendering::Shader* shader = new Rendering::Shader();
    shader->SetAPIHandle(program_handle);
    return shader;
}

/* TMP CODE (Ideally will not use any strings) */
std::string ReadShadeSourceCode(const char* file_path, const bool& vertex) {
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

void SuccessInfo(GLenum test_type, const GLuint& gl_primitive,
                 const char* primitive_name) {
    int  success;
    char info_log[512];

    if (test_type == GL_COMPILE_STATUS) {
        glGetShaderiv(gl_primitive, test_type, &success);

        if (!success) {
            glGetShaderInfoLog(gl_primitive, 512, NULL, info_log);
            FFLY_LOG_CORE_ERROR("Shader Compilation failed ({0}): {1}", primitive_name,
                                info_log);
        }
    } else if (test_type == GL_LINK_STATUS) {
        glGetProgramiv(gl_primitive, test_type, &success);

        if (!success) {
            glGetProgramInfoLog(gl_primitive, 512, NULL, info_log);
            FFLY_LOG_CORE_ERROR("Program Linking failed ({0}): {1}", primitive_name,
                                info_log);
        }
    }
}
} // namespace Shader
} // namespace Factory

} // namespace Firefly

#endif