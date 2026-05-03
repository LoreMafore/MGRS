//
// Created by Conrad Mercer on 4/28/2026.
//

#include "shaders.h"
#include "math.h"


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

uint32_t create_shader_program(const char* vertex_shader, const char* fragment_shader)
{
    uint32_t vert = compile_shader(vertex_shader, GL_VERTEX_SHADER);
    uint32_t frag = compile_shader(fragment_shader, GL_FRAGMENT_SHADER);

    uint32_t program = glCreateProgram();
    glAttachShader(program, vert);
    glAttachShader(program, frag);
    glLinkProgram(program);

    uint32_t success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        char log[512];
        glGetProgramInfoLog(program, 512, NULL, log);
        fprintf(stderr, "Failed to link shader program: %s\n", vertex_shader);
        exit(EXIT_FAILURE);
    }

    glDeleteShader(vert);
    glDeleteShader(frag);
    return program;
}

void set_orthographic_projection(uint32_t shader_program, float origin_x, float origin_y, float width, float height)
{
    mat4 projection;
    glm_ortho(origin_x, width, origin_y, height, -1.0f, 1.0f, projection);

    glUseProgram(shader_program);
    uint32_t loc = glGetUniformLocation(shader_program, "projection");
    glUniformMatrix4fv(loc, 1, GL_FALSE, (float*)projection);
}

grid_data_struct build_grid(uint32_t shader_program, float width, float height, float horizontal_spacing, float vertical_spacing)
{
    int horizontal_lines = (int)ceilf(height / horizontal_spacing) + 1;
    int vertical_lines = (int)ceilf(width / vertical_spacing) + 1;
    int total_lines = horizontal_lines + vertical_lines;

    int vertice_count = total_lines * 2 * 3;
    float *vertices = malloc(vertice_count * sizeof(float));

    uint32_t indexes = 0;

    for (int i = 0; i < horizontal_lines; i++)
    {
        float y = i * horizontal_spacing;
        vertices[indexes++] = 0.0f;    vertices[indexes++] = y; vertices[indexes++] = 0.0f;
        vertices[indexes++] = width;   vertices[indexes++] = y; vertices[indexes++] = 0.0f;
    }

    for (int i = 0; i < vertical_lines; i++)
    {
        float x = i * vertical_spacing;
        vertices[indexes++] = x;   vertices[indexes++] = 0.0f; vertices[indexes++] = 0.0f;
        vertices[indexes++] = x;   vertices[indexes++] = height; vertices[indexes++] = 0.0f;
    }

    uint32_t vao, vbo = 0;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertice_count * sizeof(float), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    free(vertices);

    grid_data_struct data;
    data.shader_program = shader_program;
    data.vao = vao;
    data.vbo = vbo;
    data.vertex_count = total_lines * 2;
    return data;
}

void render_grid(grid_data_struct *grid)
{
    glUseProgram(grid->shader_program);
    glBindVertexArray(grid->vao);
    glDrawArrays(GL_LINES, 0, grid->vertex_count);
    glBindVertexArray(0);
}

void destroy_grid(grid_data_struct* grid)
{
    glDeleteVertexArrays(1, &grid->vao);
    glDeleteBuffers(1, &grid->vbo);
    // glDeleteProgram(grid->shader_program);
}


