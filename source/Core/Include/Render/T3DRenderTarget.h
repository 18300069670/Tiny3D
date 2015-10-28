

#ifndef __T3D_RENDER_TARGET_H__
#define __T3D_RENDER_TARGET_H__


#include "T3DPrerequisites.h"


namespace Tiny3D
{
    class T3D_ENGINE_API RenderTarget
    {
    public:
        RenderTarget();
        virtual ~RenderTarget();

        const String &getName() const;

        void getMetrics(int32_t &nWidth, int32_t &nHeight,
            int32_t &nColorDepth) const;

        int32_t getWidth() const;
        int32_t getHeight() const;

        int32_t getColorDepth() const;

        virtual void update();

        Viewport *addViewport(SGCamera *camera, int32_t nZOrder, 
            Real left, Real top, Real width, Real height);

        void removeViewport(int32_t nZOrder);

        void removeAllViewports();

        uint32_t getNumViewports() const;

        Viewport *getViewport(uint32_t unIndex) const;

        void addListener(RenderTargetListener *pListener);
        void removeListener(RenderTargetListener *pListener);
        void removeAllListener();

    protected:
        typedef std::map<int32_t, Viewport*>    ViewportList;
        typedef ViewportList::iterator          ViewportListItr;
        typedef ViewportList::const_iterator    ViewportListConstItr;
        typedef ViewportList::value_type        ViewportValue;

        typedef std::list<RenderTargetListener*>    ListenerList;
        typedef ListenerList::iterator              ListenerListItr;

        int32_t         mWidth;
        int32_t         mHeight;
        int32_t         mColorDepth;

        String          mName;

        ViewportList    mViewportList;

        ListenerList    mListenerList;
    };
}


#include "T3DRenderTarget.inl"


#endif  /*__T3D_RENDER_TARGET_H__*/