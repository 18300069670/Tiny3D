

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
    renderer->setRenderMode(Renderer::E_RM_SOLID);
    renderer->setAmbientLight(Color4::WHITE);
    renderer->setLightEnabled(true);

//     T3D_ENTRANCE.getActiveRenderer()->setCullingMode(Renderer::E_CULL_NONE);

    SGNodePtr root = T3D_SCENE_MGR.getRoot();
    
    // ����任���
    SGTransformNodePtr node = SGTransformNode::create();
    root->addChild(node);

    node->lookAt(Vector3(0.0, 2.0, 4.0), Vector3::ZERO, Vector3::UNIT_Y);

    // ������
    SGCameraPtr camera = SGCamera::create();
    node->addChild(camera);

    camera->setProjectionType(SGCamera::E_PT_PERSPECTIVE);

    Radian fovY(Math::PI * Real(0.5));
    Real ratio = Real(960) / Real(640);
    camera->setPerspective(fovY, ratio, 1.0, 1000.0);

    // ������任���
    node = SGTransformNode::create();
    root->addChild(node);
    node->setPosition(1.0, 0.0, 0.0);
//     node->setOrientation(Radian(Math::PI * Real(0.5)), Vector3(0.0, 1.0, 0.0));

    SGTransformNodePtr node1 = SGTransformNode::create();
    node->addChild(node1);
    node1->setPosition(2.0, 0.0, 0.0);
//     node1->setScale(1.2, 1.2, 1.2);
    node1->setOrientation(Radian(Math::PI / Real(6.0)), Vector3(0.0, 1.0, 0.0));

    // ������ #1 mesh
    SGShapePtr shape = SGShape::create();
    node1->addChild(shape);
    
    SGBoxPtr box = SGBox::create("");
    shape->addChild(box);

    SGTransformNodePtr node2 = SGTransformNode::create();
    node->addChild(node2);
    node2->setPosition(-1.0, 0.0, 0.0);

    // #2 Mesh
    shape = SGShape::create();
    node2->addChild(shape);
    
    box = SGBox::create("");
    shape->addChild(box);

    SGTransformNodePtr node3 = SGTransformNode::create();
    node->addChild(node3);
    node3->setPosition(-4.0, 0.0, 0.0);

    // #3 Mesh
    shape = SGShape::create();
    node3->addChild(shape);

    SGSpherePtr sphere = SGSphere::create("");
    shape->addChild(sphere);

    node = SGTransformNode::create();
    root->addChild(node);
    node->setPosition(-10.0, 0.0, 0.0);

    shape = SGShape::create();
    node->addChild(shape);

    sphere = SGSphere::create("");
    shape->addChild(sphere);

    ViewportPtr viewport = mRenderWindow->addViewport(camera, 0, 0.0, 0.0, 1.0, 1.0);
    viewport->setBackgroundColor(Color4::BLACK);

//     Matrix4 mat(false);
//     mat.setTranslate(Vector3(5.0, 5.0, 5.0));

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
