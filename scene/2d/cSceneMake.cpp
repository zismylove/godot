#include "cSceneMake.h"

#include "cPlaceItemNode.h"
#include "core/math/random_number_generator.h"
#include "scene/resources/packed_scene.h"

void cSceneMake::set_mapsize(Vector2i inMapsize) {
	mapSize = inMapsize;
}

Vector2i cSceneMake::get_mapsize() {
	return mapSize;
}

void cSceneMake::set_mapType(cSceneMake::TILEMAP_TYPE inMaptype) {
	mapType = inMaptype;
}

cSceneMake::TILEMAP_TYPE cSceneMake::get_maptype() {
	return mapType;
}

void cSceneMake::set_baseLayerDatas(const TypedArray<cLayerData> &inLayerDatas) {
	baseLayerDatas = inLayerDatas;
}

TypedArray<cLayerData> cSceneMake::get_layerDatas() {
	return baseLayerDatas;
}

void cSceneMake::set_BaseLayerTileset(Ref<TileSet> inBaseLayerTileset) {
	baseLayerTileset = inBaseLayerTileset;
}

Ref<TileSet> cSceneMake::get_baseLayerTileset() {
	return baseLayerTileset;
}

void cSceneMake::set_baseTilemapLayer(const NodePath &inBaseTilemapLayer) {
	baseTilemapLayerPath = inBaseTilemapLayer;
}

NodePath cSceneMake::get_baseTilemapLayer() const {
	return baseTilemapLayerPath;
}

// 第二层方法实现
void cSceneMake::set_secondLayerDatas(const TypedArray<cLayerData> &inLayerDatas) {
	secondLayerDatas = inLayerDatas;
}

TypedArray<cLayerData> cSceneMake::get_secondLayerDatas() {
	return secondLayerDatas;
}

void cSceneMake::set_SecondLayerTileset(Ref<TileSet> inSecondLayerTileset) {
	secondLayerTileset = inSecondLayerTileset;
}

Ref<TileSet> cSceneMake::get_secondLayerTileset() {
	return secondLayerTileset;
}

void cSceneMake::set_secondTilemapLayer(const NodePath &inSecondTilemapLayer) {
	secondTilemapLayerPath = inSecondTilemapLayer;
}

NodePath cSceneMake::get_secondTilemapLayer() const {
	return secondTilemapLayerPath;
}

// 第三层方法实现
void cSceneMake::set_thirdLayerDatas(const TypedArray<cLayerData> &inLayerDatas) {
	thirdLayerDatas = inLayerDatas;
}

TypedArray<cLayerData> cSceneMake::get_thirdLayerDatas() {
	return thirdLayerDatas;
}

void cSceneMake::set_ThirdLayerTileset(Ref<TileSet> inThirdLayerTileset) {
	thirdLayerTileset = inThirdLayerTileset;
}

Ref<TileSet> cSceneMake::get_thirdLayerTileset() {
	return thirdLayerTileset;
}

void cSceneMake::set_thirdTilemapLayer(const NodePath &inThirdTilemapLayer) {
	thirdTilemapLayerPath = inThirdTilemapLayer;
}

NodePath cSceneMake::get_thirdTilemapLayer() const {
	return thirdTilemapLayerPath;
}

// 层级控制参数方法实现
void cSceneMake::set_secondLayerThreshold(float threshold) {
	secondLayerThreshold = CLAMP(threshold, 0.0f, 1.0f);
}

float cSceneMake::get_secondLayerThreshold() const {
	return secondLayerThreshold;
}

void cSceneMake::set_thirdLayerThreshold(float threshold) {
	thirdLayerThreshold = CLAMP(threshold, 0.0f, 1.0f);
}

float cSceneMake::get_thirdLayerThreshold() const {
	return thirdLayerThreshold;
}

// 各层形状控制参数方法实现
void cSceneMake::set_baseLayerNoiseFreq(float freq) {
	baseLayerNoiseFreq = MAX(freq, 0.1f);
}

float cSceneMake::get_baseLayerNoiseFreq() const {
	return baseLayerNoiseFreq;
}

void cSceneMake::set_baseLayerContinuity(float continuity) {
	baseLayerContinuity = CLAMP(continuity, 0.0f, 1.0f);
}

float cSceneMake::get_baseLayerContinuity() const {
	return baseLayerContinuity;
}

void cSceneMake::set_secondLayerNoiseFreq(float freq) {
	secondLayerNoiseFreq = MAX(freq, 0.1f);
}

float cSceneMake::get_secondLayerNoiseFreq() const {
	return secondLayerNoiseFreq;
}

void cSceneMake::set_secondLayerContinuity(float continuity) {
	secondLayerContinuity = CLAMP(continuity, 0.0f, 1.0f);
}

float cSceneMake::get_secondLayerContinuity() const {
	return secondLayerContinuity;
}

void cSceneMake::set_thirdLayerNoiseFreq(float freq) {
	thirdLayerNoiseFreq = MAX(freq, 0.1f);
}

float cSceneMake::get_thirdLayerNoiseFreq() const {
	return thirdLayerNoiseFreq;
}

void cSceneMake::set_thirdLayerContinuity(float continuity) {
	thirdLayerContinuity = CLAMP(continuity, 0.0f, 1.0f);
}

float cSceneMake::get_thirdLayerContinuity() const {
	return thirdLayerContinuity;
}

// 随机种子方法实现
void cSceneMake::set_randomSeed(int seed) {
	randomSeed = seed;
}

int cSceneMake::get_randomSeed() const {
	return randomSeed;
}

// 树木生成参数方法实现
void cSceneMake::set_treeMinDistance(int distance) {
	treeMinDistance = MAX(distance, 1); // 最小值为1，确保有效距离
}

int cSceneMake::get_treeMinDistance() const {
	return treeMinDistance;
}

// 生成的树木信息方法实现
void cSceneMake::set_generatedTreesInfo(const TypedArray<Dictionary> &treesInfo) {
	generatedTreesInfo = treesInfo;
}

TypedArray<Dictionary> cSceneMake::get_generatedTreesInfo() const {
	return generatedTreesInfo;
}

// 检查指定位置周围指定距离内是否已经有树木
bool cSceneMake::hasTreeWithinDistance(const Vector<spawnTreeData> &existingTrees, Vector2i pos, int distance) {
	for (const auto &tree : existingTrees) {
		int dx = abs(tree.pos.x - pos.x);
		int dy = abs(tree.pos.y - pos.y);
		// 使用切比雪夫距离（棋盘距离），确保周围distance个tile范围内没有其他树
		if (dx <= distance && dy <= distance) {
			return true;
		}
	}
	return false;
}

// 私有辅助方法：处理单个层的生成
void cSceneMake::processLayer(TileMapLayer *layer, const TypedArray<cLayerData> &layerDatas,
		const Ref<TileSet> &tileset, Vector<spawnTreeData> &treeDataArr,
		int layerIndex, float noiseFreq, float continuityThreshold) {
	if (!layer || !tileset.is_valid() || layerDatas.size() == 0) {
		return;
	}

	layer->set_tile_set(tileset);
	layer->clear();

	// 生成该层的形状控制噪声（用于产生大块连续区域）
	Vector<Vector<float>> shapeNoiseMap;
	shapeNoiseMap.resize(mapSize.x);
	for (int x = 0; x < mapSize.x; x++) {
		shapeNoiseMap.write[x].resize(mapSize.y);
	}

	// 创建一个简单的噪声生成器用于形状控制
	Ref<FastNoiseLite> shapeNoise = memnew(FastNoiseLite);
	shapeNoise->set_seed(randomSeed + layerIndex * 1000);

	for (int x = 0; x < mapSize.x; x++) {
		for (int y = 0; y < mapSize.y; y++) {
			// 缩放坐标来控制块大小，noiseFreq越小块越大
			float scaledX = float(x) / noiseFreq;
			float scaledY = float(y) / noiseFreq;

			// 用缩放后的坐标生成噪声
			float noiseValue = (shapeNoise->get_noise_2d(scaledX, scaledY) + 1.0f) / 2.0f; // 转换到0-1范围
			shapeNoiseMap.write[x].write[y] = noiseValue;
		}
	}

	RandomNumberGenerator rng;

	// 处理每个图层数据
	for (auto &itLayerData : layerDatas) {
		cLayerData *tempLayerData = Object::cast_to<cLayerData>(itLayerData);
		if (!tempLayerData) {
			continue;
		}

		bool bHasTree = tempLayerData->addTileInfo.is_valid();
		cTreeTileinfo *treeTileInfo = nullptr;
		cTreeTileinfo::treeInfo currentTreeInfo;
		if (bHasTree) {
			treeTileInfo = Object::cast_to<cTreeTileinfo>(*tempLayerData->addTileInfo);
			if (treeTileInfo) {
				currentTreeInfo = treeTileInfo->getRandomTreePath();
			} else {
				bHasTree = false;
			}
		}

		float threshold = tempLayerData->threshold;
		spawnTileData tempSpawnData;
		tempSpawnData.bTerrain = tempLayerData->bTerrain;
		tempSpawnData.terrainId = tempLayerData->terrainId;
		tempSpawnData.terrainSet = tempLayerData->terrainSet;
		tempSpawnData.sourceId = tempLayerData->sourceID;

		for (int x = 0; x < mapSize.x; x++) {
			for (int y = 0; y < mapSize.y; y++) {
				// 首先检查形状噪声是否超过连续性阈值（控制大块形状）
				if (shapeNoiseMap[x][y] < continuityThreshold) {
					continue;
				}

				// 在大块区域内，应用图层数据的噪声和阈值进行细节控制
				float noiseValue = float(tempLayerData->noise->get_noise_2d(x, y) + 1) / 2;

				if (noiseValue < threshold) {
					continue;
				}

				// 处理树木生成
				if (bHasTree && treeTileInfo) {
					rng.set_seed(randomSeed + (x + 1) * (y + 1) + layerIndex * 10000);
					float treeValue = rng.randf();
					if (treeValue < treeTileInfo->threshold) {
						// 检查周围指定距离内是否已经有其他树木
						Vector2i currentPos = Vector2i(x, y);
						if (!hasTreeWithinDistance(treeDataArr, currentPos, treeMinDistance)) {
							spawnTreeData tempTreeData;
							tempTreeData.pos = currentPos;
							tempTreeData.treePath = "";
							tempTreeData.treeInfo = currentTreeInfo; // 保存该树对应的完整树信息
							treeDataArr.append(tempTreeData);
						}
						// 如果周围指定距离内有树木就跳过，不添加新树
					}
				}

				tempSpawnData.posArr.append(Vector2i(x, y));
			}
		}

		// 生成瓦片
		if (tempLayerData->bTerrain) {
			layer->set_cells_terrain_connect(tempSpawnData.posArr, tempSpawnData.terrainSet, tempSpawnData.terrainId);
		} else {
			for (auto &tempPos : tempSpawnData.posArr) {
				layer->set_cell(tempPos, tempLayerData->sourceID, tempLayerData->atlasPos);
			}
		}
	}
}

void cSceneMake::makeBaseTile(bool bClearTree) {
	// 验证并初始化基础层
	if (baseTilemapLayerPath.is_empty()) {
		ERR_PRINT("the baselayer is null");
		return;
	}
	baseTilemapLayer = Object::cast_to<TileMapLayer>(get_node(baseTilemapLayerPath));
	if (!baseTilemapLayer) {
		ERR_PRINT("the baselayer is null");
		return;
	}

	// 初始化第二层和第三层
	if (!secondTilemapLayerPath.is_empty()) {
		secondTilemapLayer = Object::cast_to<TileMapLayer>(get_node(secondTilemapLayerPath));
	}
	if (!thirdTilemapLayerPath.is_empty()) {
		thirdTilemapLayer = Object::cast_to<TileMapLayer>(get_node(thirdTilemapLayerPath));
	}

	Vector<spawnTreeData> treeDataArr;

	// 清空之前的树木信息
	generatedTreesInfo.clear();

	// 生成基础层（使用独立的形状控制）
	print_line("Generating base layer...");
	processLayer(baseTilemapLayer, baseLayerDatas, baseLayerTileset, treeDataArr, 0,
			baseLayerNoiseFreq, baseLayerContinuity);

	// 生成第二层（如果配置了）
	if (secondTilemapLayer && secondLayerTileset.is_valid() && secondLayerDatas.size() > 0) {
		print_line("Generating second layer...");
		processLayer(secondTilemapLayer, secondLayerDatas, secondLayerTileset, treeDataArr, 1,
				secondLayerNoiseFreq, secondLayerContinuity);
	}

	// 生成第三层（如果配置了）
	if (thirdTilemapLayer && thirdLayerTileset.is_valid() && thirdLayerDatas.size() > 0) {
		print_line("Generating third layer...");
		processLayer(thirdTilemapLayer, thirdLayerDatas, thirdLayerTileset, treeDataArr, 2,
				thirdLayerNoiseFreq, thirdLayerContinuity);
	}

	// 处理植物生成（原有逻辑保持不变）
	Node *root = baseTilemapLayer->get_parent()->get_parent();
	Node2D *plantRoot = Object::cast_to<Node2D>(root->get_node(NodePath("plantRoot")));
	if (!plantRoot) {
		plantRoot = Object::cast_to<Node2D>(ClassDB::instantiate("Node2D"));
		root->add_child(plantRoot);
		plantRoot->set_owner(root);
		plantRoot->set_name("plantRoot");
		plantRoot->set_y_sort_enabled(true);
	} else {
		if (bClearTree) {
			TypedArray<Node> children = plantRoot->get_children();
			for (int i = 0; i < children.size(); i++) {
				Node *child = Object::cast_to<Node>(children[i]);
				if (child) {
					child->queue_free();
				}
			}
		}
	}

	// 生成树木
	Ref<PackedScene> ref = ResourceLoader::load("res://placeItem/bigPlant/placeBigPlantTemplate.tscn");
	if (treeDataArr.size() > 0) {
		for (auto &tempTreeData : treeDataArr) {
			Vector2i treePos = tempTreeData.pos;
			int x = treePos.x;
			int y = treePos.y;

			if (x != 0 && y != 0 && x != mapSize.x - 1 && y != mapSize.y - 1) {
				Vector2 gPos = baseTilemapLayer->to_global(baseTilemapLayer->map_to_local(treePos));

				RandomNumberGenerator rng;
				rng.set_seed(randomSeed + x * 13 + y * 17);
				int randIndex = rng.randi_range(0, tempTreeData.treeInfo.count - 1);
				Ref<Resource> treeRes = tempTreeData.treeInfo.treePathArr[randIndex];

				String thePath = treeRes->get_path();

				cPlaceItemNode *tree = Object::cast_to<cPlaceItemNode>(ref->instantiate());

				tree->set_itemRes(treeRes);
				// 从文件路径获取文件名（不包含扩展名）作为节点名称
				String theName = thePath.get_file().get_basename();
				plantRoot->add_child(tree);
				tree->set_owner(root);
				tree->set_name(theName);
				tree->set_global_position(gPos);
				tree->nat_setupPlaceItem(Dictionary());

				// 保存树木信息到数组中供编辑器查看
				Dictionary treeInfo;
				treeInfo["position"] = tempTreeData.pos;
				treeInfo["global_position"] = gPos;
				treeInfo["tree_path"] = thePath;
				treeInfo["tree_name"] = theName;
				treeInfo["tree_count"] = tempTreeData.treeInfo.count;
				treeInfo["selected_index"] = randIndex;
				treeInfo["tree_resource"] = treeRes; // 保存树的资源对象
				generatedTreesInfo.append(treeInfo);
			}
		}
	}

	print_line("Multi-layer terrain generation completed!");
}

void cSceneMake::_bind_methods() {
	ClassDB::bind_method(D_METHOD("makeBaseTile", "bClearTree"), &cSceneMake::makeBaseTile);

	ClassDB::bind_method(D_METHOD("set_mapsize", "mapsize"), &cSceneMake::set_mapsize);
	ClassDB::bind_method(D_METHOD("get_mapsize"), &cSceneMake::get_mapsize);

	ClassDB::bind_method(D_METHOD("set_mapType", "mapsize"), &cSceneMake::set_mapType);
	ClassDB::bind_method(D_METHOD("get_mapType"), &cSceneMake::get_maptype);

	ClassDB::bind_method(D_METHOD("set_BaseLayerTileset", "tileset"), &cSceneMake::set_BaseLayerTileset);
	ClassDB::bind_method(D_METHOD("get_baseLayerTileset"), &cSceneMake::get_baseLayerTileset);

	ClassDB::bind_method(D_METHOD("set_baseLayerDatas", "layerDatas"), &cSceneMake::set_baseLayerDatas);
	ClassDB::bind_method(D_METHOD("get_layerDatas"), &cSceneMake::get_layerDatas);

	ClassDB::bind_method(D_METHOD("set_baseTilemapLayer", "timemapLayer"), &cSceneMake::set_baseTilemapLayer);
	ClassDB::bind_method(D_METHOD("get_baseTilemapLayer"), &cSceneMake::get_baseTilemapLayer);

	ClassDB::bind_method(D_METHOD("set_secondLayerDatas", "layerDatas"), &cSceneMake::set_secondLayerDatas);
	ClassDB::bind_method(D_METHOD("get_secondLayerDatas"), &cSceneMake::get_secondLayerDatas);
	ClassDB::bind_method(D_METHOD("set_SecondLayerTileset", "tileset"), &cSceneMake::set_SecondLayerTileset);
	ClassDB::bind_method(D_METHOD("get_secondLayerTileset"), &cSceneMake::get_secondLayerTileset);
	ClassDB::bind_method(D_METHOD("set_secondTilemapLayer", "timemapLayer"), &cSceneMake::set_secondTilemapLayer);
	ClassDB::bind_method(D_METHOD("get_secondTilemapLayer"), &cSceneMake::get_secondTilemapLayer);

	ClassDB::bind_method(D_METHOD("set_thirdLayerDatas", "layerDatas"), &cSceneMake::set_thirdLayerDatas);
	ClassDB::bind_method(D_METHOD("get_thirdLayerDatas"), &cSceneMake::get_thirdLayerDatas);
	ClassDB::bind_method(D_METHOD("set_ThirdLayerTileset", "tileset"), &cSceneMake::set_ThirdLayerTileset);
	ClassDB::bind_method(D_METHOD("get_thirdLayerTileset"), &cSceneMake::get_thirdLayerTileset);
	ClassDB::bind_method(D_METHOD("set_thirdTilemapLayer", "timemapLayer"), &cSceneMake::set_thirdTilemapLayer);
	ClassDB::bind_method(D_METHOD("get_thirdTilemapLayer"), &cSceneMake::get_thirdTilemapLayer);

	ClassDB::bind_method(D_METHOD("set_secondLayerThreshold", "threshold"), &cSceneMake::set_secondLayerThreshold);
	ClassDB::bind_method(D_METHOD("get_secondLayerThreshold"), &cSceneMake::get_secondLayerThreshold);
	ClassDB::bind_method(D_METHOD("set_thirdLayerThreshold", "threshold"), &cSceneMake::set_thirdLayerThreshold);
	ClassDB::bind_method(D_METHOD("get_thirdLayerThreshold"), &cSceneMake::get_thirdLayerThreshold);

	// 各层形状控制参数绑定
	ClassDB::bind_method(D_METHOD("set_baseLayerNoiseFreq", "freq"), &cSceneMake::set_baseLayerNoiseFreq);
	ClassDB::bind_method(D_METHOD("get_baseLayerNoiseFreq"), &cSceneMake::get_baseLayerNoiseFreq);
	ClassDB::bind_method(D_METHOD("set_baseLayerContinuity", "continuity"), &cSceneMake::set_baseLayerContinuity);
	ClassDB::bind_method(D_METHOD("get_baseLayerContinuity"), &cSceneMake::get_baseLayerContinuity);

	ClassDB::bind_method(D_METHOD("set_secondLayerNoiseFreq", "freq"), &cSceneMake::set_secondLayerNoiseFreq);
	ClassDB::bind_method(D_METHOD("get_secondLayerNoiseFreq"), &cSceneMake::get_secondLayerNoiseFreq);
	ClassDB::bind_method(D_METHOD("set_secondLayerContinuity", "continuity"), &cSceneMake::set_secondLayerContinuity);
	ClassDB::bind_method(D_METHOD("get_secondLayerContinuity"), &cSceneMake::get_secondLayerContinuity);

	ClassDB::bind_method(D_METHOD("set_thirdLayerNoiseFreq", "freq"), &cSceneMake::set_thirdLayerNoiseFreq);
	ClassDB::bind_method(D_METHOD("get_thirdLayerNoiseFreq"), &cSceneMake::get_thirdLayerNoiseFreq);
	ClassDB::bind_method(D_METHOD("set_thirdLayerContinuity", "continuity"), &cSceneMake::set_thirdLayerContinuity);
	ClassDB::bind_method(D_METHOD("get_thirdLayerContinuity"), &cSceneMake::get_thirdLayerContinuity);

	// 随机种子方法绑定
	ClassDB::bind_method(D_METHOD("set_randomSeed", "seed"), &cSceneMake::set_randomSeed);
	ClassDB::bind_method(D_METHOD("get_randomSeed"), &cSceneMake::get_randomSeed);

	// 树木生成参数方法绑定
	ClassDB::bind_method(D_METHOD("set_treeMinDistance", "distance"), &cSceneMake::set_treeMinDistance);
	ClassDB::bind_method(D_METHOD("get_treeMinDistance"), &cSceneMake::get_treeMinDistance);

	// 生成的树木信息方法绑定
	ClassDB::bind_method(D_METHOD("set_generatedTreesInfo", "treesInfo"), &cSceneMake::set_generatedTreesInfo);
	ClassDB::bind_method(D_METHOD("get_generatedTreesInfo"), &cSceneMake::get_generatedTreesInfo);

	// Other组 - 其他配置
	ClassDB::add_property_group(get_class_static(), "Other", "");
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2I, "mapSize", PROPERTY_HINT_NONE, ""), "set_mapsize", "get_mapsize");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "mapType", PROPERTY_HINT_NONE, "forest,desert"), "set_mapType", "get_maptype");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "randomSeed", PROPERTY_HINT_RANGE, "0,999999"), "set_randomSeed", "get_randomSeed");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "treeMinDistance", PROPERTY_HINT_RANGE, "1,20"), "set_treeMinDistance", "get_treeMinDistance");
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "generatedTreesInfo", PROPERTY_HINT_ARRAY_TYPE, "Dictionary"), "set_generatedTreesInfo", "get_generatedTreesInfo");

	// 基础层组
	ClassDB::add_property_group(get_class_static(), "BaseLayer", "");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "baseLayerTileset", PROPERTY_HINT_RESOURCE_TYPE, "TileSet"), "set_BaseLayerTileset", "get_baseLayerTileset");
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "baseLayerDatas", PROPERTY_HINT_ARRAY_TYPE, MAKE_RESOURCE_TYPE_HINT("cLayerData")), "set_baseLayerDatas", "get_layerDatas");
	ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "baseTilemapLayer"), "set_baseTilemapLayer", "get_baseTilemapLayer");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "baseLayerNoiseFreq", PROPERTY_HINT_RANGE, "0.1,5.0"), "set_baseLayerNoiseFreq", "get_baseLayerNoiseFreq");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "baseLayerContinuity", PROPERTY_HINT_RANGE, "0.0,1.0"), "set_baseLayerContinuity", "get_baseLayerContinuity");

	// 第二层组
	ClassDB::add_property_group(get_class_static(), "SecondLayer", "");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "secondLayerTileset", PROPERTY_HINT_RESOURCE_TYPE, "TileSet"), "set_SecondLayerTileset", "get_secondLayerTileset");
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "secondLayerDatas", PROPERTY_HINT_ARRAY_TYPE, MAKE_RESOURCE_TYPE_HINT("cLayerData")), "set_secondLayerDatas", "get_secondLayerDatas");
	ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "secondTilemapLayer"), "set_secondTilemapLayer", "get_secondTilemapLayer");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "secondLayerThreshold", PROPERTY_HINT_RANGE, "0.0,1.0"), "set_secondLayerThreshold", "get_secondLayerThreshold");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "secondLayerNoiseFreq", PROPERTY_HINT_RANGE, "0.1,5.0"), "set_secondLayerNoiseFreq", "get_secondLayerNoiseFreq");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "secondLayerContinuity", PROPERTY_HINT_RANGE, "0.0,1.0"), "set_secondLayerContinuity", "get_secondLayerContinuity");

	// 第三层组
	ClassDB::add_property_group(get_class_static(), "ThirdLayer", "");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "thirdLayerTileset", PROPERTY_HINT_RESOURCE_TYPE, "TileSet"), "set_ThirdLayerTileset", "get_thirdLayerTileset");
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "thirdLayerDatas", PROPERTY_HINT_ARRAY_TYPE, MAKE_RESOURCE_TYPE_HINT("cLayerData")), "set_thirdLayerDatas", "get_thirdLayerDatas");
	ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "thirdTilemapLayer"), "set_thirdTilemapLayer", "get_thirdTilemapLayer");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "thirdLayerThreshold", PROPERTY_HINT_RANGE, "0.0,1.0"), "set_thirdLayerThreshold", "get_thirdLayerThreshold");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "thirdLayerNoiseFreq", PROPERTY_HINT_RANGE, "0.1,5.0"), "set_thirdLayerNoiseFreq", "get_thirdLayerNoiseFreq");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "thirdLayerContinuity", PROPERTY_HINT_RANGE, "0.0,1.0"), "set_thirdLayerContinuity", "get_thirdLayerContinuity");

	BIND_ENUM_CONSTANT(FOREST);
	BIND_ENUM_CONSTANT(DESERT);
}
