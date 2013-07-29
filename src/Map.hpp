#ifndef MAP_HPP
#define MAP_HPP

#include "libtcod.hpp"

class cTile {
	protected:
		enum eTileType {
			NONE,
			FLOOR,
			WALL,
			TRAP
		} tileType;
		int symbol;
		bool canWalkThrough,
			 canSeeThrough;
//		bool isExplored;
//		TCODColor inFOV,
//				  notInFOV;
	public:
		cTile (void) {;}

//		void setProperties (int character, const TCODColor &colInFOV, const TCODColor &colNotInFOV) {
//			setSymbol (character);
//			setColorsInFOV(colInFOV);
//			setColorNotInFOV(colNotInFOV);
//		}
//		void toggleExplored (void) {isExplored = !(isExplored);}
		virtual int returnSymbol (void) = 0;
		virtual void update (void) = 0;
//		bool returnIsExplored (void) {return isExplored;}
//		TCODColor& returnColor (bool isInFOV) {
//			if (isInFOV)
//				return inFOV;
//			return notInFOV;
//		}
};

class cWall: public cTile {
	public:
		cWall (void) {
			tileType = WALL;
			symbol = '#';
			canWalkThrough = false;
			canSeeThrough = false;
		}
		int returnSymbol (void) {return symbol;}
		void update (void) {;}
};

class cFloor: public cTile {
	public:
		cFloor (void) {
			tileType = FLOOR;
			symbol = '.';
			canWalkThrough = true;
			canSeeThrough = true;
		}
		int returnSymbol (void) {return symbol;}
		void update (void) {;}
};

class cTrap: public cTile {
	private:
		bool hidden;
		int hiddenSymbol;
	public:
		cTrap (void) {
			tileType = TRAP;
			hidden = true;
			hiddenSymbol = '^';
			symbol = '.';
			canWalkThrough = true;
			canSeeThrough = true;
		}
		int returnSymbol (void) {
			return (hidden?symbol:hiddenSymbol);
		}
		void update (void) {
			hidden = false;
		}
};

class Map {
	private:
		int mapWidth, mapHeight;
//		TCODMap *tcodMap;
// TODO: try making this a vector instead of an array (then you can use the
// at() functions to more safely access things).
		cTile ***tile;
	public:
		Map (int mapWidth, int mapHeight);
//		void update (void);
		void render (void);
};

void testingRoom (int width, int height, cTile ***tileMap);

//#include "Tile.hpp"

/*
struct ColorSet {
	TCODColor inFOV,
			  notInFOV;
};

class Map {
	public:
		enum ColorScheme {
			CAVE,
			FOREST
		} colorScheme;
		enum MapGenAlgo {
			TESTINGROOM,
			CELLAUTO
		} mapGenAlgo;

		int width, height;
		ColorSet *colorSet;
		TCODMap *tcodMap;
		TileMap *tileMap;

		Map (int width, int height, int mapGenType = 0, int colScheme = 1);
		~Map();
		void update (void);
		void render(void) const;
	private:
};
*/
/*
// sValue == searchValue, fValue == fillValue
void scanLineFloodFill (int x, int y, int xUpper, int yUpper,
		int **countArray, int sValue, int fValue);

// Uses single color set. Don't use for transition areas.
void cellAuto (int width, int height, TCODMap *tcodMap, TileMap *tileMap,
		ColorSet *colorSet);
void testingRoom (int width, int height, TCODMap *tcodMap, TileMap *tileMap,
		ColorSet *colorSet);
*/
#endif
