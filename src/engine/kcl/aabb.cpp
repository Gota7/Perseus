#include "aabb.h"
#include <cmath>

bool KclAABB::Collides(KclAABB other) {
    if (abs(center.x - other.center.x) > halfSize.x + other.halfSize.x) return false;
	if (abs(center.y - other.center.y) > halfSize.y + other.halfSize.y) return false;
	return true;
}