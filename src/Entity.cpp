#include "libtcod.hpp"
#include "Entity.hpp"

void cTempPlayer::update (short dx, short dy) {
	if (dx != 0)
		posx += dx;
	if (dy != 0)
		posy += dy;
}
