#include <iostream>
#include <string>

template < class t >
class Singleton
{
private:
	static inline t* Instance = nullptr;
public:

	template< class... ARGS >
	static void init( ARGS... args )
	{
		if ( Instance )
		{
			std::cerr << "Error: " + std::string( __FUNCSIG__ ) + " is already initialized.";
			throw;
		}

		Instance = new t( args... );
	}
	
	static void destroy()
	{
		if (Instance)
			delete Instance;

		Instance = nullptr;
	}
	
	static t* Get()
	{
		return Instance;
	}

	static t& GetR()
	{
		return *Instance;
	}
};