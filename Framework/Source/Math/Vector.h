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
	};

	template < typename t >
	struct sVector3
	{
		t x, y,z;
	};

	template < typename t >
	struct sVector4
	{
		t x, y, z, w;
	};

	DEF_VEC_TYPE( float, f )
	DEF_VEC_TYPE( double, d )
	DEF_VEC_TYPE( int, i )
}
