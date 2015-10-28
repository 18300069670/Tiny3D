

#include "Resource/T3DResource.h"


namespace Tiny3D
{
    Resource::Resource(const String &strName)
        : mSize(0)
        , mIsLoaded(false)
        , mName(strName)
    {

    }

    Resource::~Resource()
    {
        if (mIsLoaded)
            unload();
    }

    void Resource::unload()
    {

    }
}