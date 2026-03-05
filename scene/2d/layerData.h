#pragma once

#include "core/io/resource.h"
#include "modules/noise/fastnoise_lite.h"

class cTileInfo : public Resource {
	GDCLASS(cTileInfo, Resource)

public:
	String theID;

	void set_theID(String inID);
	String get_theID();

protected:
	static void _bind_methods();
};

class cTreeTileinfo : public cTileInfo {
	GDCLASS(cTreeTileinfo, cTileInfo)

public:
	struct treeInfo {
		Vector<Ref<Resource>> treePathArr;
		int count;
	};

	Ref<FastNoiseLite> noise;

	String treeResPath;
	float threshold;
	TypedArray<String> treeResArr;
	TypedArray<int> probabilityArr;

	void set_noise(const Ref<FastNoiseLite> inNoise);
	Ref<FastNoiseLite> get_noise();

	void set_treeResPath(String inTreeResPath);
	String get_treeResPath();

	void set_threshold(float inThreshold);
	float get_threshold();

	void setTreeResArr(const TypedArray<String> &inTreeResArr);
	TypedArray<String> getTreeResArr();

	void setProbabilityArr(const TypedArray<int> &inProbabilityArr);
	TypedArray<int> getProbabilityArr();

	treeInfo getRandomTreePath();

protected:
	static void _bind_methods();
};

class cLayerData : public Resource {
	GDCLASS(cLayerData, Resource);

public:
	enum ADDTIVE_TILE_TYPE {
		TREE,
		CROPS,
	};

	Ref<FastNoiseLite> noise;

	String title;

	bool bTerrain = true;

	float threshold;

	int sourceID = -1;

	Vector2i atlasPos = Vector2i(0, 0);

	int terrainSet = 0;

	int terrainId = 0;

	float weight = 1.0;

	ADDTIVE_TILE_TYPE addtive_tile_type;

	Ref<cTileInfo> addTileInfo;

	void set_title(String inTitle);
	String get_title();

	void set_threshold(float inThreshold);
	float get_threshold();

	void set_noise(const Ref<FastNoiseLite> &inNoise);
	Ref<FastNoiseLite> get_noise();

	void set_bTerrain(bool inBterrain);
	bool get_bTerrain();

	void set_sourceID(int inSourceID);
	int get_sourceID();

	void set_atlasPOS(Vector2i inAtlasPOS);
	Vector2i get_atlasPOS();

	void set_terrainSet(int inTerrainSet);
	int get_terrainSet();

	void set_terrainID(int inTerrainID);
	int get_terrainID();

	void set_weight(float inWeight);
	float get_weight();

	void set_addtive_tile_type(cLayerData::ADDTIVE_TILE_TYPE inAddTiveTileInfo);
	ADDTIVE_TILE_TYPE get_addtive_tile_type();

	void setAddtiveTileinfo(const Ref<cTileInfo> inAddTileinfo);
	Ref<cTileInfo> getAddtiveTileinfo();

protected:
	static void _bind_methods();
};

VARIANT_ENUM_CAST(cLayerData::ADDTIVE_TILE_TYPE);
