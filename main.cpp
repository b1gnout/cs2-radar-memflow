#include <stdio.h>
#include <unistd.h>
#include "render.h"
#include "game.h"
#include "memory.h"

int main(int argc, char *argv[])
{

    if (geteuid() > 0)
    {
        printf("Must be ran as sudo. closing\n");
        return 0;
    }

    Memory cs2_mem = {"cs2.exe"};

    if (!get_os_instance(&cs2_mem.os_instance))
    {
        printf("Failed to get os_instance. closing\n");
        return 1;
    }

    if (!get_process_instance(cs2_mem.os_instance, &cs2_mem.process_instance, cs2_mem.process_name))
    {
        printf("Failed to get process_instance. closing\n");
        return 1;
    }

    render_data render = {"CS2 Radar"};

    if (!init_render(&render))
    {
        printf("Failed to init renderer: %s\n", SDL_GetError());
        return 1;
    }

    Game cs2_game(&cs2_mem);

    load_textures(&render);

    while (poll_events(&render))
    {
        if (!cs2_game.get_current_map())
            break;

        render_current_map(&render, cs2_game.current_map.map_texture);
        cs2_game.fetch_entities();

        for (int i = 0; i < 128; i++)
        {
            vec2 radar_position = get_radar_position(cs2_game.entities[i].position, render.window_size_x, render.window_size_y, cs2_game.current_map);

            if (cs2_game.entities[i].team == 2)
            {
                render_player_icon(&render, radar_position.x, radar_position.y, cs2_game.entities[i].eye_angle_x, 255, 160, 0);
            }
            if (cs2_game.entities[i].team == 3)
            {
                render_player_icon(&render, radar_position.x, radar_position.y, cs2_game.entities[i].eye_angle_x, 0, 220, 255);
            }

        }

        render_scene(&render);
        SDL_Delay(16);
    }
}