#pragma once

#include "Math/Vector.h"

namespace Collider
{
	struct cBoxCollider
	{
		math::sVector2f pos, extent;
	};

	struct cCircleCollider
	{
		math::sVector2f pos;
		float           rad;
	};

	bool IsColliding( const Collider::cBoxCollider&    _first, const Collider::cBoxCollider&    _second );
	bool IsColliding( const Collider::cCircleCollider& _first, const Collider::cCircleCollider& _second );
}