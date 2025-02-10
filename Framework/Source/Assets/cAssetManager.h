
#ifndef HEADER_CASSETMANAGER
#define HEADER_CASSETMANAGER

#include "Singleton.hpp"

#include "list"
#include "Assets/cAsset.h"

class cAssetManager : public Singleton< cAssetManager >
{
    
    std::list< iAsset* > m_assets;
public:
    cAssetManager() = default;
    ~cAssetManager();

    template< class t, class... Args >
    t* spawn( Args... _args )
    {
        static_assert( std::is_base_of_v< cAsset< t >, t >, "t must derive from cAsset" );
        t* _t = new t( _args... );
        m_assets.push_back( ( iAsset* )_t );
        return _t;
    }

    void draw();
    
};

#endif