

#include "HelloWorldApp.h"
#include <Tiny3D.h>


using namespace Tiny3D;

HelloWorldApp::HelloWorldApp()
{

}

HelloWorldApp::~HelloWorldApp()
{

}

int32_t HelloWorldApp::go()
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

bool HelloWorldApp::applicationDidFinishLaunching()
{
    Renderer *renderer = T3D_ENTRANCE.getActiveRenderer();
    renderer->setLightEnabled(false);
    renderer->setRenderMode(Renderer::E_RM_WIREFRAME);
    renderer->setAmbientLight(Color4::WHITE);

    T3D_ENTRANCE.getActiveRenderer()->setCullingMode(Renderer::E_CULL_NONE);

    SGNodePtr root = T3D_SCENE_MGR.getRoot();
    
    // 相机变换结点
    SGTransformNodePtr node = SGTransformNode::create();
    root->addChild(node);

    node->lookAt(Vector3(0.0, 20.0, 40.0), Vector3::ZERO, Vector3::UNIT_Y);

    // 相机结点
    SGCameraPtr camera = SGCamera::create();
    node->addChild(camera);
    camera->setProjectionType(SGCamera::E_PT_PERSPECTIVE);

    Radian fovY(Math::PI * Real(0.5));
    Real ratio = Real(960) / Real(640);
    camera->setPerspective(fovY, ratio, 1.0, 1000.0);

    // 视口
    ViewportPtr viewport = mRenderWindow->addViewport(camera, 0, 0.0, 0.0, 1.0, 1.0);
    viewport->setBackgroundColor(Color4::BLACK);

    // 变换结点
//     node = SGTransformNode::create();
//     root->addChild(node);
//     node->setPosition(1.0, 0.0, 0.0);
//     node->setOrientation(Radian(Math::PI * Real(0.5)), Vector3(0.0, 1.0, 0.0));
// 
//     {
//         // 立方体 #1 变换结点
//         SGTransformNodePtr node1 = SGTransformNode::create();
//         node->addChild(node1);
//         node1->setPosition(2.0, 0.0, 0.0);
//         node1->setScale(1.2, 1.2, 1.2);
//         node1->setOrientation(Radian(Math::PI / Real(6.0)), Vector3(0.0, 1.0, 0.0));
// 
//         {
//             // 立方体 #1 可见物体结点
//             SGShapePtr shape = SGShape::create();
//             node1->addChild(shape);
// 
//             {
//                 // 立方体 #1 可渲染物体结点
//                 SGBoxPtr box = SGBox::create("");
//                 shape->addChild(box);
//             }
//         }
// 
//         // 立方体 #2 变换结点
//         SGTransformNodePtr node2 = SGTransformNode::create();
//         node->addChild(node2);
//         node2->setPosition(-1.0, 0.0, 0.0);
// 
//         {
//             // 立方体 #2 可见物体结点
//             SGShapePtr shape = SGShape::create();
//             node2->addChild(shape);
// 
//             {
//                 // 立方体 #2 可渲染物体结点
//                 SGBoxPtr box = SGBox::create("");
//                 shape->addChild(box);
//             }
//         }
// 
//         // 球体 #1 变换结点
//         SGTransformNodePtr node3 = SGTransformNode::create();
//         node->addChild(node3);
//         node3->setPosition(-4.0, 0.0, 0.0);
// 
//         {
//             // 球体 #1 可见物体结点
//             SGShapePtr shape = SGShape::create();
//             node3->addChild(shape);
// 
//             {
//                 // 球体 #1 可渲染物体结点
//                 SGSpherePtr sphere = SGSphere::create("");
//                 shape->addChild(sphere);
//             }
//         }
//     }
// 
//     // 球体 #2 变换结点
//     node = SGTransformNode::create();
//     root->addChild(node);
//     node->setPosition(-10.0, 0.0, 0.0);
// 
//     {
//         // 球体 #2 可见物体结点
//         SGShapePtr shape = SGShape::create();
//         node->addChild(shape);
// 
//         {
//             // 球体 #2 可渲染物体结点
//             SGSpherePtr sphere = SGSphere::create("");
//             shape->addChild(sphere);
//         }
//     }

    // 模型 #1 变换结点
    node = SGTransformNode::create();
    root->addChild(node);
    node->setPosition(0.0, 0.0, 0.0);
//     node->setScale(200.0f, 200.0f, 200.0f);

    {
        // 模型 #1 可见物体结点
        SGModelPtr model = SGModel::create("knight.tmt");
        node->addChild(model);
//         SGShapePtr shape = SGShape::create();
//         node->addChild(shape);
// 
//         SGBoxPtr box = SGBox::create("");
//         shape->addChild(box);
    }

    return true;
}

void HelloWorldApp::applicationDidEnterBackground()
{

}

void HelloWorldApp::applicationWillEnterForeground()
{

}

void HelloWorldApp::applicationWillTerminate()
{

}
