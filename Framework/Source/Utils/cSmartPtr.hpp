#pragma once

#include <xutility>

#include <iostream>

template< typename t >
class cSmartPtr
{
private:
	t* m_ptr;
public:
	template< typename... ARGS >
	cSmartPtr( ARGS... _args ) :m_ptr( new t( _args... ) ) { }
	cSmartPtr( cSmartPtr< t >&& _other ) noexcept :m_ptr( _other.m_ptr ) { _other.m_ptr = nullptr; }
	~cSmartPtr() { if( m_ptr ) delete m_ptr; }

	cSmartPtr( cSmartPtr< t >& ) = delete;
	cSmartPtr( const cSmartPtr< t >& )  = delete;
	cSmartPtr( const cSmartPtr< t >&& ) = delete;
	cSmartPtr< t >& operator=( const cSmartPtr< t >& ) = delete;

	t&       operator* () { return *m_ptr; }
	t* const operator->() { return  m_ptr; }

	t& operator=( cSmartPtr< t >&& _other )
	{ 
		if( m_ptr )
			delete m_ptr;
		m_ptr = _other.m_ptr;
		_other.m_ptr = nullptr;
	}

	operator t* const () { return m_ptr; };

	template< typename ty >
	constexpr cSmartPtr< ty >&& Cast() { return ( cSmartPtr< ty >&& )( *( cSmartPtr< ty >* )this ); }

	t* const Get() { return m_ptr; }
};