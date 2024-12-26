#include "cShadowMap.h"

void cShadowMap::set_rayLength(float in_rayLength) {
	rayLength = in_rayLength;
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

int cShadowMap::get_blackTileSourceId(){
	return blackTileSourceId;
}

void cShadowMap::update_noCol(Vector2i midPos) {
	for(auto& tilePos: showTileArr) {
		set_cell(tilePos,blackTileSourceId,blackTileAltasPos);
	}

	for(int x=midPos.x - roundSzie;x<(midPos.x + roundSzie+1);x++) {
		for(int y=midPos.y - roundSzie;y<(midPos.y + roundSzie+1);y++) {
			float distance =Math::sqrt(Math::pow(2,(x + 0.5 - midPos.x)) + Math::pow(2,(y + 0.5 - midPos.y)));
			if(distance <= roundSzie) {
				// circle_blocks.append(Vector2i(x, y));
				// set_cell(Vector2i(x, y),blackTileSourceId,blackTileAltasPos);
				TypedArray<Vector2i> circle_blocks;
				circle_blocks.append(Vector2i(x,y));
				set_cells_terrain_connect(circle_blocks,0,0,true);
			}
		}
	}
	// set_cells_terrain_connect(circle_blocks,0,0,true);
}

void cShadowMap::_bind_methods() {
	ClassDB::bind_method(D_METHOD("update_noCol", "midPos"), &cShadowMap::update_noCol);

	ClassDB::bind_method(D_METHOD("set_rayLength", "rayLength"), &cShadowMap::set_rayLength);
	ClassDB::bind_method(D_METHOD("get_rayLength"), &cShadowMap::get_rayLength);
	ClassDB::bind_method(D_METHOD("set_colMask", "colMask"), &cShadowMap::set_colMask);
	ClassDB::bind_method(D_METHOD("get_colMask"), &cShadowMap::get_colMask);
	ClassDB::bind_method(D_METHOD("set_blackTileAltasPos", "blackTileAltasPos"), &cShadowMap::set_blackTileAltasPos);
	ClassDB::bind_method(D_METHOD("get_blackTileAltasPos"), &cShadowMap::get_blackTileAltasPos);
	ClassDB::bind_method(D_METHOD("set_blackTileSourceId", "blackTileSourceId"), &cShadowMap::set_blackTileSourceId);
	ClassDB::bind_method(D_METHOD("get_blackTileSourceId"), &cShadowMap::get_blackTileSourceId);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "rayLength", PROPERTY_HINT_NONE ),"set_rayLength","get_rayLength");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "colMask", PROPERTY_HINT_NONE ),"set_colMask","get_colMask");
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2I, "blackTileAltasPos", PROPERTY_HINT_NONE ),"set_blackTileAltasPos","get_blackTileAltasPos");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "blackTileSourceId", PROPERTY_HINT_NONE ),"set_blackTileSourceId","get_blackTileSourceId");

}
