

#include "Render/T3DSceneManager.h"
#include "Render/T3DSGCamera.h"
#include "Render//T3DSGTransformNode.h"
#include "Render/T3DSGRenderable.h"
#include "Render/T3DRenderer.h"
#include "Render/T3DRenderQueue.h"


namespace Tiny3D
{
    T3D_INIT_SINGLETON(SceneManager);

    SceneManager::SceneManager()
        : mRoot(nullptr)
        , mRenderer(nullptr)
        , mRenderQueue(nullptr)
    {
        mRenderQueue = RenderQueue::create();
        mRoot = SGTransformNode::create();
        mRoot->setName("Root");
    }

    SceneManager::~SceneManager()
    {
        mRenderQueue = nullptr;
        mRoot = nullptr;
    }

    void SceneManager::renderScene(const SGCameraPtr &camera, const ViewportPtr &viewport)
    {
        mCurCamera = camera;
        mRenderer->setViewport(viewport);

        // ���ȸ�������任
        mCurCamera->updateTransform();

        // ����scene graph�����н��
        mRoot->updateTransform();

        // ��scene graph�����н����frustum culling
        mRoot->frustumCulling(mCurCamera->getBound(), mRenderQueue);

        // ֱ�Ӷ���Ⱦ���еĶ�����Ⱦ
        mRenderer->beginRender(viewport->getBackgroundColor());
        mRenderQueue->render(mRenderer);
        mRenderer->endRender();
    }
}
