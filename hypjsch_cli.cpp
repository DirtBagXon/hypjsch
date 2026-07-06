/*
 * ____ HYPSEUS COPYRIGHT NOTICE ____
 *
 * Copyright (C) 2022 DirtBagXon
 *
 * This file is part of HYPSEUS SINGE, a laserdisc arcade game emulator
 *
 * HYPSEUS SINGE is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * HYPSEUS SINGE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * g++ hypjsch_cli.cpp -lSDL3 -o hypjsch_cli
 *
 */

#include <SDL3/SDL.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <csignal>

#ifdef WIN32
#include <windows.h>
#endif

#include "keycodes.h"

static volatile bool running = true;

static void handle_sigint(int)
{
    running = false;
}

static int encode(int js_index, int control_id)
{
    return js_index * 100 + control_id;
}

static int js_index(SDL_JoystickID id, SDL_JoystickID* ids, int count)
{
    for (int i = 0; i < count; i++)
        if (ids[i] == id)
            return i;
    return -1;
}

static const char* joy_name(SDL_Joystick* j, int i)
{
    const char* name = SDL_GetJoystickName(j);
    return name ? name : "Unknown";
}

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    if (!SDL_Init(SDL_INIT_JOYSTICK))
    {
        SDL_Log("SDL init failed: %s", SDL_GetError());
        return 1;
    }

    int count = 0;
    SDL_JoystickID* ids = SDL_GetJoysticks(&count);

    if (!ids || count <= 0)
    {
        fprintf(stderr, "No joysticks found\n");
        SDL_free(ids);
        SDL_Quit();
        return 1;
    }

    fprintf(stdout, "%d joystick(s) found\n\n", count);
    fflush(stdout);

    SDL_Joystick** sticks =
        (SDL_Joystick**)SDL_calloc(count, sizeof(SDL_Joystick*));

    for (int i = 0; i < count; i++)
        sticks[i] = SDL_OpenJoystick(ids[i]);

    SDL_Event event;

    while (running && SDL_WaitEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
            goto exit;

        if (event.type == SDL_EVENT_KEY_DOWN)
        {
            if (event.key.key == SDLK_ESCAPE)
                goto exit;
        }

        if (event.type == SDL_EVENT_JOYSTICK_AXIS_MOTION)
        {
            int i = js_index(event.jaxis.which, ids, count);
            if (i < 0) continue;

            if (SDL_abs(event.jaxis.value) > JITTER)
            {
                int code = encode(i, event.jaxis.axis);

                printf("%s:\t", joy_name(sticks[i], i));
                printf("Axis: %03d\t- ", code);

                if (event.jaxis.value < 0)
                    printf("%s -%03d\n", "KEY_[AXIS]", code + 1);
                else
                    printf("%s +%03d\n", "KEY_[AXIS]", code + 1);
            }
            fflush(stdout);
        }

        else if (event.type == SDL_EVENT_JOYSTICK_HAT_MOTION)
        {
            int i = js_index(event.jhat.which, ids, count);
            if (i < 0) continue;

            int code = i * 100;

            printf("%s:\t", joy_name(sticks[i], i));
            printf("HAT - Set KEY_UP Button to: %03d\n", code);
            fflush(stdout);
        }

        else if (event.type == SDL_EVENT_JOYSTICK_BUTTON_DOWN)
        {
            int i = js_index(event.jbutton.which, ids, count);
            if (i < 0) continue;

            int code = encode(i, event.jbutton.button);

            printf("%s:\t", joy_name(sticks[i], i));
            printf("Button: %03d\t- ", code + 1);
            printf("KEY_[ACT] = %03d\n", code + 1);
            fflush(stdout);
        }

        if (!running)
            goto exit;
    }
    SDL_Delay(1);

    printf("\n%s - %s\n\n", "CLI Mapper Finished", VERSION);
    fflush(stdout);

exit:
    for (int i = 0; i < count; i++)
        if (sticks[i])
            SDL_CloseJoystick(sticks[i]);

    SDL_free(sticks);
    SDL_free(ids);

    SDL_Quit();
    return 0;
}
