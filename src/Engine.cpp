#include "Engine.hpp"

Engine::Engine (int screenWidth, int screenHeight, const char *title):
		screenWidth(screenWidth), screenHeight(screenHeight), title(title) {
	TCODConsole::setCustomFont ("./terminal8x8_gs_tc.png", 
			TCOD_FONT_LAYOUT_TCOD, 32, 8);
	TCODConsole::initRoot (screenWidth, screenHeight, title, false);
	gameStatus = STARTUP;
	map = new Map (screenWidth, screenHeight);
	player.symbol = '@';
	player.posx = screenWidth/2;
	player.posy = screenHeight/2;
}

Engine::~Engine (void) {
	if (map) delete map;
}

void Engine::update (void) {
	if (gameStatus == STARTUP) {
	}
	gameStatus = PLAYER_MOVE;
	getPlayerInput();
	switch (gameStatus) {
		case NEWTURN:
			break;
		case DEFEAT:
			break;
		case VICTORY:
			break;
		default:
			break;
	}
}

void Engine::render (void) {
	TCODConsole::root->clear();
	map->render();
	TCODConsole::root->putCharEx (player.posx, player.posy, '@', TCODColor::white, TCODColor::black);
}

void Engine::getPlayerInput (void) {
	TCODSystem::checkForEvent (TCOD_EVENT_KEY_PRESS, &key, NULL);
	switch (key.vk) {
		case TCODK_LEFT:
			player.update (-1,0);
			std::cout << key.c;
			break;
		case TCODK_RIGHT:
			player.update (1,0);
			break;
		case TCODK_UP:
			player.update (0,-1);
			break;
		case TCODK_DOWN:
			player.update (0,1);
			break;
		case TCODK_CHAR:
			switch (key.c) {
				case 'h':
					player.update (-1,0);
					break;
				case 'l':
					player.update (1,0);
					break;
				case 'k':
					player.update (0,-1);
					break;
				case 'j':
					player.update (0,1);
					break;
				case 'y':
					player.update (-1,-1);
					break;
				case 'u':
					player.update (1,-1);
					break;
				case 'b':
					player.update (-1,1);
					break;
				case 'n':
					player.update (1,1);
					break;
				default:
					break;
			}
		default:
			break;
	}
}
/*
void Engine::getPlayerInput (void) {
	TCODSystem::checkForEvent (TCOD_EVENT_KEY_PRESS, &key, NULL);
	switch (key.vk) {
		case TCODK_LEFT:
			keyPress = LEFT;
			break;
		case TCODK_RIGHT:
			keyPress = RIGHT;
			break;
		case TCODK_UP:
			keyPress = UP;
			break;
		case TCODK_DOWN:
			keyPress = DOWN;
			break;
		case TCODK_CHAR:
			switch (key.c) {
				case 'h':
					keyPress = LEFT;
					break;
				case 'l':
					keyPress = RIGHT;
					break;
				case 'k':
					keyPress = UP;
					break;
				case 'j':
					keyPress = DOWN;
					break;
				case 'y':
					keyPress = LEFT;
					break;
				case 'u':
					keyPress = LEFT;
					break;
				case 'b':
					keyPress = LEFT;
					break;
				case 'n':
					keyPress = LEFT;
					break;
				default:
					break;
			}
		default:
			break;
	}
	switch (keyPress) {
		case LEFT:
			case
			break;
}
*/
