
typedef struct row { float x, y, z, w; };

struct sMatrix4x4
{
public:
	sMatrix4x4()
		: x( { 1.0f, 0.0f, 0.0f, 0.0f } )
		, y( { 0.0f, 1.0f, 0.0f, 0.0f } )
		, z( { 0.0f, 0.0f, 1.0f, 0.0f } )
		, w( { 0.0f, 0.0f, 0.0f, 1.0f } )
	{ }

	sMatrix4x4( const row& _x, const row& _y, const row& _z, const row& _w ) : x( _x ), y( _y ), z( _z ), w( _w ) { }

	sMatrix4x4 operator*( const sMatrix4x4& _o )
	{
		return sMatrix4x4 {
			{ 0.0f, 0.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 0.0f }
		};
	}


	float* data() { return &x.x; }

	row x, y, z, w;
};