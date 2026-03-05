#pragma once

#include "core/object/object.h"
#include "node_2d.h"

class cPlaceItemNode : public Node2D {
	GDCLASS(cPlaceItemNode, Node2D)

public:
	Ref<Resource> itemRes;

	void set_itemRes(const Ref<Resource> &inItemRes);
	Ref<Resource> get_itemRes();

	void nat_setupPlaceItem(const Dictionary &inData);

protected:
	static void _bind_methods();
	GDVIRTUAL1(setupPlaceItem, Dictionary);
};
