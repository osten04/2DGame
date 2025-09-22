#include "Singleton.hpp"
#include "cInput.hpp"

#include "vector"

class iInput
{
public:
	virtual void CB( const sInput& _input ) = 0;
	virtual void* GetObject() = 0;
};

template < class t >
class cInput : public iInput
{
private:

	t* m_instance;
	void ( t::* m_memberfunc )( const sInput& );

public:

	cInput( t* _instance, void ( t::* memberfunction )( const sInput& ) ) : m_instance( _instance ), m_memberfunc( memberfunction ) { }

	virtual void CB( const sInput& _input ) override { ( m_instance->*m_memberfunc )( _input ); }
	virtual void* GetObject() { return m_instance; }
};

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