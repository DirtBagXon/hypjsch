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
 * g++ keycodes.cpp hypjsch.cpp -lSDL2 -lSDL2_test -o hypjsch
 *
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_test_font.h>
#include <cinttypes>
#include "keycodes.h"

#ifdef WIN32
#include <windows.h>
#endif

int pos(int size, const char* word) {
     return ((size - (strlen(word)<<3))>>1);
}

int main(int argc, char *argv[]) {

    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK) != 0) {
#ifdef WIN32
       MessageBox(NULL,"Unable to initialize SDL", "Encountered an error", MB_OK | MB_ICONERROR);
#else
       SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
#endif
       exit(1);
    }

    if (SDL_NumJoysticks() == 0) {
#ifdef WIN32
       MessageBox(NULL,"No joysticks found", "Encountered an error", MB_OK | MB_ICONERROR);
#else
       SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "No joysticks found", NULL);
#endif
       SDL_Quit();
       exit(1);
    }

    Uint32 sdl_flags = 0;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    int size = 0x140, offset = 0x64;
    sdl_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_ALWAYS_ON_TOP;

    if (SDL_CreateWindowAndRenderer(size, size>>1, sdl_flags, &window, &renderer)) {
#ifdef WIN32
       MessageBox(NULL, SDL_GetError(), "Encountered an error", MB_OK | MB_ICONERROR);
#else
       SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", SDL_GetError(), NULL);
#endif
       SDL_Quit();
       exit(1);
    }

    SDL_SetWindowTitle(window, "Hypseus Config Value Calc");
    SDL_Joystick *joystick;

    const char ega[30] = "e.g. KEY_DOWN = SDLK_DOWN 0 0";
    const char egb[30] = "e.g. KEY_QUIT = SDLK_ESCAPE 0";
    const char egk[16] = "e.g. KEY_TEST =";
    int js = 0, kb = 0, index = 0;
    int ln = 0x4f, s = 0x28;
    char example[s] = {};
    char joy[s] = {};
    char button[s];
    char axis[s];
    char hat[s];
    char key[s];

    SDL_Event event;
    while (1) {

        if (SDL_NumJoysticks() == 0) break;

        SDL_SetRenderDrawColor(renderer, 0xb8, 0x2, 0x2, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        if (SDL_JoystickOpen(js) == NULL ) break;
        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, SDL_ALPHA_OPAQUE);

        if (kb) SDLTest_DrawString(renderer, pos(size, "Keyboard"), 0x23, "Keyboard");
        else {
           strncpy (joy, SDL_JoystickNameForIndex(js), s);
           joy[s] = '\0';
           SDLTest_DrawString(renderer, pos(size, joy), 0x23, joy);
        }

        SDL_WaitEvent(&event);
        if (event.type == SDL_QUIT) {
            break;
        } else if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_ESCAPE)
                break;
	}

        for (int i=0; i < SDL_NumJoysticks(); i++) {

          joystick = SDL_JoystickOpen(i);
          if (joystick == NULL) break;
          index = event.jaxis.which * offset;

          if (event.type == SDL_JOYAXISMOTION && event.jaxis.which == i) {

            js = i;
            kb = 0;

            if (event.jaxis.axis > 0x63) { // 3 digit input codes
               index = index * offset;
               snprintf (axis, sizeof(axis), "Axis:%04i %i", event.jaxis.axis + 1 + index, event.jaxis.value);
               if (event.jaxis.value < 0) snprintf (example, sizeof(example), "%s -%04i", ega, event.jaxis.axis + 1 + index);
               else snprintf (example, sizeof(example), "%s +%04i", ega, event.jaxis.axis + 1 + index);
            }
            else
            {
               snprintf (axis, sizeof(axis), "Axis:%03i %i", event.jaxis.axis + 1 + index, event.jaxis.value);
               if (event.jaxis.value < 0) snprintf (example, sizeof(example), "%s -%03i", ega, event.jaxis.axis + 1 + index);
               else snprintf (example, sizeof(example), "%s +%03i", ega, event.jaxis.axis + 1 + index);
            }

            SDLTest_DrawString(renderer, pos(size, axis), ln, axis);

          } else if (event.type == SDL_JOYBUTTONDOWN && event.jbutton.which == i) {

            js = i;
            kb = 0;

            if (event.jbutton.button > 0x63) { // 3 digit input codes
               index = index * offset;
               snprintf (button, sizeof(button), "Button: %04i", event.jbutton.button + 1 + index);
               snprintf (example, sizeof(example), "%s %04i", egb, event.jbutton.button + 1 + index);
            }
            else
            {
               snprintf (button, sizeof(button), "Button: %03i", event.jbutton.button + 1 + index);
               snprintf (example, sizeof(example), "%s %03i", egb, event.jbutton.button + 1 + index);
            }

            SDLTest_DrawString(renderer, pos(size, button), ln, button);

          } else if (event.type == SDL_JOYHATMOTION && event.jhat.hat == i) {

            js = event.jhat.which;
            kb = 0;

            snprintf (hat, sizeof(hat), "HAT: %s", sdl2_hat(event.jhat.value));
            example[0] = '\0';

            SDLTest_DrawString(renderer, pos(size, hat), ln, hat);

          } else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {

            kb = 1;

            snprintf (key, sizeof(key), "Key: %s", sdl2_key(event.key.keysym.sym));
            snprintf (example, sizeof(example), "%s %s 0 0", egk, sdl2_key(event.key.keysym.sym));

            SDLTest_DrawString(renderer, pos(size, key), ln, key);
          }
       }

       SDLTest_DrawString(renderer, pos(size, example), 0x78, example);
       SDLTest_DrawString(renderer, 0xe1, 0x96, "ESC to quit");
       SDL_RenderPresent(renderer);
    }

    SDL_JoystickClose(joystick);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
