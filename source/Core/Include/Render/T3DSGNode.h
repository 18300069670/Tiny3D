
#ifndef __T3D_SG_NODE_H__
#define __T3D_SG_NODE_H__


#include "Misc/T3DNode.h"
#include "T3DMath.h"
#include "T3DVector3.h"
#include "T3DMatrix3.h"
#include "T3DMatrix4.h"
#include "Misc/T3DSmartPtr.h"
#include "T3DTypedef.h"


namespace Tiny3D
{
    class T3D_ENGINE_API SGNode : public Node
    {
        friend class SceneManager;

        T3D_DISABLE_COPY(SGNode);
    protected:
        /**
         * @brief Constructor.
         * @remarks
         *      All derived class should implement a static create() method to
         *      create the concrete object.
         */
        SGNode(uint32_t unID = E_NID_AUTOMATIC);

    public:
        virtual ~SGNode();

        void setUserData(long_t data);
        long_t getUserData() const;

        void setUserObject(const ObjectPtr &rkObject);
        const ObjectPtr &getUserObject() const;
        ObjectPtr getUserObject();

        virtual void setDirty(bool isDirty, bool recursive = false);
        bool isDirty() const;

        virtual void setVisible(bool visible);
        bool isVisible() const;

    protected:
        /** 
         * @brief Perform self transformation and recursively call all children
         *      updateTransform()
         */
        virtual void updateTransform();

        /**
         * @brief Perform frustum culling against a frustum bound and recursively
         *      call all children frustumCulling()
         */
        virtual void frustumCulling(const BoundPtr &bound, const RenderQueuePtr &queue);

        virtual void cloneProperties(const NodePtr &node) const;

    private:
        long_t      mUserData;      /// Store user data
        ObjectPtr   mUserObject;   /// Pointer to user object

        bool        mIsDirty;
        bool        mIsVisible;
    };
}


#include "T3DSGNode.inl"


#endif  /*__T3D_SG_NODE_H__*/