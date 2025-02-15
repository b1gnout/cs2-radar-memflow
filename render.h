#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <unistd.h>
#include "game.h"

struct render_data
{
    char window_title[32];
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event window_events;
    int window_size_x = 512, window_size_y = 512;
};

bool init_render(render_data *render);

void load_textures(render_data *render);

bool poll_events(render_data *render);

void render_current_map(render_data *render, SDL_Texture* map_texture);

void render_player_icon(render_data *render, int16_t position_x, int16_t position_y, float view_angle_x, float color_r, float color_g, float color_b);

void render_scene(render_data* render);

void draw_dead_player_icon(render_data* render, int16_t position_x, int16_t position_y, float color_r, float color_g, float color_b);d