#pragma once

#include "core/io/resource.h"

class layerData: public Resource {
	GDCLASS(layerData, Resource);
public:

	float minV;

	float maxV;

	int sourceID = -1;

	Vector2i atlasPos = Vector2i(0,0);

	int terrainSet = 0;

	int terrainId = 0;

	void set_minV(float inMinV);

	float get_minV();

protected:
	static void _bind_methods();

};
