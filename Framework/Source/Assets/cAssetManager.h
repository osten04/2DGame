
#ifndef HEADER_CASSETMANAGER
#define HEADER_CASSETMANAGER

#include <vector>

#include "Singleton.hpp"

#include "Assets/cAsset.h"

#include "Utils/cSmartPtr.hpp"

struct ManagerInitiator
{
    void ( *init )();
    void ( *destroy )();
};

class cAssetManager : public Singleton< cAssetManager >
{
    
    std::vector< cSmartPtr< iAsset > > m_assets;
public:
    cAssetManager();
    ~cAssetManager();

    template< class t, class... Args >
    t* const spawn( Args... _args )
    {
        static_assert( std::is_base_of_v< iAsset, t >, "t must derive from cAsset");

        cSmartPtr< t >&& asset = cSmartPtr< t >(_args...);
        t* const out = asset;
        m_assets.push_back( asset.Cast< iAsset >() );
        return out;
    }

    void draw( math::sVector2i _screen );

private:
    static inline std::vector< ManagerInitiator > m_regestry = std::vector< ManagerInitiator >();

public:
    template< class t >
    static void RegisterManager()
    {
        cAssetManager::m_regestry.push_back( ManagerInitiator { .init = &cAssetRenderer< t >::init, .destroy = &cAssetRenderer< t >::destroy } );
    }
};

template< class t >
struct cReflectManager
{
    cReflectManager() { cAssetManager::RegisterManager< t >(); }

    static cReflectManager< t > creator;

};

#define RegisterAssetManager( t ) template<> cReflectManager< t > cReflectManager< t >::creator{}

#endif