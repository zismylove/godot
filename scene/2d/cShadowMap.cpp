#include "cShadowMap.h"

#include "scene/resources/world_2d.h"
#include "servers/physics_server_2d.h"

#include <string>

void cShadowMap::setShadowMapType(EShadowMapType type) {
	shadowMapType = type;
}

EShadowMapType cShadowMap::getShadowMapType() {
	return shadowMapType;
}

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

void cShadowMap::update_noCol(Vector2i inMidPos, int newRange) {
	midPos = inMidPos;
	roundSzie = newRange;

}

void cShadowMap::update_noColCircle(Vector2i inMidPos, int newRange) {
	midPos = inMidPos;
	roundSzie = newRange;
	print_line(("the 0 size is"+std::string(std::to_string(showTileArr.size()))).c_str());

	for (int i = 0; i < showTileArr.size(); i++) {
		Vector2i tilePos = showTileArr[i];
		set_cell(tilePos, blackTileSourceId, halfBlackTileAltasPos);
		int theArrIndex = tilePos.x * mapRect.size.y + tilePos.y;
		allTileData[theArrIndex] = 0;
	}

	int centerX = midPos.x;
	int centerY = midPos.y;

	int startX = centerX - roundSzie;
	int startY = centerY - roundSzie;

	int endX = centerX + roundSzie;
	int endY = centerY + roundSzie;

	if (startX < 0)
		startX = 0;

	if (startY < 0)
		startY = 0;

	if (endX >= mapRect.size.x)
		endX = mapRect.size.x - 1;
	if (endY >= mapRect.size.y)
		endY = mapRect.size.y - 1;

	showTileArr.clear();
	for (int x = startX; x <= endX; ++x) {
		for (int y = startY; y <= endY; ++y) {
			// 检查点 (i, j) 是否在圆内
			float dx = (float)x - (float)centerX;
			float dy = (float)y - (float)centerY;
			if (dx * dx + dy * dy <= (roundSzie * roundSzie) - 0.5) {
				int theArrIndex = x * mapRect.size.y + y;
				allTileData[theArrIndex] = 1;
				showTileArr.push_back(Vector2i(x, y));
			}
		}
	}

	for (auto &tilePos : showTileArr) {
		int tileMapIndex = getTileIndex(tilePos);
		Vector2i tileAltasPos = indexTilePosMap[tileMapIndex];
		set_cell(tilePos, blackTileSourceId, tileAltasPos);
	}
}

void cShadowMap::update_noColSquare(Vector2i inMidPos, int newRange) {

}

void cShadowMap::update_specialBuff(TypedArray<Vector2i> inRange) {
	hideShow();
	showTileArr = inRange;
	for (auto &tilePos : showTileArr) {

		Vector2i tempPos = tilePos;
		int x =tempPos.x;
		int y =tempPos.y;
		int theArrIndex = x * mapRect.size.y + y;
		allTileData[theArrIndex] = 1;
	}
	for (auto &tilePos : showTileArr) {
		int tileMapIndex = getTileIndex(tilePos);
		Vector2i tileAltasPos = indexTilePosMap[tileMapIndex];
		set_cell(tilePos, blackTileSourceId, tileAltasPos);
	}
}

void cShadowMap::init() {
	showTileArr.clear();

	allTileData.resize(mapRect.size.x * mapRect.size.y);
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

void cShadowMap::resize(Vector2i newSize) {
	mapRect.size = newSize;
	for (int x = 0; x < newSize.x; x++) {
		for (int y = 0; y < newSize.y; y++) {
			set_cell(Vector2i(x, y), blackTileSourceId, blackTileAltasPos);
		}
	}
	init();
}

int cShadowMap::getTileIndex(Vector2i inPos) {
	int x = inPos.x;
	int y = inPos.y;

	int tempX = inPos.x;
	int tempY = inPos.y;

	int endX = mapRect.position.x + mapRect.size.x;
	int endY = mapRect.position.y + mapRect.size.y;

	int xSize = mapRect.size.y;

	if (tempX >= endX || tempX <= mapRect.position.x || tempY >= endY || tempY <= mapRect.position.y)
		return 0;

	tempX = x + 1;
	tempY = y - 1;
	int NE = allTileData[tempX * xSize + tempY] * 2;

	tempX = x + 1;
	tempY = y + 1;
	int SE = allTileData[tempX * xSize + tempY] * 8;

	tempX = x - 1;
	tempY = y + 1;
	int SW = allTileData[tempX * xSize + tempY] * 32;

	tempX = x - 1;
	tempY = y - 1;
	int NW = allTileData[tempX * xSize + tempY] * 128;

	tempX = x;
	tempY = y - 1;
	int N = allTileData[tempX * xSize + tempY];

	tempX = x - 1;
	tempY = y;
	int W = allTileData[tempX * xSize + tempY] * 64;

	tempX = x + 1;
	tempY = y;
	int E = allTileData[tempX * xSize + tempY] * 4;

	tempX = x;
	tempY = y + 1;
	int S = allTileData[tempX * xSize + tempY] * 16;

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

void cShadowMap::fill() {
	int endX = mapRect.size.x;
	int endY = mapRect.size.y;

	for (int x = 0; x < endX; x++) {
		for (int y = 0; y < endY; y++) {
			set_cell(Vector2i(x, y), blackTileSourceId, blackTileAltasPos);
		}
	}
}

void cShadowMap::hideShow() {
	for (auto &tilePos : showTileArr) {
		erase_cell(tilePos);
		Vector2i tempPos = tilePos;
		int x =tempPos.x;
		int y =tempPos.y;
		int theArrIndex = x * mapRect.size.y + y;
		allTileData[theArrIndex] = 0;
	}
	showTileArr.clear();
}

void cShadowMap::collisionDispose() {
	uint32_t colMask;
	TypedArray<RID>excludeRID;
	Vector2 startPos;
	Vector2 endPos;

	PhysicsDirectSpaceState2D* state2d = get_world_2d()->get_direct_space_state();

	Ref<PhysicsRayQueryParameters2D>query = PhysicsRayQueryParameters2D::create(startPos,endPos,colMask,excludeRID);

	PhysicsDirectSpaceState2D::RayResult theRes;
	state2d->intersect_ray(query->get_parameters(),theRes);

}


void cShadowMap::_bind_methods() {
	ClassDB::bind_method(D_METHOD("fill"), &cShadowMap::fill);
	ClassDB::bind_method(D_METHOD("hideShow"), &cShadowMap::hideShow);

	ClassDB::bind_method(D_METHOD("update_noCol", "midPos"), &cShadowMap::update_noCol);
	ClassDB::bind_method(D_METHOD("init"), &cShadowMap::init);
	ClassDB::bind_method(D_METHOD("resize", "newsize"), &cShadowMap::resize);

	ClassDB::bind_method(D_METHOD("update_noColCircle", "inMidPos,newRange"), &cShadowMap::update_noColCircle);
	ClassDB::bind_method(D_METHOD("update_noColSquare", "inMidPos,newRange"), &cShadowMap::update_noColCircle);
	ClassDB::bind_method(D_METHOD("update_specialBuff", "inRange"), &cShadowMap::update_specialBuff);

	ClassDB::bind_method(D_METHOD("setShadowMapType", "shadowMapType"), &cShadowMap::setShadowMapType);
	ClassDB::bind_method(D_METHOD("getShadowMapType"), &cShadowMap::getShadowMapType);

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

	ADD_PROPERTY(PropertyInfo(Variant::INT, "shadowMapType", PROPERTY_HINT_ENUM,"shadowMap,buff,itemRange" ), "setShadowMapType", "getShadowMapType");
}
