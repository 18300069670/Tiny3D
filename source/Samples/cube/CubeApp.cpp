

#include "CubeApp.h"


using namespace Tiny3D;


CubeApp::CubeApp()
{

}

CubeApp::~CubeApp()
{

}

bool CubeApp::applicationDidFinishLaunching()
{
    Renderer *renderer = T3D_ENTRANCE.getActiveRenderer();
    renderer->setRenderMode(Renderer::E_RM_WIREFRAME);

    SGNodePtr root = T3D_SCENE_MGR.getRoot();
    
    // ����任���
    SGTransformNodePtr node = SGTransformNode::create();
    root->addChild(node);
    node->lookAt(Vector3(-1.0, 1.0, 2.0), Vector3::ZERO, Vector3::UNIT_Y);

    {
        // ������
        SGCameraPtr camera = SGCamera::create();
        node->addChild(camera);
        camera->setProjectionType(SGCamera::E_PT_PERSPECTIVE);

        Radian fovY(Math::PI * Real(0.5));
        Real ratio = Real(960) / Real(640);
        camera->setPerspective(fovY, ratio, 0.5, 1000.0);

        // �ӿ�
        ViewportPtr viewport = mRenderWindow->addViewport(camera, 0, 0.0, 0.0, 1.0, 1.0);
        viewport->setBackgroundColor(Color4::BLACK);
    }

    // �任���
    node = SGTransformNode::create();
    root->addChild(node);

    {
        // ������
        SGBoxPtr box = SGBox::create("");
        node->addChild(box);
    }

    return true;
}
