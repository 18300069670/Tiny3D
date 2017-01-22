

#include "ModelApp.h"
#include <Tiny3D.h>


using namespace Tiny3D;


ModelApp::ModelApp()
{

}

ModelApp::~ModelApp()
{

}

int32_t ModelApp::go()
{
    Entrance *entrance = new Entrance();

    entrance->setApplicationListener(this);

    RenderWindow *renderWindow = nullptr;
    Entrance::getInstance().initialize(true, renderWindow);
    mRenderWindow = renderWindow;
    Entrance::getInstance().run();

    delete entrance;

    return 0;
}

bool ModelApp::applicationDidFinishLaunching()
{
    Renderer *renderer = T3D_ENTRANCE.getActiveRenderer();
    renderer->setLightEnabled(true);
    renderer->setRenderMode(Renderer::E_RM_WIREFRAME);
    renderer->setAmbientLight(Color4::WHITE);

    SGNodePtr root = T3D_SCENE_MGR.getRoot();
    
    // ����任���
    SGTransformNodePtr node = SGTransformNode::create();
    root->addChild(node);
    node->lookAt(Vector3(5.0, 2.0, 10.0), Vector3::ZERO, Vector3::UNIT_Y);

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

    // ģ�� #1 �任���
    node = SGTransformNode::create();
    root->addChild(node);
    node->setPosition(0.0, 0.0, 0.0);
//     node->setOrientation(Radian(-Math::PI*0.5), Vector3::UNIT_X);
	node->setScale(0.02, 0.02, 0.02);
    {
        // ģ�� #1 �ɼ�������
        SGModelPtr model = SGModel::create("������.tmt");
        node->addChild(model);
    }

    return true;
}

void ModelApp::applicationDidEnterBackground()
{

}

void ModelApp::applicationWillEnterForeground()
{

}

void ModelApp::applicationWillTerminate()
{

}
