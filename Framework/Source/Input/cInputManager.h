#include "Singleton.hpp"
#include "cInput.hpp"

#include "vector"

class cInputManager : public Singleton< cInputManager >
{
public:
	cInputManager( void* _window );
	~cInputManager();

	template< class t >
	void Subscribe( t* _c, void ( t::* _memberfunction )( const sInput& ) )
	{
		m_callbacks.push_back( new cInput< t >( _c, _memberfunction ) );
	}

	void UnSubscribe( void* _owner );

	void CallCallbacks( const sInput& _input );

private:
	std::vector< iInput* > m_callbacks;

};