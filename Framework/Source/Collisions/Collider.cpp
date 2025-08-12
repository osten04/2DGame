#include "Collider.h"

bool Collider::IsColliding( const Collider::cBoxCollider& _first, const Collider::cBoxCollider& _second )
{
	return
		( _first.pos.x - _second.pos.x < _first.extent.x + _second.extent.x ) &&
		( _first.pos.y - _second.pos.y < _first.extent.y + _second.extent.y );
}

bool Collider::IsColliding( const Collider::cCircleCollider& _first, const Collider::cCircleCollider& _second )
{
	return ( _first.pos - _second.pos ).Length() < _first.rad + _second.rad;
}
