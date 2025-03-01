#include "game.h"

Game::Game(Memory *mem) : process_memory(mem)
{
    client_dll_module = process_memory->get_module_info("client.dll");
    matchmaking_dll_module = process_memory->get_module_info("matchmaking.dll");

    uintptr_t entlist_pattern_rip = process_memory->find_byte_pattern(client_dll_module, {0x89, 0x05, 0x00, 0x00, 0x00, 0x00, 0x4a, 0x89, 0x3c, 0xf2});
    uint32_t entlist_offset = 0;
    process_memory->read_process_mem(&entlist_offset, entlist_pattern_rip + 2, sizeof(entlist_offset));
    entity_list_ptr = entlist_pattern_rip + entlist_offset + 14;

    uintptr_t gametype_pattern_rip = process_memory->find_byte_pattern(client_dll_module, {0x75, 0x5B, 0x48, 0x8B, 0x0D});
    uint32_t gametype_offset = 0;
    process_memory->read_process_mem(&gametype_offset, gametype_pattern_rip + 5, sizeof(gametype_offset));

    process_memory->read_process_mem(&gametype_ptr, gametype_pattern_rip + gametype_offset + 9, sizeof(gametype_ptr));
}

bool Game::get_current_map()
{
    memset(&current_map.map_name, 0, sizeof(current_map.map_name));
    uintptr_t map_name_address = 0;
    process_memory->read_process_mem(&map_name_address, gametype_ptr + 0x120, sizeof(map_name_address));
    if (!map_name_address)
        return false;

    process_memory->read_process_mem(&current_map.map_name, map_name_address + 4, sizeof(current_map.map_name));

    if (!current_map.map_name)
        return false;

    if (!strcmp(current_map.map_name, "<empty>"))
    {
        current_map = map_empty;
        return true;
    }
    if (!strcmp(current_map.map_name, "de_dust2"))
    {
        current_map = map_dust;
        return true;
    }
    if (!strcmp(current_map.map_name, "de_mirage"))
    {
        current_map = map_mirage;
        return true;
    }
    if (!strcmp(current_map.map_name, "de_inferno"))
    {
        current_map = map_inferno;
        return true;
    }
    if (!strcmp(current_map.map_name, "de_overpass"))
    {
        current_map = map_overpass;
        return true;
    }
    if (!strcmp(current_map.map_name, "de_ancient"))
    {
        current_map = map_ancient;
        return true;
    }
    if (!strcmp(current_map.map_name, "de_anubis"))
    {
        current_map = map_anubis;
        return true;
    }
    if (!strcmp(current_map.map_name, "de_train"))
    {
        current_map = map_train;
        return true;
    }
    if (!strcmp(current_map.map_name, "cs_office"))
    {
        current_map = map_office;
        return true;
    }
    if (!strcmp(current_map.map_name, "de_anubis"))
    {
        current_map = map_office;
        return true;
    }

    return true;
}

void Game::fetch_entities()
{
    for (int i = 0; i < 128; i++)
    {
        uintptr_t entity_ptr = 0;
        process_memory->read_process_mem(&entity_ptr, entity_list_ptr + i * 0x8, sizeof(entity_ptr));
        if (!entity_ptr)
            continue;

        process_memory->read_process_mem(&entities[i].health, entity_ptr + 0x344, sizeof(entities[i].health));
        process_memory->read_process_mem(&entities[i].team, entity_ptr + 0x3E3, sizeof(entities[i].team));
        process_memory->read_process_mem(&entities[i].position, entity_ptr + 0x1324, sizeof(entities[i].position));
        process_memory->read_process_mem(&entities[i].eye_angle_x, entity_ptr + 0x143C, sizeof(entities[i].eye_angle_x));
    }
}

vec2 get_radar_position(const vec3 world_position, int window_size_x, int window_size_y, map_info current_map)
{
    vec2 position;
    float x_ratio = (world_position.x - current_map.min_x) / (current_map.max_x - current_map.min_x);
    float y_ratio = (world_position.y - current_map.min_y) / (current_map.max_y - current_map.min_y);

    position.x = x_ratio * window_size_x;
    position.y = window_size_y - (y_ratio * window_size_y);

    return position;
}
