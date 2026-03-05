#include "cPlaceItemNode.h"

void cPlaceItemNode::set_itemRes(const Ref<Resource> &inItemRes) {
	itemRes = inItemRes;
}

Ref<Resource> cPlaceItemNode::get_itemRes() {
	return itemRes;
}

void cPlaceItemNode::nat_setupPlaceItem(const Dictionary &inData) {
	GDVIRTUAL_CALL(setupPlaceItem, inData);
}

void cPlaceItemNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_itemRes", "itemRes"), &cPlaceItemNode::set_itemRes);
	ClassDB::bind_method(D_METHOD("get_itemRes"), &cPlaceItemNode::get_itemRes);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "itemRes", PROPERTY_HINT_RESOURCE_TYPE, ""), "set_itemRes", "get_itemRes");

	GDVIRTUAL_BIND(setupPlaceItem, "inData");
}
