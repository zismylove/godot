#pragma once

#include "layerData.h"
#include "node_2d.h"
#include "tile_map_layer.h"

class cSceneMake : public Node2D {
	GDCLASS(cSceneMake, Node2D);

public:
	struct spawnTileData {
		TypedArray<Vector2i> posArr;
		int terrainSet;
		int terrainId;
		int sourceId;
		bool bTerrain;
	};

	struct spawnTreeData {
		Vector2i pos;
		String treePath;
		cTreeTileinfo::treeInfo treeInfo; // 保存该树对应的完整树信息
	};

	enum TILEMAP_TYPE {
		FOREST,
		DESERT,
	};

	Vector2i mapSize = Vector2i(30, 30);

	TILEMAP_TYPE mapType = FOREST;

	// 基础层相关属性
	Ref<TileSet> baseLayerTileset;
	TypedArray<cLayerData> baseLayerDatas;
	NodePath baseTilemapLayerPath;
	TileMapLayer *baseTilemapLayer;

	// 第二层相关属性
	Ref<TileSet> secondLayerTileset;
	TypedArray<cLayerData> secondLayerDatas;
	NodePath secondTilemapLayerPath;
	TileMapLayer *secondTilemapLayer;

	// 第三层相关属性
	Ref<TileSet> thirdLayerTileset;
	TypedArray<cLayerData> thirdLayerDatas;
	NodePath thirdTilemapLayerPath;
	TileMapLayer *thirdTilemapLayer;

	// 层级控制参数
	float secondLayerThreshold = 0.3f; // 第二层生成阈值(0-1)
	float thirdLayerThreshold = 0.6f; // 第三层生成阈值(0-1)

	// 各层独立的形状控制参数
	float baseLayerNoiseFreq = 1.0f; // 基础层噪声频率（越小形状越大）
	float baseLayerContinuity = 0.3f; // 基础层连续性阈值

	float secondLayerNoiseFreq = 1.5f; // 第二层噪声频率
	float secondLayerContinuity = 0.4f; // 第二层连续性阈值

	float thirdLayerNoiseFreq = 2.0f; // 第三层噪声频率
	float thirdLayerContinuity = 0.5f; // 第三层连续性阈值

	// 随机种子
	int randomSeed = 12345; // 随机种子，影响所有随机生成

	// 树木生成参数
	int treeMinDistance = 4; // 树木最小间距（tile单位），控制树木之间的最小距离

	// 保存生成的树木信息供编辑器查看
	TypedArray<Dictionary> generatedTreesInfo;

	// 基础层方法
	void set_mapsize(Vector2i inMapsize);
	Vector2i get_mapsize();

	void set_mapType(cSceneMake::TILEMAP_TYPE inMaptype);
	cSceneMake::TILEMAP_TYPE get_maptype();

	void set_baseLayerDatas(const TypedArray<cLayerData> &inLayerDatas);
	TypedArray<cLayerData> get_layerDatas();

	void set_BaseLayerTileset(Ref<TileSet> inBaseLayerTileset);
	Ref<TileSet> get_baseLayerTileset();

	void set_baseTilemapLayer(const NodePath &inBaseTilemapLayer);
	NodePath get_baseTilemapLayer() const;

	// 第二层方法
	void set_secondLayerDatas(const TypedArray<cLayerData> &inLayerDatas);
	TypedArray<cLayerData> get_secondLayerDatas();

	void set_SecondLayerTileset(Ref<TileSet> inSecondLayerTileset);
	Ref<TileSet> get_secondLayerTileset();

	void set_secondTilemapLayer(const NodePath &inSecondTilemapLayer);
	NodePath get_secondTilemapLayer() const;

	// 第三层方法
	void set_thirdLayerDatas(const TypedArray<cLayerData> &inLayerDatas);
	TypedArray<cLayerData> get_thirdLayerDatas();

	void set_ThirdLayerTileset(Ref<TileSet> inThirdLayerTileset);
	Ref<TileSet> get_thirdLayerTileset();

	void set_thirdTilemapLayer(const NodePath &inThirdTilemapLayer);
	NodePath get_thirdTilemapLayer() const;

	// 层级控制参数方法
	void set_secondLayerThreshold(float threshold);
	float get_secondLayerThreshold() const;

	void set_thirdLayerThreshold(float threshold);
	float get_thirdLayerThreshold() const;

	// 各层形状控制参数方法
	void set_baseLayerNoiseFreq(float freq);
	float get_baseLayerNoiseFreq() const;
	void set_baseLayerContinuity(float continuity);
	float get_baseLayerContinuity() const;

	void set_secondLayerNoiseFreq(float freq);
	float get_secondLayerNoiseFreq() const;
	void set_secondLayerContinuity(float continuity);
	float get_secondLayerContinuity() const;

	void set_thirdLayerNoiseFreq(float freq);
	float get_thirdLayerNoiseFreq() const;
	void set_thirdLayerContinuity(float continuity);
	float get_thirdLayerContinuity() const;

	// 随机种子方法
	void set_randomSeed(int seed);
	int get_randomSeed() const;

	// 树木生成参数方法
	void set_treeMinDistance(int distance);
	int get_treeMinDistance() const;

	// 生成的树木信息方法
	void set_generatedTreesInfo(const TypedArray<Dictionary> &treesInfo);
	TypedArray<Dictionary> get_generatedTreesInfo() const;

public:
	void makeBaseTile(bool bClearTree = false);

protected:
	static void _bind_methods();

private:
	// 私有辅助方法：检查指定位置周围指定距离内是否已经有树木
	bool hasTreeWithinDistance(const Vector<spawnTreeData> &existingTrees, Vector2i pos, int distance);

	// 私有辅助方法：处理单个层的生成
	void processLayer(TileMapLayer *layer, const TypedArray<cLayerData> &layerDatas,
			const Ref<TileSet> &tileset, Vector<spawnTreeData> &treeDataArr,
			int layerIndex, float noiseFreq, float continuityThreshold);
};

VARIANT_ENUM_CAST(cSceneMake::TILEMAP_TYPE);
