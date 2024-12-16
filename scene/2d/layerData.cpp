#include "layerData.h"

void cTileInfo::set_theID(String inID) {
	theID = inID;
}

String cTileInfo::get_theID() {
	return theID;
}

void cTileInfo::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_theID", "theID"), &cTileInfo::set_theID);
	ClassDB::bind_method(D_METHOD("get_theID"), &cTileInfo::get_theID);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "theID", PROPERTY_HINT_NONE, ""), "set_theID", "get_theID");
}



void cTreeTileinfo::set_treeResPath(String inTreeResPath) {
	treeResPath = inTreeResPath;
}

String cTreeTileinfo::get_treeResPath() {
	return treeResPath;
}

void cTreeTileinfo::setTreeDirPath(String inTreeDirPath) {
	treeDirPath = inTreeDirPath;
}

String cTreeTileinfo::getTreeDirPath() {
	return treeDirPath;
}

void cTreeTileinfo::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_treeResPath", "cTreeTileinfo"), &cTreeTileinfo::set_treeResPath);
	ClassDB::bind_method(D_METHOD("get_treeResPath"), &cTreeTileinfo::get_treeResPath);
	ClassDB::bind_method(D_METHOD("setTreeDirPath", "treeResPath"), &cTreeTileinfo::setTreeDirPath);
	ClassDB::bind_method(D_METHOD("getTreeDirPath"), &cTreeTileinfo::getTreeDirPath);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "treeResPath", PROPERTY_HINT_NONE, ""), "set_treeResPath", "get_treeResPath");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "treeDirPath", PROPERTY_HINT_NONE, ""), "setTreeDirPath", "getTreeDirPath");

}

void cLayerData::set_threshold(float inThreshold) {
	threshold = inThreshold;
}

float cLayerData::get_threshold() {
	return threshold;
}

// void cLayerData::set_noise(const Ref<FastNoiseLite> &inNoise) {
// 	if(noise==inNoise)
// 		return;
// 	noise = inNoise;
// }
//
// Ref<FastNoiseLite> cLayerData::get_noise() {
// 	return noise;
// }

void cLayerData::set_sourceID(int inSourceID) {
	sourceID = inSourceID;
}

int cLayerData::get_sourceID() {
	return sourceID;
}

void cLayerData::set_atlasPOS(Vector2i inAtlasPOS) {
	atlasPos = inAtlasPOS;
}

Vector2i cLayerData::get_atlasPOS() {
	return atlasPos;
}

void cLayerData::set_terrainSet(int inTerrainSet) {
	terrainSet = inTerrainSet;
}

int cLayerData::get_terrainSet() {
	return terrainSet;
}

void cLayerData::set_terrainID(int inTerrainID) {
	terrainId = inTerrainID ;
}

int cLayerData::get_terrainID() {
	return terrainId;
}

void cLayerData::set_addtive_tile_type(cLayerData::ADDTIVE_TILE_TYPE inAddTiveTileInfo) {
	addtive_tile_type= inAddTiveTileInfo;
}

cLayerData::ADDTIVE_TILE_TYPE cLayerData::get_addtive_tile_type() {
	return addtive_tile_type;
}

void cLayerData::setAddtiveTileinfo(const Ref<cTileInfo> inAddTileinfo) {
	if(inAddTileinfo == addTileInfo)
		return;
	addTileInfo = inAddTileinfo;
}

Ref<cTileInfo> cLayerData::getAddtiveTileinfo() {
	return addTileInfo;
}

void cLayerData::_bind_methods() {
	// ClassDB::bind_method(D_METHOD("set_noise", "noise"), &cLayerData::set_noise);
	// ClassDB::bind_method(D_METHOD("get_noise"), &cLayerData::get_noise);
	ClassDB::bind_method(D_METHOD("set_threshold", "threshold"), &cLayerData::set_threshold);
	ClassDB::bind_method(D_METHOD("get_threshold"), &cLayerData::get_threshold);
	ClassDB::bind_method(D_METHOD("set_sourceID", "sourceID"), &cLayerData::set_sourceID);
	ClassDB::bind_method(D_METHOD("get_sourceID"), &cLayerData::get_sourceID);
	ClassDB::bind_method(D_METHOD("set_atlasPOS", "atlasPos"), &cLayerData::set_atlasPOS);
	ClassDB::bind_method(D_METHOD("get_atlasPOS"), &cLayerData::get_atlasPOS);
	ClassDB::bind_method(D_METHOD("set_terrainSet", "terrainSet"), &cLayerData::set_terrainSet);
	ClassDB::bind_method(D_METHOD("get_terrainSet"), &cLayerData::get_terrainSet);
	ClassDB::bind_method(D_METHOD("set_terrainID", "terrainId"), &cLayerData::set_terrainID);
	ClassDB::bind_method(D_METHOD("get_terrainID"), &cLayerData::get_terrainID);
	ClassDB::bind_method(D_METHOD("set_addtive_tile_type", "addtive_tile_type"), &cLayerData::set_addtive_tile_type);
	ClassDB::bind_method(D_METHOD("get_addtive_tile_type"), &cLayerData::get_addtive_tile_type);
	ClassDB::bind_method(D_METHOD("setAddtiveTileinfo", "addTileInfo"), &cLayerData::setAddtiveTileinfo);
	ClassDB::bind_method(D_METHOD("getAddtiveTileinfo"), &cLayerData::getAddtiveTileinfo);



	// ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "noise", PROPERTY_HINT_RESOURCE_TYPE, "FastNoiseLite"), "set_noise", "get_noise");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "threshold", PROPERTY_HINT_RANGE, "0,1,0.01"), "set_threshold", "get_threshold");

	ADD_PROPERTY(PropertyInfo(Variant::INT, "sourceID", PROPERTY_HINT_NONE, ""), "set_sourceID", "get_sourceID");
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2I, "atlasPos", PROPERTY_HINT_NONE, ""), "set_atlasPOS", "get_atlasPOS");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "terrainSet", PROPERTY_HINT_NONE, ""), "set_terrainSet", "get_terrainSet");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "terrainId", PROPERTY_HINT_NONE, ""), "set_terrainID", "get_terrainID");

	ADD_PROPERTY(PropertyInfo(Variant::INT, "addtive_tile_type", PROPERTY_HINT_ENUM, "tree,crops"), "set_addtive_tile_type", "get_addtive_tile_type");

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "addTileInfo", PROPERTY_HINT_RESOURCE_TYPE, "cTileInfo"), "setAddtiveTileinfo", "getAddtiveTileinfo");

	BIND_ENUM_CONSTANT(TREE)
	BIND_ENUM_CONSTANT(CROPS)

}
