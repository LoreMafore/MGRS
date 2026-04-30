//
// Created by Conrad Mercer on 4/28/2026.
//

#include "shaders.h"


void orthographic_projection(float origin_x, float width, float height, float origin_y, mat4 projection)
{
    uint32_t shader_program = glCreateProgram();
    glm_ortho(origin_x, width, height, origin_y, -1.0f, 1.0f, projection);

    int projection_location = glGetUniformLocation(shader_program, "projection");
    glUniformMatrix4fv(projection_location, 1, GL_FALSE, (float*)projection);
}

char* read_file(const char* filepath)
{
    FILE *file = fopen(filepath, "rb");

    if (!file)
    {
        fprintf(stderr, "Failed to open shader file: %s\n", filepath);
        return NULL;
    }

    fseek(file , 0 , SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(length + 1);
    fread(buffer, 1, length, file);
    buffer[length] = '\0';
    fclose(file);
    return buffer;
}

uint32_t compile_shader(const char* filepath, GLenum shader_type)
{
    char *source = read_file(filepath);

    if (!source)
    {
        fprintf(stderr, "Failed to load shader file: %s\n", filepath);
        exit(EXIT_FAILURE);
    }

    uint32_t shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, (const char **)&source, NULL);
    glCompileShader(shader);
    free(source);

    uint32_t success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char info_log[512];
        glGetShaderInfoLog(shader, 512, NULL, info_log);
        fprintf(stderr, "Failed to compile shader: %s\n", filepath);
        exit(EXIT_FAILURE);
    }

    return shader;
}
