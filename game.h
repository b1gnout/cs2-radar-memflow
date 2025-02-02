#include <cstdint>
#include "memory.h"

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
    char map_name[32];
    float min_x, max_x, min_y, max_y;
};

static map_info map_empty = {"<empty>", 0.f, 0.f, 0.f, 0.f};
static map_info map_dust = {"de_dust2", -2500.f, 2000.f, -1200.f, 3250.f};
static map_info map_mirage = {"de_mirage", -3180.f, 1800.f, -3250.f, 1900.f};
static map_info map_inferno = {"de_inferno", -2000.f, 2780.f, -1200.f, 3850.f};

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
    entity_info entities[64];
    map_info current_map;

    bool get_current_map();
    void fetch_entities();

private:
    Memory *process_memory;
};

vec2 get_radar_position(const vec3 world_position, int window_size_x, int window_size_y, map_info current_map);