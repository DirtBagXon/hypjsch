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
 * g++ keycodes.cpp hypjsch.cpp -lSDL3_test -lSDL3 -o hypjsch
 *
 */


#include <SDL3/SDL.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#include "keycodes.h"

#ifdef WIN32
#include <windows.h>
#endif

struct SlotMapping
{
    int count = 0;
    SDL_JoystickID* ids = nullptr;
    SDL_Joystick** sticks = nullptr;

    int active_js = -1;
    int keyboard_mode = 0;

    char line[128] = {0};
    char output[128] = {0};

    Uint32 last_update = 0;
};

static int center_x(int screen_w, const char* text)
{
    return (screen_w - ((int)strlen(text) * 8)) / 2;
}

static int encode(int js_index, int control_id)
{
    return (js_index * 100) + control_id;
}

static int js_index(SDL_JoystickID id, SDL_JoystickID* ids, int count)
{
    for (int i = 0; i < count; i++)
        if (ids[i] == id)
            return i;
    return -1;
}

static void render_mapper(SDL_Renderer* r, SlotMapping& st,
                          int screen_w, const char* version,
                          SDL_Event& event)
{
    const char* title = "KEYBOARD DEVICE";

    if (event.type == SDL_EVENT_JOYSTICK_AXIS_MOTION)
    {
        int i = js_index(event.jaxis.which, st.ids, st.count);
        if (i >= 0)
        {
            st.active_js = i;
            st.last_update = SDL_GetTicks();

            if (abs(event.jaxis.value) > JITTER) {

                st.keyboard_mode = 0;
                int code = encode(i, event.jaxis.axis);

                snprintf(st.line, sizeof(st.line),
                         "Raw Device %d Axis %d = %d",
                         event.jaxis.which,
                         event.jaxis.axis,
                         event.jaxis.value);

                snprintf(st.output, sizeof(st.output),
                         "Config: KEY_[AXIS] = %s%03d",
                         (event.jaxis.value < 0 ? "-" : "+"),
                         code + 1);
            }
        }
    }
    else if (event.type == SDL_EVENT_JOYSTICK_BUTTON_DOWN)
    {
        int i = js_index(event.jbutton.which, st.ids, st.count);
        if (i >= 0)
        {
            st.active_js = i;
            st.keyboard_mode = 0;

            int code = encode(i, event.jbutton.button);

            snprintf(st.line, sizeof(st.line),
                     "Raw Device %d Button: %d",
                     event.jbutton.which,
                     event.jbutton.button);

            snprintf(st.output, sizeof(st.output),
                     "Config: KEY_[ACT] = %03d",
                     code + 1);
        }
    }
    else if (event.type == SDL_EVENT_JOYSTICK_HAT_MOTION)
    {
        int i = js_index(event.jhat.which, st.ids, st.count);
        if (i >= 0)
        {
            st.active_js = i;
            st.keyboard_mode = 0;

            int code = encode(i, event.jhat.hat);

            snprintf(st.line, sizeof(st.line),
                     "Raw Device %d Hat %d: %s",
                     event.jhat.which,
                     event.jhat.hat,
                     sdl3_hat(event.jhat.value));

            snprintf(st.output, sizeof(st.output),
                     "Config: KEY_UP Button: %03d",
                     code);
        }
    }
    else if (event.type == SDL_EVENT_KEY_DOWN ||
             event.type == SDL_EVENT_KEY_UP)
    {
        st.keyboard_mode = 1;

        snprintf(st.line, sizeof(st.line),
                 "Scancode: %s",
                 SDL_GetKeyName(event.key.key));

        snprintf(st.output, sizeof(st.output),
                 "Config: KEY_[ACT] = %s 0 0",
                 sdl3_key(event.key.key));
    }

    if (!st.keyboard_mode && st.active_js >= 0 && st.sticks)
    {
        const char* name = SDL_GetJoystickName(st.sticks[st.active_js]);
        if (name) title = name;
    }

    SDL_SetRenderDrawColor(r, 0xB8, 0x02, 0x02, 0xFF);
    SDL_RenderClear(r);

    SDL_SetRenderDrawColor(r, 0xFF, 0xFF, 0xFF, 0xFF);

    SDL_RenderDebugText(r, center_x(screen_w, title), 40, title);
    SDL_RenderDebugText(r, center_x(screen_w, st.line), 70, st.line);
    SDL_RenderDebugText(r, center_x(screen_w, st.output), 100, st.output);

    SDL_RenderDebugText(r, 8, 150, "(SDL3)");
    SDL_RenderDebugText(r, 64, 150, version);
    SDL_RenderDebugText(r, 290, 150, "ESC to quit");

    SDL_RenderPresent(r);
}

#ifdef WIN32
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    (void)hInstance;
    (void)hPrevInstance;
    (void)lpCmdLine;
    (void)nCmdShow;
#else
int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;
#endif

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK))
    {
#ifdef WIN32
       MessageBox(NULL,"Unable to initialize SDL", "Encountered an error", MB_OK | MB_ICONERROR);
#else
        SDL_Log("SDL init failed: %s", SDL_GetError());
#endif
        return 1;
    }

    int count = 0;
    SDL_JoystickID* ids = SDL_GetJoysticks(&count);

    if (!ids || count <= 0)
    {
#ifdef WIN32
       MessageBox(NULL,"No joysticks found", "Encountered an error", MB_OK | MB_ICONERROR);
#else
       SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "No joysticks found", NULL);
#endif
        SDL_free(ids);
        SDL_Quit();
        return 1;
    }

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (!SDL_CreateWindowAndRenderer(
            "Hypseus SDL3 Joystick API Calculator",
            0x180, 0xA6,
            SDL_WINDOW_ALWAYS_ON_TOP,
            &window, &renderer))
    {
#ifdef WIN32
       MessageBox(NULL, SDL_GetError(), "Encountered an error", MB_OK | MB_ICONERROR);
#else
       SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", SDL_GetError(), NULL);
#endif
        SDL_free(ids);
        SDL_Quit();
        return 1;
    }

    SDL_Joystick** sticks =
        (SDL_Joystick**)SDL_calloc(count, sizeof(SDL_Joystick*));

    for (int i = 0; i < count; i++)
        sticks[i] = SDL_OpenJoystick(ids[i]);

    SlotMapping st;
    st.count = count;
    st.ids = ids;
    st.sticks = sticks;

    SDL_Event event;

    const int SCREEN_W = 0x180;

    while (true)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                goto quit;

            if (event.type == SDL_EVENT_KEY_DOWN &&
                event.key.key == SDLK_ESCAPE)
                goto quit;

            render_mapper(renderer, st, SCREEN_W, VERSION, event);
        }

        SDL_Delay(1);
    }

quit:

    for (int i = 0; i < count; i++)
        if (sticks[i])
            SDL_CloseJoystick(sticks[i]);

    SDL_free(sticks);
    SDL_free(ids);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

