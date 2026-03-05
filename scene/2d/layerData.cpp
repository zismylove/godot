#include "layerData.h"

#include "core/io/resource_loader.h"
#include "core/math/random_number_generator.h"

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

void cTreeTileinfo::set_threshold(float inThreshold) {
	threshold = inThreshold;
}

float cTreeTileinfo::get_threshold() {
	return threshold;
}

void cTreeTileinfo::setTreeResArr(const TypedArray<String> &inTreeResArr) {
	treeResArr = inTreeResArr;
}

TypedArray<String> cTreeTileinfo::getTreeResArr() {
	return treeResArr;
}

void cTreeTileinfo::setProbabilityArr(const TypedArray<int> &inProbabilityArr) {
	probabilityArr = inProbabilityArr;
}

TypedArray<int> cTreeTileinfo::getProbabilityArr() {
	return probabilityArr;
}

void cTreeTileinfo::set_noise(const Ref<FastNoiseLite> inNoise) {
	noise = inNoise;
}

Ref<FastNoiseLite> cTreeTileinfo::get_noise() {
	return noise;
}

cTreeTileinfo::treeInfo cTreeTileinfo::getRandomTreePath() {
	int allPropertyCount = 0;
	Vector<Ref<Resource>> prabilityStrArr;

	int pathArrCount = treeResArr.size();

	Vector<Ref<Resource>> treeResLoadArr;
	for (auto &thePath : treeResArr) {
		Ref<Resource> tempRes = ResourceLoader::load(thePath);
		treeResLoadArr.append(tempRes);
	}

	int probalityArrCount = probabilityArr.size();
	if (pathArrCount > probalityArrCount) {
		int needAdd = pathArrCount - probalityArrCount;
		for (int i = 0; i < needAdd; i++) {
			probabilityArr.append(1);
		}
	} else {
		probalityArrCount = pathArrCount;
	}

	for (int i = 0; i < probalityArrCount; i++) {
		int tempCount = int(probabilityArr[i]);

		Ref<Resource> treeRes = treeResLoadArr[i];

		for (int j = 0; j < tempCount; j++) {
			prabilityStrArr.append(treeRes);
		}
		allPropertyCount += tempCount;
	}

	treeInfo info;
	info.count = allPropertyCount;
	info.treePathArr = prabilityStrArr;
	return info;
}

void cTreeTileinfo::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_treeResPath", "inTreeResPath"), &cTreeTileinfo::set_treeResPath);
	ClassDB::bind_method(D_METHOD("get_treeResPath"), &cTreeTileinfo::get_treeResPath);

	ClassDB::bind_method(D_METHOD("set_threshold", "inThreshold"), &cTreeTileinfo::set_threshold);
	ClassDB::bind_method(D_METHOD("get_threshold"), &cTreeTileinfo::get_threshold);

	ClassDB::bind_method(D_METHOD("setTreeResArr", "inTreeResArr"), &cTreeTileinfo::setTreeResArr);
	ClassDB::bind_method(D_METHOD("getTreeResArr"), &cTreeTileinfo::getTreeResArr);

	ClassDB::bind_method(D_METHOD("setProbabilityArr", "inProbabilityArr"), &cTreeTileinfo::setProbabilityArr);
	ClassDB::bind_method(D_METHOD("getProbabilityArr"), &cTreeTileinfo::getProbabilityArr);

	ClassDB::bind_method(D_METHOD("set_noise"), &cTreeTileinfo::set_noise);
	ClassDB::bind_method(D_METHOD("get_noise"), &cTreeTileinfo::get_noise);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "noise", PROPERTY_HINT_RESOURCE_TYPE, "FastNoiseLite"), "set_noise", "get_noise");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "threshold", PROPERTY_HINT_NONE), "set_threshold", "get_threshold");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "treeResPath", PROPERTY_HINT_NONE, ""), "set_treeResPath", "get_treeResPath");
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_FLOAT32_ARRAY, "probabilityArr"), "setProbabilityArr", "getProbabilityArr");
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_STRING_ARRAY, "treeResArr"), "setTreeResArr", "getTreeResArr");
}

void cLayerData::set_title(String inTitle) {
	title = inTitle;
	set_name(inTitle);
}

String cLayerData::get_title() {
	return title;
}

void cLayerData::set_threshold(float inThreshold) {
	threshold = inThreshold;
}

float cLayerData::get_threshold() {
	return threshold;
}

void cLayerData::set_noise(const Ref<FastNoiseLite> &inNoise) {
	if (noise == inNoise) {
		return;
	}
	noise = inNoise;
}

Ref<FastNoiseLite> cLayerData::get_noise() {
	return noise;
}

void cLayerData::set_bTerrain(bool inBterrain) {
	bTerrain = inBterrain;
}

bool cLayerData::get_bTerrain() {
	return bTerrain;
}

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
	terrainId = inTerrainID;
}

int cLayerData::get_terrainID() {
	return terrainId;
}

void cLayerData::set_weight(float inWeight) {
	weight = inWeight;
}

float cLayerData::get_weight() {
	return weight;
}

void cLayerData::set_addtive_tile_type(cLayerData::ADDTIVE_TILE_TYPE inAddTiveTileInfo) {
	addtive_tile_type = inAddTiveTileInfo;
}

cLayerData::ADDTIVE_TILE_TYPE cLayerData::get_addtive_tile_type() {
	return addtive_tile_type;
}

void cLayerData::setAddtiveTileinfo(const Ref<cTileInfo> inAddTileinfo) {
	if (inAddTileinfo == addTileInfo) {
		return;
	}
	addTileInfo = inAddTileinfo;
}

Ref<cTileInfo> cLayerData::getAddtiveTileinfo() {
	return addTileInfo;
}

void cLayerData::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_title", "title"), &cLayerData::set_title);
	ClassDB::bind_method(D_METHOD("get_title"), &cLayerData::get_title);

	ClassDB::bind_method(D_METHOD("set_noise", "noise"), &cLayerData::set_noise);
	ClassDB::bind_method(D_METHOD("get_noise"), &cLayerData::get_noise);

	ClassDB::bind_method(D_METHOD("set_bTerrain", "terrain"), &cLayerData::set_bTerrain);
	ClassDB::bind_method(D_METHOD("get_bTerrain"), &cLayerData::get_bTerrain);

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

	ClassDB::bind_method(D_METHOD("set_weight", "weight"), &cLayerData::set_weight);
	ClassDB::bind_method(D_METHOD("get_weight"), &cLayerData::get_weight);

	ClassDB::bind_method(D_METHOD("set_addtive_tile_type", "addtive_tile_type"), &cLayerData::set_addtive_tile_type);
	ClassDB::bind_method(D_METHOD("get_addtive_tile_type"), &cLayerData::get_addtive_tile_type);
	ClassDB::bind_method(D_METHOD("setAddtiveTileinfo", "addTileInfo"), &cLayerData::setAddtiveTileinfo);
	ClassDB::bind_method(D_METHOD("getAddtiveTileinfo"), &cLayerData::getAddtiveTileinfo);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "title", PROPERTY_HINT_NONE), "set_title", "get_title");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "noise", PROPERTY_HINT_RESOURCE_TYPE, "FastNoiseLite"), "set_noise", "get_noise");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "bTerrain", PROPERTY_HINT_NONE), "set_bTerrain", "get_bTerrain");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "threshold", PROPERTY_HINT_RANGE, "0,1,0.001"), "set_threshold", "get_threshold");

	ADD_PROPERTY(PropertyInfo(Variant::INT, "sourceID", PROPERTY_HINT_NONE, ""), "set_sourceID", "get_sourceID");
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2I, "atlasPos", PROPERTY_HINT_NONE, ""), "set_atlasPOS", "get_atlasPOS");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "terrainSet", PROPERTY_HINT_NONE, ""), "set_terrainSet", "get_terrainSet");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "terrainId", PROPERTY_HINT_NONE, ""), "set_terrainID", "get_terrainID");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "weight", PROPERTY_HINT_NONE, ""), "set_weight", "get_weight");

	ADD_PROPERTY(PropertyInfo(Variant::INT, "addtive_tile_type", PROPERTY_HINT_ENUM, "tree,crops"), "set_addtive_tile_type", "get_addtive_tile_type");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "addTileInfo", PROPERTY_HINT_RESOURCE_TYPE, "cTileInfo"), "setAddtiveTileinfo", "getAddtiveTileinfo");

	BIND_ENUM_CONSTANT(TREE);
	BIND_ENUM_CONSTANT(CROPS);
}
