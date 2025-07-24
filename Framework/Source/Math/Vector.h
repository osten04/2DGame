#ifndef MATH_VECTOR
#define MATH_VECTOR

#define DEF_VEC_TYPE( type, sufix )       \
typedef sVector2< type > sVector2##sufix; \
typedef sVector3< type > sVector3##sufix; \
typedef sVector4< type > sVector4##sufix;

namespace math
{
	
	template < typename t >
	struct sVector2
	{
		t x, y;

		inline sVector2 operator+=( const sVector2& _other ) { return sVector2{ x + _other.x, y + _other.y }; }
		inline sVector2 operator+ ( const sVector2& _other ) { return sVector2{ x + _other.x, y + _other.y }; }
		inline sVector2 operator*=( const sVector2& _other ) { return sVector2{ x * _other.x, y * _other.y }; }
		inline sVector2 operator* ( const sVector2& _other ) { return sVector2{ x * _other.x, y * _other.y }; }

		inline sVector2 operator* ( float _other ) { return sVector2{ x * _other, y * _other }; }
	};

	template < typename t >
	struct sVector3
	{
		t x, y, z;

		inline sVector3 operator+=( const sVector3& _other ) { return sVector3{ x + _other.x, y + _other.y, z + _other.z }; }
		inline sVector3 operator+ ( const sVector3& _other ) { return sVector3{ x + _other.x, y + _other.y, z + _other.z }; }
		inline sVector3 operator*=( const sVector3& _other ) { return sVector3{ x * _other.x, y * _other.y, z * _other.z }; }
		inline sVector3 operator* ( const sVector3& _other ) { return sVector3{ x * _other.x, y * _other.y, z * _other.z }; }
	};

	template < typename t >
	struct sVector4
	{
		t x, y, z, w;

		inline sVector4 operator+=( const sVector4& _other ) { return sVector3{ x + _other.x, y + _other.y, z + _other.z, w + _other.w }; }
		inline sVector4 operator+ ( const sVector4& _other ) { return sVector3{ x + _other.x, y + _other.y, z + _other.z, w + _other.w }; }
		inline sVector4 operator*=( const sVector4& _other ) { return sVector3{ x * _other.x, y * _other.y, z * _other.z, w * _other.w }; }
		inline sVector4 operator* ( const sVector4& _other ) { return sVector3{ x * _other.x, y * _other.y, z * _other.z, w * _other.w }; }
	};

	DEF_VEC_TYPE( float, f )
	DEF_VEC_TYPE( double, d )
	DEF_VEC_TYPE( int, i )
}

#endif