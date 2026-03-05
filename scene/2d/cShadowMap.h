#pragma once

#include "tile_map_layer.h"

#include <vector>

enum EShadowMapType {
	E_SHADOWMAP,
	E_BUFFER,
	E_ITEMRANGE,
};

class cShadowMap : public TileMapLayer {
	GDCLASS(cShadowMap, TileMapLayer)

public:
	EShadowMapType shadowMapType;

	void setShadowMapType(EShadowMapType type);
	EShadowMapType getShadowMapType();

	float rayLength = 400;

	int roundSzie = 10;

	Rect2i mapRect = Rect2i(0, 0, 40, 40);
	void set_mapRect(Rect2i inMapRect);
	Rect2i get_mapRect();

	void set_rayLength(float in_rayLength);
	float get_rayLength();

	unsigned int colMask = 0;

	void set_colMask(unsigned int inColMask);
	unsigned int get_colMask();

	Vector2i blackTileAltasPos;

	Vector2i halfBlackTileAltasPos = Vector2i(0, 2);

	void set_blackTileAltasPos(Vector2i inBlackTileAltasPob);
	Vector2i get_blackTileAltasPos();

	int blackTileSourceId;
	void set_blackTileSourceId(int inBlackTileSourceId);
	int get_blackTileSourceId();

	void update_noCol(Vector2i midPos, int newRange = 10);

	void update_noColCircle(Vector2i inMidPos, int newRange = 10);

	void update_noColSquare(Vector2i inMidPos, int newRange = 10);

	void update_specialBuff(TypedArray<Vector2i> inRange);

	void update_specialBuffSignleCell(TypedArray<Vector2i> inRange);

	TypedArray<Vector2i> indexTilePosMap;

	void init();

	void resize(Vector2i newSize);

	int getTileIndex(Vector2i inPos);

	void fill();

	void hideShow();

	void collisionDispose();

protected:
	static void _bind_methods();

private:
	std::vector<int> allTileData;

	TypedArray<Vector2i> showTileArr;

	Vector2i midPos;
};

VARIANT_ENUM_CAST(EShadowMapType);
