#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <iostream>
#include "libtcod.hpp"
#include "Map.hpp"
#include "Entity.hpp"

enum eKeyPress {
	LEFT = 1,
	RIGHT,
	DOWN,
	UP
};

enum eGameStatus {
	STARTUP,
	PLAYER_MOVE,
	NEWTURN,
	DEFEAT,
	VICTORY
};

class Engine {
	private:
		eGameStatus gameStatus;
		eKeyPress keyPress; 

		int screenWidth, screenHeight;
		const char *title;

		Map *map;
		cTempPlayer player;
//		cEntityManager entityManager;
		TCOD_key_t key;
//		TCOD_mouse_t mouse;
	public:
		Engine (int screenWidth, int screenHeight, const char *title);
		~Engine (void);

		void update (void);
		void render (void);

		// If you want to add a player action, do it through this function.
		void getPlayerInput (void);

};


#endif
