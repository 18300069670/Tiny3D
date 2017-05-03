

#include "SkeletonApp.h"
#include <Tiny3D.h>


using namespace Tiny3D;


SkeletonApp::SkeletonApp()
{

}

SkeletonApp::~SkeletonApp()
{

}

int32_t SkeletonApp::go()
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

bool SkeletonApp::applicationDidFinishLaunching()
{
    Renderer *renderer = T3D_ENTRANCE.getActiveRenderer();
    renderer->setLightEnabled(true);
    renderer->setRenderMode(Renderer::E_RM_WIREFRAME);
    renderer->setAmbientLight(Color4::WHITE);

    SGNodePtr root = T3D_SCENE_MGR.getRoot();

    // ����
    SGIndicatorPtr indicator = SGIndicator::create(50, 50, 50);
    root->addChild(indicator);

    // ����任���
    SGTransformNodePtr node = SGTransformNode::create();
    root->addChild(node);
    node->lookAt(Vector3(150, 150, 150), Vector3::ZERO, Vector3::UNIT_Y);
//     node->lookAt(Vector3(10, 10, 10), Vector3::ZERO, Vector3::UNIT_Y);

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
//     node = SGTransformNode::create();
//     root->addChild(node);
// //     node->setPosition(0.0, -166.487442, 76.205284);
//     {
//         // ģ�� #1 �ɼ�������
//         SGModelPtr model = SGModel::create("������.tmt");
//         model->setRenderMode(SGModel::E_RENDER_SKELETON);
//         node->addChild(model);
// //         model->runAction("Take 001");
//     }

    node = SGTransformNode::create();
    root->addChild(node);
//     node->setPosition(20.0, -0, 0);
//     node->setOrientation(Radian(-Math::PI*0.5), Vector3::UNIT_Y);
    {
        SGModelPtr model = SGModel::create("skeleton.tmt");
        node->addChild(model);
        model->setRenderMode(SGModel::E_RENDER_SKELETON);
        model->runAction("Take 001");
//         model->runAction("Walk");

    }

//     node = SGTransformNode::create();
//     root->addChild(node);
//     {
//         // ������ #1 �ɼ�������
//         SGShapePtr shape = SGShape::create();
//         node->addChild(shape);
// 
//         {
//             // ������ #1 ����Ⱦ������
//             SGBoxPtr box = SGBox::create("");
//             shape->addChild(box);
//         }
//     }

    return true;
}

void SkeletonApp::applicationDidEnterBackground()
{

}

void SkeletonApp::applicationWillEnterForeground()
{

}

void SkeletonApp::applicationWillTerminate()
{

}
