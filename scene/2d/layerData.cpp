#include "layerData.h"

void layerData::set_minV(float inMinV) {
	minV = inMinV;
}

float layerData::get_minV() {
	return minV;
}

void layerData::_bind_methods() {
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "minV", PROPERTY_HINT_RANGE, "0,1,0.01"), "set_minV", "get_minV");

}
