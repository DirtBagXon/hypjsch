/*
 * ____ HYPSEUS COPYRIGHT NOTICE ____
 *
 * Copyright (C) 2022 DirtBagXon
 *
 * This file is part of HYPSEUS SINGE, a laserdisc arcade game emulator
 *
 * HYPSEUS SINGE is free software"; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation"; either version 2 of the License, or
 * (at your option) any later version.
 *
 * HYPSEUS SINGE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY"; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program"; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_joystick.h>
#include <string>

const char* sdl3_key(int key)
{
	if (key == SDLK_BACKSPACE) return "SDLK_BACKSPACE";
	else if (key == SDLK_TAB) return "SDLK_TAB";
	else if (key == SDLK_RETURN) return "SDLK_RETURN";
	else if (key == SDLK_ESCAPE) return "SDLK_ESCAPE";
	else if (key == SDLK_SPACE) return "SDLK_SPACE";
	else if (key == SDLK_HASH) return "SDLK_HASH";
	else if (key == SDLK_APOSTROPHE) return "SDLK_QUOTE";
	else if (key == SDLK_COMMA) return "SDLK_COMMA";
	else if (key == SDLK_MINUS) return "SDLK_MINUS";
	else if (key == SDLK_PERIOD) return "SDLK_PERIOD";
	else if (key == SDLK_APPLICATION) return "SDLK_APPLICATION";
	else if (key == SDLK_SLASH) return "SDLK_SLASH";
	else if (key == SDLK_0) return "SDLK_0";
	else if (key == SDLK_1) return "SDLK_1";
	else if (key == SDLK_2) return "SDLK_2";
	else if (key == SDLK_3) return "SDLK_3";
	else if (key == SDLK_4) return "SDLK_4";
	else if (key == SDLK_5) return "SDLK_5";
	else if (key == SDLK_6) return "SDLK_6";
	else if (key == SDLK_7) return "SDLK_7";
	else if (key == SDLK_8) return "SDLK_8";
	else if (key == SDLK_9) return "SDLK_9";
	else if (key == SDLK_SEMICOLON) return "SDLK_SEMICOLON";
	else if (key == SDLK_EQUALS) return "SDLK_EQUALS";
	else if (key == SDLK_LEFTBRACKET) return "SDLK_LEFTBRACKET";
	else if (key == SDLK_RIGHTBRACKET) return "SDLK_RIGHTBRACKET";
	else if (key == SDLK_BACKSLASH) return "SDLK_BACKSLASH";
	else if (key == SDLK_GRAVE) return "SDLK_BACKQUOTE";
	else if (key == SDLK_A) return "SDLK_A";
	else if (key == SDLK_B) return "SDLK_B";
	else if (key == SDLK_C) return "SDLK_C";
	else if (key == SDLK_D) return "SDLK_D";
	else if (key == SDLK_E) return "SDLK_E";
	else if (key == SDLK_F) return "SDLK_F";
	else if (key == SDLK_G) return "SDLK_G";
	else if (key == SDLK_H) return "SDLK_H";
	else if (key == SDLK_I) return "SDLK_I";
	else if (key == SDLK_J) return "SDLK_J";
	else if (key == SDLK_K) return "SDLK_K";
	else if (key == SDLK_L) return "SDLK_L";
	else if (key == SDLK_M) return "SDLK_M";
	else if (key == SDLK_N) return "SDLK_N";
	else if (key == SDLK_O) return "SDLK_O";
	else if (key == SDLK_P) return "SDLK_P";
	else if (key == SDLK_Q) return "SDLK_Q";
	else if (key == SDLK_R) return "SDLK_R";
	else if (key == SDLK_S) return "SDLK_S";
	else if (key == SDLK_T) return "SDLK_T";
	else if (key == SDLK_U) return "SDLK_U";
	else if (key == SDLK_V) return "SDLK_V";
	else if (key == SDLK_W) return "SDLK_W";
	else if (key == SDLK_X) return "SDLK_X";
	else if (key == SDLK_Y) return "SDLK_Y";
	else if (key == SDLK_Z) return "SDLK_Z";
	else if (key == SDLK_CAPSLOCK) return "SDLK_CAPSLOCK";
	else if (key == SDLK_DELETE) return "SDLK_DELETE";
	else if (key == SDLK_F1) return "SDLK_F1";
	else if (key == SDLK_F2) return "SDLK_F2";
	else if (key == SDLK_F3) return "SDLK_F3";
	else if (key == SDLK_F4) return "SDLK_F4";
	else if (key == SDLK_F5) return "SDLK_F5";
	else if (key == SDLK_F6) return "SDLK_F6";
	else if (key == SDLK_F7) return "SDLK_F7";
	else if (key == SDLK_F8) return "SDLK_F8";
	else if (key == SDLK_F9) return "SDLK_F9";
	else if (key == SDLK_F10) return "SDLK_F10";
	else if (key == SDLK_F11) return "SDLK_F11";
	else if (key == SDLK_F12) return "SDLK_F12";
	else if (key == SDLK_SCROLLLOCK) return "SDLK_SCROLLLOCK";
	else if (key == SDLK_PAUSE) return "SDLK_PAUSE";
	else if (key == SDLK_INSERT) return "SDLK_INSERT";
	else if (key == SDLK_HOME) return "SDLK_HOME";
	else if (key == SDLK_PAGEUP) return "SDLK_PAGEUP";
	else if (key == SDLK_END) return "SDLK_END";
	else if (key == SDLK_PAGEDOWN) return "SDLK_PAGEDOWN";
	else if (key == SDLK_RIGHT) return "SDLK_RIGHT";
	else if (key == SDLK_LEFT) return "SDLK_LEFT";
	else if (key == SDLK_DOWN) return "SDLK_DOWN";
	else if (key == SDLK_UP) return "SDLK_UP";
	else if (key == SDLK_NUMLOCKCLEAR) return "SDLK_NUMLOCKCLEAR";
	else if (key == SDLK_KP_DIVIDE) return "SDLK_KP_DIVIDE";
	else if (key == SDLK_KP_MULTIPLY) return "SDLK_KP_MULTIPLY";
	else if (key == SDLK_KP_MINUS) return "SDLK_KP_MINUS";
	else if (key == SDLK_KP_PLUS) return "SDLK_KP_PLUS";
	else if (key == SDLK_KP_ENTER) return "SDLK_KP_ENTER";
	else if (key == SDLK_KP_1) return "SDLK_KP_1";
	else if (key == SDLK_KP_2) return "SDLK_KP_2";
	else if (key == SDLK_KP_3) return "SDLK_KP_3";
	else if (key == SDLK_KP_4) return "SDLK_KP_4";
	else if (key == SDLK_KP_5) return "SDLK_KP_5";
	else if (key == SDLK_KP_6) return "SDLK_KP_6";
	else if (key == SDLK_KP_7) return "SDLK_KP_7";
	else if (key == SDLK_KP_8) return "SDLK_KP_8";
	else if (key == SDLK_KP_9) return "SDLK_KP_9";
	else if (key == SDLK_KP_0) return "SDLK_KP_0";
	else if (key == SDLK_KP_PERIOD) return "SDLK_KP_PERIOD";
	else if (key == SDLK_VOLUMEUP) return "SDLK_VOLUMEUP";
	else if (key == SDLK_VOLUMEDOWN) return "SDLK_VOLUMEDOWN";
	else if (key == SDLK_LCTRL) return "SDLK_LCTRL";
	else if (key == SDLK_LSHIFT) return "SDLK_LSHIFT";
	else if (key == SDLK_LALT) return "SDLK_LALT";
	else if (key == SDLK_LGUI) return "SDLK_LGUI";
	else if (key == SDLK_RCTRL) return "SDLK_RCTRL";
	else if (key == SDLK_RSHIFT) return "SDLK_RSHIFT";
	else if (key == SDLK_RALT) return "SDLK_RALT";
	else if (key == SDLK_RGUI) return "SDLK_RGUI";
	else if (key == SDLK_MODE) return "SDLK_MODE";
	else {
		std::string s = std::to_string(key);
		const char *pchar = s.c_str();
		return pchar;
	}
}

const char* sdl3_hat(int key)
{
	if (key == SDL_HAT_CENTERED) return "SDL_HAT_CENTERED";
	else if (key == SDL_HAT_UP) return "SDL_HAT_UP";
	else if (key == SDL_HAT_RIGHT) return "SDL_HAT_RIGHT";
	else if (key == SDL_HAT_DOWN) return "SDL_HAT_DOWN";
	else if (key == SDL_HAT_LEFT) return "SDL_HAT_LEFT";
	else if (key == SDL_HAT_RIGHTUP) return "SDL_HAT_RIGHTUP";
	else if (key == SDL_HAT_RIGHTDOWN) return "SDL_HAT_RIGHTDOWN";
	else if (key == SDL_HAT_LEFTUP) return "SDL_HAT_LEFTUP";
	else if (key == SDL_HAT_LEFTDOWN) return "SDL_HAT_LEFTDOWN";
	else return "SDLK_UNKNOWN";
}
