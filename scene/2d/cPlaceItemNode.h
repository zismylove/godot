#pragma once
#include "node_2d.h"
#include "core/object/object.h"

class cPlaceItemNode:public Node2D {
	GDCLASS(cPlaceItemNode,Node2D)
public:

	Ref<Resource>itemRes;

	void set_itemRes(const Ref<Resource>&inItemRes);
	Ref<Resource>get_itemRes();

protected:
	static void _bind_methods();

};
