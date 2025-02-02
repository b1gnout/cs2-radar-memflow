#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <unistd.h>

struct texture_data
{
    SDL_Texture *no_map_texture;
    SDL_Texture *ancient_radar_texture;
    SDL_Texture *dust_radar_texture;
    SDL_Texture *inferno_radar_texture;
    SDL_Texture *mirage_radar_texture;
    SDL_Texture *nuke_radar_texture;
    SDL_Texture *overpass_radar_texture;
    SDL_Texture *train_radar_texture;
    SDL_Texture *vertigo_radar_texture;
};

struct render_data
{
    char window_title[32];
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event window_events;
    texture_data textures;
    int window_size_x = 512, window_size_y = 512;
};

bool init_render(render_data *render);

void load_textures(render_data *render);

bool poll_events(render_data *render);

void render_current_map(render_data *render, char map_name[32]);

void render_player_icon(render_data *render, int16_t position_x, int16_t position_y, float view_angle_x, float color_r, float color_g, float color_b);

void render_scene(render_data* render);

void draw_dead_player_icon(render_data* render, int16_t position_x, int16_t position_y, float color_r, float color_g, float color_b);