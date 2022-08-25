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
 * g++ hypjsch_cli.cpp -lSDL2 -o hypjsch_cli
 *
 */

#include <SDL2/SDL.h>
#include <cinttypes>
#include "keycodes.h"

int main(int argc, char *argv[]) {

    if (SDL_Init(SDL_INIT_JOYSTICK) != 0) {
       SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
       exit(1);
    }

    SDL_Joystick *joystick;
    const char ega[30] = "KEY_DOWN = SDLK_DOWN 0 0";
    const char egb[30] = "KEY_QUIT = SDLK_ESCAPE 0";
    const char e[44] = "(Third column provides example config only)";
    int n = 0x0a, t = 0x09, len = 0x28;
    char j[len] = {};
    int index = 0;

    if (SDL_NumJoysticks() == 0) {
       fprintf(stderr, "No joysticks found%c", n);
       SDL_Quit();
       exit(1);
    } else {
       fprintf(stdout, "%c%d joystick(s) found - ", n, SDL_NumJoysticks());
       fprintf(stdout, "%s%c%c", e, n, n);
    }

    SDL_Event event;
    while (1) {

        SDL_WaitEvent(&event);
        if (event.type == SDL_QUIT) {
            break;
        }

        for (int i=0; i < SDL_NumJoysticks(); i++) {

          if (SDL_NumJoysticks() == 0) break;
          joystick = SDL_JoystickOpen(i);

          if (joystick == NULL) break;
          index = event.jaxis.which * 0x64;
          strncpy (j, SDL_JoystickNameForIndex(i), len);
          j[len] = '\0';

          if (event.type == SDL_JOYAXISMOTION && event.jaxis.which == i) {

             if (abs(event.jaxis.value) > JITTER) {
                if (event.jaxis.axis > 0x63) { // 3 digit input codes
                   index = index * 0x64;
                   fprintf (stdout, "%s:%c", j, t);
                   fprintf (stdout, "Axis: %04i%c- ", event.jaxis.axis + 1 + index, t);
                   if (event.jaxis.value < 0) fprintf (stdout, "%s -%04i%c", ega, event.jaxis.axis + 1 + index, n);
                   else fprintf (stdout, "%s +%04i%c", ega, event.jaxis.axis + 1 + index, n);
                }
                else
                {
                   fprintf (stdout, "%s:%c", j, t);
                   fprintf (stdout, "Axis: %03i%c- ", event.jaxis.axis + 1 + index, t);
                   if (event.jaxis.value < 0) fprintf (stdout, "%s -%03i%c", ega, event.jaxis.axis + 1 + index, n);
                   else fprintf (stdout, "%s +%03i%c", ega, event.jaxis.axis + 1 + index, n);
                }
             }

          } else if (event.type == SDL_JOYBUTTONDOWN && event.jbutton.which == i) {

             if (event.jbutton.button > 0x63) { // 3 digit input codes
                index = index * 0x64;
                fprintf (stdout, "%s:%c", j, t);
                fprintf (stdout, "Button: %04i%c- ", event.jbutton.button + 1 + index, t);
                fprintf (stdout, "%s %04i%c", egb, event.jbutton.button + 1 + index, n);
             }
             else
             {
                fprintf (stdout, "%s:%c", j, t);
                fprintf (stdout, "Button: %03i%c- ", event.jbutton.button + 1 + index, t);
                fprintf (stdout, "%s %03i%c", egb, event.jbutton.button + 1 + index, n);
             }
          }
       }
    }

    fprintf(stdout, "%c%s", n, e);
    fprintf(stdout, " - %s%c%c", VERSION, n, n);
    SDL_JoystickClose(joystick);
    SDL_Quit();
    return 0;
}
