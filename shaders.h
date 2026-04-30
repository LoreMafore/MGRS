//
// Created by Conrad Mercer on 4/28/2026.
//

#ifndef MGRS_SHADERS_H
#define MGRS_SHADERS_H

#include <stdio.h>
#include <stdlib.h>
#include <glad.h>
#include <cglm/cglm.h>
#include "Global.h"

typedef struct
{
    uint32_t shader_program;
    uint32_t vao;
    uint32_t vbo;
    int vertex_count;
}grid_data_struct;

char* read_file(const char *filepath);
uint32_t compile_shader(const char*filepath, GLenum shader_type);
uint32_t create_shader_program(const char *vertex_shader, const char *fragment_shader);
void set_orthographic_projection(float origin_x, float width, float height, float origin_y, mat4 projection);
grid_data_struct build_grid(uint32_t shader_program, float width, float height, float spacing);
void render_grid(grid_data_struct *grid);
void destroy_grid(grid_data_struct *grid);

#endif //MGRS_SHADERS_H