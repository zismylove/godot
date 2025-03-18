#include "cSceneMake.h"

#include "cPlaceItemNode.h"
#include "core/math/random_number_generator.h"


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

void cSceneMake::makeBaseTile(bool bClearTree) {
	//构建基础层
	if(baseTilemapLayerPath.is_empty()) {
		ERR_PRINT("the baselayer is null");
		return;
	}
	baseTilemapLayer = Object::cast_to<TileMapLayer>(get_node(baseTilemapLayerPath));
	if(!baseTilemapLayer) {
		ERR_PRINT("the baselayer is null");
		return;
	}

	if(!baseLayerTileset.is_valid()) {
		ERR_PRINT("the tileset is null");
		return;
	}

	baseTilemapLayer->set_tile_set(baseLayerTileset);

	baseTilemapLayer->clear();

	Vector<spawnTileData>spawnArr;
	Vector<spawnTreeData>treeDataArr;

	cTreeTileinfo::treeInfo theTreeInfo;

	RandomNumberGenerator rng;

	for(auto& itLayerData:baseLayerDatas) {

		cLayerData* tempLayerData = Object::cast_to<cLayerData>(itLayerData);
		bool bHasTree = tempLayerData->addTileInfo.is_valid();
		String treePath;
		cTreeTileinfo* treeTileInfo;
		if(bHasTree) {
			treeTileInfo= Object::cast_to<cTreeTileinfo>(*tempLayerData->addTileInfo);
			if(treeTileInfo) {
				theTreeInfo = treeTileInfo->getRandomTreePath();
			} else {
				bHasTree = false;
			}
		}

		if(tempLayerData) {

			float thershold =tempLayerData->threshold;
			spawnTileData tempSpawnData;
			tempSpawnData.bTerrain = tempLayerData->bTerrain;
			tempSpawnData.terrainId = tempLayerData->terrainId;
			tempSpawnData.terrainSet = tempLayerData->terrainSet;
			tempSpawnData.sourceId = tempLayerData->sourceID;

			for(int x=0;x<mapSize.x;x++) {
				for(int y=0;y<mapSize.y;y++) {
					float noiseValue = float(tempLayerData->noise->get_noise_2d(x,y)+1)/2;

					if(noiseValue<thershold)
						continue;

					if(bHasTree) {

						rng.set_seed((x+1)*(y+1));
						float theV = rng.randf();
						if(theV<treeTileInfo->threshold){

						// noiseValue = float(treeTileInfo->noise->get_noise_2d(x,y)+1)/2.0;
						// if(noiseValue<treeTileInfo->threshold) {
							spawnTreeData tempTreeData;
							tempTreeData.pos = Vector2i(x,y);
							tempTreeData.treePath = treePath;
							treeDataArr.append(tempTreeData);
						}
					}

					tempSpawnData.posArr.append(Vector2i(x,y));

				}
			}
			if(tempLayerData->bTerrain) {
				baseTilemapLayer->set_cells_terrain_connect(tempSpawnData.posArr,tempSpawnData.terrainSet,tempSpawnData.terrainId);
			}
			else {
				for(auto& tempPos:tempSpawnData.posArr) {
					baseTilemapLayer->set_cell(tempPos,tempLayerData->sourceID,tempLayerData->atlasPos);
				}
			}
		}
	}

	Node* root = baseTilemapLayer->get_parent()->get_parent();
	Node2D* plantRoot = Object::cast_to<Node2D>(root->get_node(NodePath("plantRoot")));
	if(!plantRoot) {
		plantRoot=Object::cast_to<Node2D>(ClassDB::instantiate("Node2D"));
		root->add_child(plantRoot);
		plantRoot->set_owner(root);
		plantRoot->set_name("plantRoot");
		plantRoot->set_y_sort_enabled(true);
	} else {
		if(bClearTree) {
			TypedArray<Node> children = plantRoot->get_children();
			for(int i=0;i<children.size();i++) {
				Node* child =Object::cast_to<Node>(children[i]);
				if(child)
				{
					child->queue_free();
				}
			}
		}
	}
	Ref<PackedScene> ref = ResourceLoader::load("res://placeItem/bigPlant/placeBigPlantTemplate.tscn");
	if(treeDataArr.size()>0) {
		for(auto& tempTreeData:treeDataArr) {
			Vector2i treePos = tempTreeData.pos;
			String treePath = tempTreeData.treePath;

			int x = treePos.x;
			int y = treePos.y;

			if(x!=0&&y!=0&&x!=mapSize.x-1&&y!=mapSize.y-1) {

				Vector2 gPos = baseTilemapLayer->to_global(baseTilemapLayer->map_to_local(treePos));

				RandomNumberGenerator rng;
				int randIndex = rng.randi_range(0,theTreeInfo.count-1);
				Ref<Resource>treeRes = theTreeInfo.treePathArr[randIndex];

				cPlaceItemNode* tree =Object::cast_to<cPlaceItemNode>(ref->instantiate());

				tree->set_itemRes(treeRes);
				plantRoot->add_child(tree);
				tree->set_owner(root);
				tree->set_name(String("tree"));
				tree->set_global_position(gPos);
				tree->nat_setupPlaceItem(Dictionary());
			}
		}
	}
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

	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2I, "mapSize", PROPERTY_HINT_NONE, ""), "set_mapsize", "get_mapsize");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "mapType", PROPERTY_HINT_NONE, "forest,desert"), "set_mapType", "get_maptype");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "baseLayerTileset", PROPERTY_HINT_RESOURCE_TYPE, "TileSet"), "set_BaseLayerTileset", "get_baseLayerTileset");
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "baseLayerDatas", PROPERTY_HINT_ARRAY_TYPE, MAKE_RESOURCE_TYPE_HINT("cLayerData")), "set_baseLayerDatas", "get_layerDatas");

	ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "baseTilemapLayer"), "set_baseTilemapLayer", "get_baseTilemapLayer");

	BIND_ENUM_CONSTANT(FOREST);
	BIND_ENUM_CONSTANT(DESERT);
}
