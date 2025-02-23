#pragma once
#include <cstdint>
#include "memory.h"
#include "render.h"

struct vec2
{
    float x, y;
};

struct vec3
{
    float x, y, z;
};

struct map_info
{
    SDL_Texture* map_texture;
    char map_name[32];
    float min_x, max_x, min_y, max_y;
};

inline map_info map_empty = {0, "<empty>", 0.f, 0.f, 0.f, 0.f};
inline map_info map_dust = {0, "de_dust2", -2500.f, 2000.f, -1200.f, 3250.f};
inline map_info map_mirage = {0, "de_mirage", -2877.f, 1567.f,  -3070.f, 1374.f};
inline map_info map_inferno = {0, "de_inferno", -2000.f, 2780.f, -1200.f, 3850.f};
inline map_info map_overpass = {0, "de_overpass", -4768.f, 412.f, -3520.72, 1660.f};
inline map_info map_ancient = {0, "de_ancient", -2871, 2105.f, -2888.32, 2088.f};
inline map_info map_anubis = {0, "de_anubis", -2938, 2688.f, -2198.32, 3428.f};
inline map_info map_train = {0, "de_train", -2375.32, 1913.f, -2139, 2149.f};
inline map_info map_office = {0, "cs_office", -1892.f, 2418.f, -2382.f, 1928.f};

class Game
{
public:
    Game(Memory *mem);

    struct entity_info
    {
        int32_t health;
        vec3 position;
        int32_t team;
        float eye_angle_x;
    };

    ModuleInfo *client_dll_module;
    ModuleInfo *matchmaking_dll_module;
    entity_info entities[128];
    map_info current_map;

    uintptr_t entity_list_ptr = 0;
    uintptr_t gametype_ptr = 0;

    bool get_current_map();
    void fetch_entities();

private:
    Memory *process_memory;
};

vec2 get_radar_position(const vec3 world_position, int window_size_x, int window_size_y, map_info current_map);
