#include "cShadowMap.h"

void cShadowMap::set_rayLength(float in_rayLength) {
	rayLength = in_rayLength;
	roundSzie = rayLength;
}

float cShadowMap::get_rayLength() {
	return rayLength;
}

void cShadowMap::set_colMask(unsigned int inColMask) {
	colMask = inColMask;
}

unsigned int cShadowMap::get_colMask() {
	return colMask;
}

void cShadowMap::set_blackTileAltasPos(Vector2i inBlackTileAltasPob) {
	blackTileAltasPos = inBlackTileAltasPob;
}

Vector2i cShadowMap::get_blackTileAltasPos() {
	return blackTileAltasPos;
}

void cShadowMap::set_blackTileSourceId(int inBlackTileSourceId) {
	blackTileSourceId = inBlackTileSourceId;
}

int cShadowMap::get_blackTileSourceId() {
	return blackTileSourceId;
}

std::vector<std::pair<int, int>> getPointsInCircle(int centerX, int centerY, int radius) {
	std::vector<std::pair<int, int>> points;

	// 遍历包含圆的所有可能点的矩形区域


	return points;
}

void cShadowMap::update_noCol(Vector2i midPos) {

	Rect2i mapRect= get_used_rect();

	for (int i=0;i<showTileArr.size();i++) {
		Vector2i tilePos = showTileArr[i];
		set_cell(tilePos, blackTileSourceId, halfBlackTileAltasPos);
		int theArrIndex = tilePos.x *mapRect.size.x+tilePos.y;
		allTileData[theArrIndex] = 0;
	}

	int centerX = midPos.x;
	int centerY = midPos.y;

	int startX = centerX - roundSzie;
	int startY = centerX - roundSzie;

	int endX= centerX + roundSzie;
	int endY= centerY + roundSzie;

	if(startX<0)
		startX = 0;

	if(startY<0)
		startY = 0;

	if(endX>=mapRect.size.x)
		endX = mapRect.size.x-1;
	if(endY>=mapRect.size.y)
		endY = mapRect.size.y-1;

	showTileArr.clear();
	for (int x =startX; x <= endX; ++x) {
		for (int y = startY; y <= endY; ++y) {
			// 检查点 (i, j) 是否在圆内
			float dx = (float)x - (float)centerX;
			float dy = (float)y - (float)centerY;
			if (dx * dx + dy * dy <= (roundSzie * roundSzie)-0.5) {
				int theArrIndex = x*mapRect.size.x+y;
				allTileData[theArrIndex] = 1;
				showTileArr.push_back(Vector2i(x,y));
			}
		}
	}

	// for (int x = midPos.x - roundSzie; x < (midPos.x + roundSzie + 1); x++) {
	// 	for (int y = midPos.y - roundSzie; y < (midPos.y + roundSzie + 1); y++) {
	// 		float distance = Math::sqrt(Math::pow(2, (x + 0.5 - midPos.x)) + Math::pow(2, (y + 0.5 - midPos.y)));
	// 		if (distance <= roundSzie) {
	//
	// 			int theArrIndex = x*mapRect.size.x+y;
	// 			allTileData[theArrIndex] = 1;
	// 			showTileArr.push_back(Vector2i(x,y));
	// 		}
	// 	}
	// }

	for (auto &tilePos : showTileArr) {
		int tileMapIndex = getTileIndex(tilePos);
		Vector2i tileAltasPos = indexTilePosMap[tileMapIndex];
		set_cell(tilePos,blackTileSourceId,tileAltasPos);
	}

}

void cShadowMap::init() {

	Rect2i mapRect = get_used_rect();

	allTileData.resize(mapRect.size.x*mapRect.size.y);
	std::fill(allTileData.begin(), allTileData.end(), 0);

	indexTilePosMap.resize(257);

	indexTilePosMap.fill(Vector2i(0, 0));

	indexTilePosMap[0] = Vector2i(0, 1);
	indexTilePosMap[1] = Vector2i(1, 0);
	indexTilePosMap[4] = Vector2i(1, 1);
	indexTilePosMap[16] = Vector2i(1, 2);
	indexTilePosMap[64] = Vector2i(1, 3);

	indexTilePosMap[5] = Vector2i(2, 0);
	indexTilePosMap[20] = Vector2i(2, 1);
	indexTilePosMap[80] = Vector2i(2, 2);
	indexTilePosMap[65] = Vector2i(2, 3);

	indexTilePosMap[7] = Vector2i(3, 0);
	indexTilePosMap[28] = Vector2i(3, 1);
	indexTilePosMap[112] = Vector2i(3, 2);
	indexTilePosMap[193] = Vector2i(3, 3);

	indexTilePosMap[17] = Vector2i(4, 0);
	indexTilePosMap[68] = Vector2i(4, 2);

	indexTilePosMap[21] = Vector2i(5, 0);
	indexTilePosMap[84] = Vector2i(5, 1);
	indexTilePosMap[81] = Vector2i(5, 2);
	indexTilePosMap[69] = Vector2i(5, 3);

	indexTilePosMap[23] = Vector2i(6, 0);
	indexTilePosMap[92] = Vector2i(6, 1);
	indexTilePosMap[113] = Vector2i(6, 2);
	indexTilePosMap[197] = Vector2i(6, 3);

	indexTilePosMap[29] = Vector2i(7, 0);
	indexTilePosMap[116] = Vector2i(7, 1);
	indexTilePosMap[209] = Vector2i(7, 2);
	indexTilePosMap[71] = Vector2i(7, 3);

	indexTilePosMap[31] = Vector2i(8, 0);
	indexTilePosMap[124] = Vector2i(8, 1);
	indexTilePosMap[241] = Vector2i(8, 2);
	indexTilePosMap[199] = Vector2i(8, 3);

	indexTilePosMap[85] = Vector2i(9, 0);

	indexTilePosMap[87] = Vector2i(10, 0);
	indexTilePosMap[93] = Vector2i(10, 1);
	indexTilePosMap[117] = Vector2i(10, 2);
	indexTilePosMap[213] = Vector2i(10, 3);

	indexTilePosMap[95] = Vector2i(11, 0);
	indexTilePosMap[125] = Vector2i(11, 1);
	indexTilePosMap[245] = Vector2i(11, 2);
	indexTilePosMap[215] = Vector2i(11, 3);

	indexTilePosMap[119] = Vector2i(12, 0);
	indexTilePosMap[221] = Vector2i(12, 2);

	indexTilePosMap[127] = Vector2i(13, 0);
	indexTilePosMap[253] = Vector2i(13, 1);
	indexTilePosMap[247] = Vector2i(13, 2);
	indexTilePosMap[223] = Vector2i(13, 3);

	indexTilePosMap[255] = Vector2i(14, 0);

	indexTilePosMap[256] = Vector2i(0, 1);

}

int cShadowMap::getTileIndex(Vector2i inPos) {
	int x = inPos.x;
	int y = inPos.y;

	int tempX = inPos.x;
	int tempY = inPos.y;

	Rect2i mapRect= get_used_rect();

	int endX = mapRect.position.x + mapRect.size.x;
	int endY = mapRect.position.y + mapRect.size.y;

	if (tempX >= endX || tempX <= mapRect.position.x || tempY >= endY || tempY <= mapRect.position.y)
		return 0;

	tempX = x + 1;
	tempY = y - 1;
	int NE = allTileData[tempX * 40 + tempY] * 2;

	tempX = x + 1;
	tempY = y + 1;
	int SE = allTileData[tempX * 40 + tempY] * 8;

	tempX = x - 1;
	tempY = y + 1;
	int SW = allTileData[tempX * 40 + tempY] * 32;

	tempX = x - 1;
	tempY = y - 1;
	int NW = allTileData[tempX * 40 + tempY] * 128;

	tempX = x;
	tempY = y - 1;
	int N = allTileData[tempX * 40 + tempY];

	tempX = x - 1;
	tempY = y;
	int W = allTileData[tempX * 40 + tempY] * 64;

	tempX = x + 1;
	tempY = y;
	int E = allTileData[tempX * 40 + tempY] * 4;

	tempX = x;
	tempY = y + 1;
	int S = allTileData[tempX * 40 + tempY] * 16;

	if (N == 0) {
		NE = 0;
		NW = 0;
	}

	if (S == 0) {
		SE = 0;
		SW = 0;
	}

	if (W == 0) {
		SW = 0;
		NW = 0;
	}

	if (E == 0) {
		SE = 0;
		NE = 0;
	}

	return N + NE + E + SE + S + SW + W + NW;
}

void cShadowMap::_bind_methods() {
	ClassDB::bind_method(D_METHOD("update_noCol", "midPos"), &cShadowMap::update_noCol);
	ClassDB::bind_method(D_METHOD("init"),&cShadowMap::init);

	ClassDB::bind_method(D_METHOD("set_rayLength", "rayLength"), &cShadowMap::set_rayLength);
	ClassDB::bind_method(D_METHOD("get_rayLength"), &cShadowMap::get_rayLength);
	ClassDB::bind_method(D_METHOD("set_colMask", "colMask"), &cShadowMap::set_colMask);
	ClassDB::bind_method(D_METHOD("get_colMask"), &cShadowMap::get_colMask);
	ClassDB::bind_method(D_METHOD("set_blackTileAltasPos", "blackTileAltasPos"), &cShadowMap::set_blackTileAltasPos);
	ClassDB::bind_method(D_METHOD("get_blackTileAltasPos"), &cShadowMap::get_blackTileAltasPos);
	ClassDB::bind_method(D_METHOD("set_blackTileSourceId", "blackTileSourceId"), &cShadowMap::set_blackTileSourceId);
	ClassDB::bind_method(D_METHOD("get_blackTileSourceId"), &cShadowMap::get_blackTileSourceId);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "rayLength", PROPERTY_HINT_NONE ), "set_rayLength", "get_rayLength");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "colMask", PROPERTY_HINT_NONE ), "set_colMask", "get_colMask");
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2I, "blackTileAltasPos", PROPERTY_HINT_NONE ), "set_blackTileAltasPos", "get_blackTileAltasPos");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "blackTileSourceId", PROPERTY_HINT_NONE ), "set_blackTileSourceId", "get_blackTileSourceId");
}
