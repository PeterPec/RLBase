#include "Map.hpp"

Map::Map (int mapWidth, int mapHeight): mapWidth(mapWidth),
		mapHeight(mapHeight) {
	tile = new cTile**[mapWidth];
	for (int i = 0; i < mapWidth; i++)
		tile[i] = new cTile*[mapHeight];
	testingRoom (mapWidth, mapHeight, tile);
}

void testingRoom (int width, int height, cTile ***tileMap) {
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
//			tileMap[i][j].setProperties('.',TCODColor::red, TCODColor::yellow);
			tileMap[i][j] = new cTrap;
}

/*
Map::Map(int width, int height, int mapGenType,
		int colScheme): width(width), height(height) {
	colorScheme = ColorScheme(colScheme);
	mapGenAlgo = MapGenAlgo(mapGenType);
	switch (colorScheme) {
		case CAVE:
			colorSet = new ColorSet;
			colorSet->inFOV = TCODColor::lightGrey;
			colorSet->notInFOV = TCODColor::darkGrey;
			break;
		case FOREST:
			colorSet = new ColorSet;
			colorSet->inFOV = TCODColor::lightGreen;
			colorSet->notInFOV = TCODColor::darkGreen;
			break;
	};
	tcodMap = new TCODMap (width, height);
	tileMap = new TileMap (width, height);
	// TODO: CREATE SOMETHING TO DETERMINE THE COLOR SCHEME AND THE
	// ALGORIGTHMS TO USE
	switch (mapGenAlgo) {
		case TESTINGROOM:
			testingRoom (width, height, tcodMap, tileMap, colorSet);
			break;
		case CELLAUTO:
			cellAuto (width, height, tcodMap, tileMap, colorSet);
			break;
		default:
			break;
	};
}

Map::~Map () {
	delete tileMap;
	delete tcodMap;
}

void Map::update (void) {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (!tileMap->isExplored (i, j))
				if (tcodMap->isInFov (i, j))
					tileMap->setExplored (i, j, true);
		}
	}
}
*/

void Map::render (void) {
	for (int i = 0; i < mapWidth; i++) {
		for (int j = 0; j < mapHeight; j++) {
			/*
			if (tileMap->isExplored(i,j)) {
				if (tcodMap->isInFov(i,j))
					TCODConsole::root->putCharEx (i, j,
							tileMap->returnCharacter (i, j),
							tileMap->returnColor (i, j, true),
							TCODColor::black);
				else
					TCODConsole::root->putCharEx (i, j,
							tileMap->returnCharacter (i, j),
							tileMap->returnColor (i, j, false),
							TCODColor::black);
			}
		*/
			// This will render the entire map on the screen.
			TCODConsole::root->putCharEx (i,j, tile[i][j]->returnSymbol(), 
					TCODColor::grey, TCODColor::black);
		}
	}
}

/*
void scanLineFloodFill (int x, int y, int xUpper, int yUpper, 
		int **countArray, int sValue, int fValue) {
	if (x < 0 || x >= xUpper || y < 0 || y >= yUpper)
		return;
	if (countArray[x][y] != sValue)
		return;

	// Fill a vertical line
	int y1 = y;
	while (y1 < yUpper && countArray[x][y1] == sValue) {
		countArray[x][y1] = fValue;
		y1++;
	}
	y1 = y - 1;
	while (y1 >= 0 && countArray [x][y1] == sValue) {
		countArray[x][y1] = fValue;
		y1--;
	}

	// Moving Downwards (increasing y)
		//Check left
	y1 = y;
	while (y1 < yUpper && countArray[x][y1] == fValue) {
		if (x > 0 && countArray[x-1][y1] == sValue)
			scanLineFloodFill (x-1, y1, xUpper, yUpper, countArray,
					sValue, fValue);
		y1++;
	}
		//Check left-up
	y1 = y;
	while (y1 < yUpper && countArray[x][y1] == fValue) {
		if (x > 0 && y1 > 0 && countArray[x-1][y1-1] == sValue)
			scanLineFloodFill (x-1, y1-1, xUpper, yUpper, countArray,
					sValue, fValue);
		y1++;
	}
		//Check left-down
	y1 = y;
	while (y1 < yUpper && countArray[x][y1] == fValue) {
		if (x > 0 && y1 < yUpper - 1 && countArray[x-1][y1+1] == sValue)
			scanLineFloodFill (x-1, y1+1, xUpper, yUpper, countArray,
					sValue, fValue);
		y1++;
	}
		//Check right
	y1 = y;
	while (y1 < yUpper && countArray[x][y1] == fValue) {
		if (x < xUpper - 1 && countArray[x+1][y1] == sValue)
			scanLineFloodFill (x+1, y1, xUpper, yUpper, countArray,
					sValue, fValue);
		y1++;
	}
		//Check right-up
	y1 = y;
	while (y1 < yUpper && countArray[x][y1] == fValue) {
		if (x < xUpper - 1 && y1 > 0 && countArray[x+1][y1-1] == sValue)
			scanLineFloodFill (x+1, y1-1, xUpper, yUpper, countArray,
					sValue, fValue);
		y1++;
	}
		//Check right-down
	y1 = y;
	while (y1 < yUpper && countArray[x][y1] == fValue) {
		if (x < xUpper - 1 && y1 < yUpper - 1 &&
				countArray[x+1][y1+1] == sValue)
			scanLineFloodFill (x+1, y1+1, xUpper, yUpper, countArray,
					sValue, fValue);
		y1++;
	}
	// Moving Upwards (decreasing y)
		//Check left
	y1 = y - 1;
	while (y1 >= 0 && countArray[x][y1] == fValue) {
		if (x > 0 && countArray[x-1][y1] == sValue)
			scanLineFloodFill (x-1, y1, xUpper, yUpper, countArray,
					sValue, fValue);
		y1--;
	}
		//Check left-up
	y1 = y - 1;
	while (y1 >= 0 && countArray[x][y1] == fValue) {
		if (x > 0 && y1 > 0 && countArray[x-1][y1-1] == sValue)
			scanLineFloodFill (x-1, y1-1, xUpper, yUpper, countArray,
					sValue, fValue);
		y1--;
	}
		//Check left-down
	y1 = y - 1;
	while (y1 >= 0 && countArray[x][y1] == fValue) {
		if (x > 0 && y1 < yUpper - 1 && countArray[x-1][y1+1] == sValue)
			scanLineFloodFill (x-1, y1+1, xUpper, yUpper, countArray,
					sValue, fValue);
		y1--;
	}
		//Check right
	y1 = y - 1;
	while (y1 >= 0 && countArray[x][y1] == fValue) {
		if (x < xUpper - 1 && countArray[x+1][y1] == sValue)
			scanLineFloodFill (x+1, y1, xUpper, yUpper, countArray,
					sValue, fValue);
		y1--;
	}
		//Check right-up
	y1 = y - 1;
	while (y1 >= 0 && countArray[x][y1] == fValue) {
		if (x < xUpper - 1 && y1 > 0 && countArray[x+1][y1-1] == sValue)
			scanLineFloodFill (x+1, y1-1, xUpper, yUpper, countArray,
					sValue, fValue);
		y1--;
	}
		//Check right-down
	y1 = y - 1;
	while (y1 >= 0 && countArray[x][y1] == fValue) {
		if (x < xUpper - 1 && y1 < yUpper - 1 &&
				countArray[x+1][y1+1] == sValue)
			scanLineFloodFill (x+1, y1+1, xUpper, yUpper, countArray,
					sValue, fValue);
		y1--;
	}
}


void cellAuto (int width, int height, TCODMap *tcodMap, TileMap *tileMap, 
		ColorSet *colorSet) {
	tileMap->setDefaultColors (colorSet->inFOV, colorSet->notInFOV);

	// This is setting the border to be made of WALL
	for (int i = 0; i < width; i++) {
		tileMap->setProperties (i, 0, TileProperties::WALL, '#');
		tcodMap->setProperties (i, 0, false, false);
		tileMap->setProperties (i, height-1, TileProperties::WALL, '#');
		tcodMap->setProperties (i, height-1, false, false);
	}
	for (int j = 0; j < height; j++) {
		tileMap->setProperties (0, j, TileProperties::WALL, '#');
		tcodMap->setProperties (0, j, false, false);
		tileMap->setProperties (width-1, j, TileProperties::WALL, '#');
		tcodMap->setProperties (width-1, j, false, false);
	}

	// This fills the inside part with random entries of WALL and FLOOR
	TCODRandom *numGen = TCODRandom::getInstance();
	for (int i = 1; i < width - 1; i++) {
		for (int j = 1; j < height - 1; j++) {
			if (numGen->getInt (0, 99) <= 45)
				tileMap->setProperties (i, j, TileProperties::WALL, '#');
			else
				tileMap->setProperties (i, j, TileProperties::FLOOR, '.');
		}
	}
	int **countArray = new int*[width-2];
	for (int i = 0; i < width - 2; i++)
		countArray[i] = new int[height-2];
	int count = 0;
	
	// This is the actual cellular automata part. The first for loop is how
	// many times the cellAuto part will be done on the map.
	for (int z = 0; z < 4; z++) {
		for (int i = 1; i < width - 1; i++) {
			for (int j = 1; j < height - 1; j++) {
				for (int k = -1; k <= 1; k++) {
					for (int l = -1; l <= 1; l++) {
						if (k == 0 && l == 0)
							continue;
						if (tileMap->returnTileType (i + k, j + l) == TileProperties::WALL)
							count++;
					}
				}
				countArray[i-1][j-1] = count;
				count = 0;
			}
		}
		for (int i = 1; i < width - 1; i++) {
			for (int j = 1; j < height - 1; j++) {
				if (tileMap->returnTileType (i, j) == TileProperties::WALL)
					countArray[i-1][j-1] >= 4?
						tileMap->setProperties (i, j, TileProperties::WALL, '#') :
						tileMap->setProperties (i, j, TileProperties::FLOOR, '.');
				else
					countArray[i-1][j-1] >= 5 ?
						tileMap->setProperties (i, j, TileProperties::WALL, '#') :
						tileMap->setProperties (i, j, TileProperties::FLOOR, '.');
			}
		}
	}
	for (int i = 1; i < width - 1; i++) {
		for (int j = 1; j < height - 1; j++) {
			if (tileMap->returnTileType (i, j) == TileProperties::WALL) {
				countArray[i-1][j-1] = TileProperties::WALL;
				tcodMap->setProperties (i, j, false, false);
			}
			else {
				countArray[i-1][j-1] = TileProperties::FLOOR;
				tcodMap->setProperties (i, j, true, true);
			}
		}
	}

	// Beginning the flood fill to determine the largest section and where to
	// place the stairs/ramps, etc.
	int fValue = TileProperties::FLOOR + 1;
	for (int i = 0; i < width - 2; i++) {
		for (int j = 0; j < height - 2; j++) {
			if (countArray[i][j] == TileProperties::FLOOR) {
				scanLineFloodFill (i, j, width - 2, height - 2, countArray,
						TileProperties::FLOOR, fValue);
				fValue++;
			}
		}
	}
	int areaArraySize = fValue;
	int *areaArray = new int[areaArraySize];
	for (int i = 0; i < areaArraySize; i++)
		areaArray[i] = 0;
	for (int i = 0; i < width - 2; i++)
		for (int j = 0; j < height - 2; j++)
			areaArray[countArray[i][j]] += 1;
	int value = 0;
	int largestArea = 0;
	for (int i = TileProperties::FLOOR + 1; i < areaArraySize; i++) {
		if (areaArray[i] > largestArea) {
			largestArea = areaArray[i];
			value = i;
		}
	}
	int stairCasePairs = 1;
	for (int i = 0; i < stairCasePairs * 2; i++) {
		bool isOpenArea;
		int x, y;
		do {
			isOpenArea = true;
			x = numGen->getInt (0, width - 3);
			y = numGen->getInt (0, height - 3);
			for (int j = -1; j <= 1; j++) {
				for (int k = -1; k <= 1; k++) {
					if (isOpenArea) {
						if (x + j < 0 || x + j >= width - 2 ||
								y + k < 0 || y + k >= height - 2)
							isOpenArea = false;
						else if (countArray[x+j][y+k] != value)
							isOpenArea = false;
					}
				}
			}
		} while (countArray[x][y] != value || !isOpenArea);
		if (i % 2 == 0) {
		tileMap->setProperties (x + 1, y + 1, TileProperties::UPSTAIRS, '<');
		tcodMap->setProperties (x + 1, y + 1, true, false);
		}
		else if (i % 2 == 1) {
			tileMap->setProperties (x + 1, y + 1, TileProperties::DOWNSTAIRS, '>');
			tcodMap->setProperties (x + 1, y + 1, true, false);
		}
	}
}

void testingRoom (int width, int height, TCODMap *tcodMap, TileMap *tileMap,
		ColorSet *colorSet) {
	tileMap->setDefaultColors (colorSet->inFOV, colorSet->notInFOV);

	// This is setting the border to be made of WALL
	for (int i = 0; i < width; i++) {
		tileMap->setProperties (i, 0, TileProperties::WALL, '#');
		tcodMap->setProperties (i, 0, false, false);
		tileMap->setProperties (i, height-1, TileProperties::WALL, '#');
		tcodMap->setProperties (i, height-1, false, false);
	}
	for (int j = 0; j < height; j++) {
		tileMap->setProperties (0, j, TileProperties::WALL, '#');
		tcodMap->setProperties (0, j, false, false);
		tileMap->setProperties (width-1, j, TileProperties::WALL, '#');
		tcodMap->setProperties (width-1, j, false, false);
	}
	for (int i = 1; i < width - 1; i++) {
		for (int j = 1; j < height - 1; j++) {
			tileMap->setProperties (i, j, TileProperties::FLOOR, '.');
			tcodMap->setProperties (i, j, true, true);
		}
	}
}
*/
