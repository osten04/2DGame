#include "cAssetManager.h"

cAssetManager::~cAssetManager()
{
    for ( iAsset* element : m_assets )
    {
        delete element;
    }
}

void cAssetManager::draw( math::sVector2i _screen )
{
    for ( auto element : m_assets )
    {
        element->draw( _screen );
    }
}
