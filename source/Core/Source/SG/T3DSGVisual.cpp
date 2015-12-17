


#include "SG/T3DSGVisual.h"
#include "SG/T3DSGTransformNode.h"
#include "SG/T3DSGCamera.h"
#include "SG/T3DSceneManager.h"
#include "Misc/T3DEntrance.h"


namespace Tiny3D
{
    SGVisual::SGVisual(uint32_t unID /* = E_NID_AUTOMATIC */)
        : SGNode(unID)
        , mBound(nullptr)
        , mIsVisible(true)
    {

    }

    SGVisual::~SGVisual()
    {

    }

    void SGVisual::setVisible(bool visible)
    {
        mIsVisible = visible;
    }

    void SGVisual::updateBound()
    {
        SGTransformNode *parent = (SGTransformNode *)getParent();

        if (isDirty())
        {
            mWorldTransform = parent->getLocalToWorldTransform();

            if (mBound != nullptr)
            {
                mBound->setTransform(mWorldTransform);
            }

            setDirty(false);
        }
    }

    void SGVisual::updateTransform()
    {
        // update bound
        T3D_ASSERT(getParent()->getNodeType() == SGNode::E_NT_TRANSFORM);

        updateBound();

        // check this node in frustum
        if (getNodeType() != SGNode::E_NT_CAMERA)
        {
            // ���������㣬����Ҫ�ж��Ƿ�ɼ����Ƿ���Ҫ��Ⱦ
            SGCamera *camera = T3D_SCENE_MGR.getCurCamera();

            Bound *bound = camera->getBound();

            mIsInFrustum = bound->test(*mBound);

            // continue updating all children node
            SGNode::updateTransform();
        }
    }

    void SGVisual::cloneProperties(SGNode *node) const
    {
        SGNode::cloneProperties(node);

        SGVisual *newNode = (SGVisual *)node;
        newNode->mWorldTransform = mWorldTransform;

        if (mBound != nullptr)
        {
            newNode->mBound = mBound->clone();
        }
        else
        {
            newNode->mBound = nullptr;
        }

        newNode->mIsVisible = mIsVisible;
    }
}
