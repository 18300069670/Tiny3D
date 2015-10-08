

#ifndef __T3D_BUILDER_H__
#define __T3D_BUILDER_H__


#include "T3DPrerequisites.h"
#include "T3DSingleton.h"
#include "T3DCommon.h"


namespace Tiny3D
{
    /**
     * @brief The starting point class of the Tiny3D system.
     * @remarks
     *      The Tiny3D::Builder class represents a starting point for
     *      the application. From here, the application can gain access to
     *      fundamentals of the system, listing the renderer available,
     *      management of saved configurations. An instance of Builder must be
     *      created before any other Tiny3D operations are called.
     *      Once an instance has been created, the same instance is accessible
     *      throughout the life of that object by using Builder::getInstance()
     *      (as a reference) or Builder::getInstancePtr() (as a pointer).
     *      And then you should call Builder::run() for starting Tiny3D.
     */
    class T3D_ENGINE_API Builder : public Singleton<Builder>
    {
    public:
        /** Default constructor. */
        Builder();

        /** Destructor. */
        virtual ~Builder();

        /**
         * @brief Enumerate all available name of renderer in list.
         * @param [out] rRendererList
         *      list of available renderer instances.
         * @return void
         */
        void enumerateRendererList(RendererNameList &rRendererNameList) const;

        /**
         * @brief Create renderer instance.
         * @param [in] strRendererName
         *      Name of renderer.
         * @return Instance of renderer.
         */
        Renderer *createRenderer(const TString &strRendererName);

        /**
         * @brief Set active renderer.
         * @param [in] pRenderer
         *      pointer to an available renderer instance.
         * @return void
         * @remarks
         *      The renderer must be one of all available renderer. You should
         *      call Builder::enumerateRendererList() to retrieve all available
         *      renderer in list.
         */
        void setActiveRenderer(Renderer *pRenderer);

        /**
         * @brief Create render window.
         * @param [in] rkCreatedParam 
         *      reference to RenderWindowCreateParam instance. 
         *      See RenderWindowCreateParam.
         * @param [in] rkCreatedParamEx : 
         *      reference to RenderWindowCreateParamEx instance. 
         *      See RenderWindowCreateParamEx.
         * @return pointer to an instance for RenderWindow if create succeeded.
         * @see RenderWindowCreatedParam
         * @see RenderWindowCreatedParamEx
         */
        RenderWindow *createRenderWindow(
            const RenderWindowCreateParam &rkCreatedParam,
            const RenderWindowCreateParamEx &rkCreatedParamEx);

        /**
         * @brief Run Tiny3D
         * @param void
         * @return void
         */
        bool run();

        /**
         * @brief Set application event listener.
         * @param [in] pListener
         *      pointer to application listener instance.
         * @return void
         */
        void setApplicationListener(ApplicationListener *pListener);

    protected:
        System  *mSystem;
    };

    #define T3D_BUILDER         Builder::getInstance()
    #define T3D_BUILDER_PTR     Builder::getInstancePtr()
}


#endif  /*__T3D_BUILDER_H__*/
