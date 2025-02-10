#include "cAssetManager.h"

cAssetManager::~cAssetManager()
{
    for ( iAsset* element : m_assets )
    {
        delete element;
    }
}

void cAssetManager::draw()
{
    for ( auto element : m_assets )
    {
        element->draw();
    }
}
