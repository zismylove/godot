#pragma once
#include "tile_map_layer.h"

#include <vector>

class cShadowMap:public TileMapLayer {
	GDCLASS(cShadowMap,TileMapLayer)
public:
	float rayLength = 400;

	int roundSzie = 10;

	void set_rayLength(float in_rayLength);
	float get_rayLength();

	unsigned int colMask = 0;

	void set_colMask(unsigned int inColMask);
	unsigned int get_colMask();

	Vector2i blackTileAltasPos;

	Vector2i halfBlackTileAltasPos=Vector2i(0,2);

	void set_blackTileAltasPos(Vector2i inBlackTileAltasPob);
	Vector2i get_blackTileAltasPos();

	int blackTileSourceId;
	void set_blackTileSourceId(int inBlackTileSourceId);
	int get_blackTileSourceId();

	void update_noCol(Vector2i midPos);

	TypedArray<Vector2i>indexTilePosMap;

	void init();

	int getTileIndex(Vector2i inPos);

protected:

	static void _bind_methods();

private:
	std::vector<int>allTileData;

	TypedArray<Vector2i>showTileArr;

};
