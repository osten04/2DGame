
#ifndef HEADER_CASSETMANAGER
#define HEADER_CASSETMANAGER

#include "Singleton.hpp"

#include "list"
#include "Assets/cAsset.h"

class cAssetManager : Singleton< cAssetManager >
{
    cAssetManager() = default;
    ~cAssetManager();
    
    std::list< iAsset* > m_assets;
public:

    template< class t, class... Args >
    t* spawn( Args... _args )
    {
        static_assert( std::is_base_of_v< cAsset< t >, t >, "t must derive from cAsset" );
        new t( _args... );
    }

    void draw();
    
};

#endif