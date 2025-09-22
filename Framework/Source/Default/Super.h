
#ifndef DEFAULT_SUPER
#define DEFAULT_SUPER

template < typename t > struct sSuper { typedef t Super; };

#define SUPER( _type ) _type, private sSuper< _type >

#endif