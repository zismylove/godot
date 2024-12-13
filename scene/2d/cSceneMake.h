#pragma once
#include "node_2d.h"

class TileMapLayer;
class FastNoiseLite;
class TileSet;

enum ESCENE_MAKE_TYPE{
	EForest,
	EDesert,
};

class cSceneMake:public Node2D {
	GDCLASS(cSceneMake, Node2D);
public:

	ESCENE_MAKE_TYPE sceneType;

	Vector2i mapSize = Vector2i(50,50);

	TileSet* baseLayerTileSet;

	FastNoiseLite* baseLayerNoise;

	TileMapLayer* baseLayerTile;

};
