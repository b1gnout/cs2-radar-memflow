#include "render.h"

bool init_render(render_data *render)
{
    if (SDL_Init(SDL_INIT_VIDEO) > 0)
    {
        return false;
    }

    render->window = SDL_CreateWindow(render->window_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, render->window_size_x, render->window_size_y, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!render->window)
        return false;

    render->renderer = SDL_CreateRenderer(render->window, -1, SDL_RENDERER_ACCELERATED);

    if (!render->renderer)
        return false;

    return true;
}

void load_textures(render_data *render)
{
    map_empty.map_texture = IMG_LoadTexture(render->renderer, "maps/nomap.jpg");
    map_dust.map_texture = IMG_LoadTexture(render->renderer, "maps/dust2.jpg");
    map_mirage.map_texture = IMG_LoadTexture(render->renderer, "maps/mirage.jpg");
    map_inferno.map_texture = IMG_LoadTexture(render->renderer, "maps/inferno.jpg");
    map_overpass.map_texture = IMG_LoadTexture(render->renderer, "maps/overpass.jpg");
    map_ancient.map_texture = IMG_LoadTexture(render->renderer, "maps/ancient.jpg");
    map_anubis.map_texture = IMG_LoadTexture(render->renderer, "maps/anubis.jpg");
    map_train.map_texture = IMG_LoadTexture(render->renderer, "maps/train.jpg");
    map_office.map_texture = IMG_LoadTexture(render->renderer, "maps/office.jpg");
}

bool poll_events(render_data *render)
{
    SDL_PollEvent(&render->window_events);
    if (render->window_events.type == SDL_QUIT)
        return false;

    if (render->window_events.type == SDL_WINDOWEVENT)
        SDL_GetWindowSize(render->window, &render->window_size_x, &render->window_size_y);

    return true;
}

void render_current_map(render_data *render, SDL_Texture* map_texture)
{
    SDL_RenderCopy(render->renderer, map_texture, 0, 0);
}

void render_player_icon(render_data *render, int16_t position_x, int16_t position_y, float view_angle_x, float color_r, float color_g, float color_b)
{
    float angle_degrees = 0;

    if (view_angle_x >= -180 && view_angle_x <= -1)
    {
        angle_degrees = 90 - view_angle_x;
    }
    else
    {
        angle_degrees = (int)(90 - view_angle_x + 360) % 360;
    }

    filledCircleRGBA(render->renderer, position_x, position_y, 5.f, color_r, color_g, color_b, 255);

    float angle_radian = (angle_degrees - 90.f) * (M_PI) / 180.f;

    float tip_x = position_x + 10.f * cos(angle_radian);
    float tip_y = position_y + 10.f * sin(angle_radian);

    float perpendicular_angle = angle_radian + M_PI / 2.f;

    float base_left_x = position_x - 5.f * cos(perpendicular_angle);
    float base_left_y = position_y - 5.f * sin(perpendicular_angle);
    float base_right_x = position_x + 5.f * cos(perpendicular_angle);
    float base_right_y = position_y + 5.f * sin(perpendicular_angle);

    int16_t triangle_points_x[3] = {(int16_t)tip_x, (int16_t)base_left_x, (int16_t)base_right_x};
    int16_t triangle_points_y[3] = {(int16_t)tip_y, (int16_t)base_left_y, (int16_t)base_right_y};

    filledPolygonRGBA(render->renderer, triangle_points_x, triangle_points_y, 3, color_r, color_g, color_b, 255);
}

void render_scene(render_data *render)
{
    SDL_RenderPresent(render->renderer);
    SDL_SetRenderDrawColor(render->renderer, 0, 0, 0, 255);
    SDL_RenderClear(render->renderer);
}

void draw_dead_player_icon(render_data *render, int16_t position_x, int16_t position_y, float color_r, float color_g, float color_b)
{
    SDL_SetRenderDrawColor(render->renderer, color_r, color_g, color_b, 255);
    SDL_RenderDrawLine(render->renderer, position_x, position_y, position_x + 4, position_y + 4);
    SDL_RenderDrawLine(render->renderer, position_x + 4, position_y, position_x + 4, position_y + 4);
}
