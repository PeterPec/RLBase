#include "libtcod.hpp"
#include "Engine.hpp"

Engine engine (50, 50, "WH40K RR");

int main (void) {
	while (!TCODConsole::isWindowClosed()) {
		engine.update();
		engine.render();
		TCODConsole::flush();
	}
	return 0;
}
