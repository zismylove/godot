#pragma once
#include "layerData.h"
#include "node_2d.h"
#include "tile_map_layer.h"
#include "scene/resources/2d/tile_set.h"


class cSceneMake:public Node2D {
	GDCLASS(cSceneMake, Node2D);
public:
	struct spawnTileData {
		TypedArray<Vector2i>posArr;
		int terrainSet;
		int terrainId;
		int sourceId;
		bool bTerrain;
	};

	struct spawnTreeData {
		Vector2i pos;
		String treePath;
	};

	enum TILEMAP_TYPE{
		FOREST,
		DESERT,
	};

	Vector2i mapSize=Vector2i(30,30);

	TILEMAP_TYPE mapType=FOREST;

	Ref<TileSet>baseLayerTileset;

	TypedArray<cLayerData>baseLayerDatas;

	NodePath baseTilemapLayerPath;

	TileMapLayer* baseTilemapLayer;

	void set_mapsize(Vector2i inMapsize);
	Vector2i get_mapsize();

	void set_mapType(cSceneMake::TILEMAP_TYPE inMaptype);
	cSceneMake::TILEMAP_TYPE get_maptype();

	void set_baseLayerDatas(const TypedArray<cLayerData> &inLayerDatas);
	TypedArray<cLayerData>get_layerDatas();

	void set_BaseLayerTileset(Ref<TileSet>inBaseLayerTileset);
	Ref<TileSet> get_baseLayerTileset();

	void set_baseTilemapLayer(const NodePath& inBaseTilemapLayer);
	NodePath get_baseTilemapLayer() const;

public:

	void makeBaseTile(bool bClearTree=false);

protected:
	static void _bind_methods();
};

VARIANT_ENUM_CAST(cSceneMake::TILEMAP_TYPE);
