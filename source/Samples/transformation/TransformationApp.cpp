

#include "TransformationApp.h"
#include <Tiny3D.h>


using namespace Tiny3D;


TransformationApp::TransformationApp()
{

}

TransformationApp::~TransformationApp()
{

}

int32_t TransformationApp::go()
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

bool TransformationApp::applicationDidFinishLaunching()
{
    Renderer *renderer = T3D_ENTRANCE.getActiveRenderer();

    SGNodePtr root = T3D_SCENE_MGR.getRoot();
    
    // 相机变换结点
    SGTransformNodePtr node = SGTransformNode::create();
    root->addChild(node);
    node->lookAt(Vector3(0.0, 2.0, 10.0), Vector3::ZERO, Vector3::UNIT_Y);

    {
        // 相机结点
        SGCameraPtr camera = SGCamera::create();
        node->addChild(camera);
        camera->setProjectionType(SGCamera::E_PT_PERSPECTIVE);

        Radian fovY(Math::PI * Real(0.5));
        Real ratio = Real(960) / Real(640);
        camera->setPerspective(fovY, ratio, 0.5, 1000.0);

        // 视口
        ViewportPtr viewport = mRenderWindow->addViewport(camera, 0, 0.0, 0.0, 1.0, 1.0);
        viewport->setBackgroundColor(Color4::BLACK);
    }

    // 变换结点
    node = SGTransformNode::create();
    root->addChild(node);
    node->setPosition(0.0, 0.0, 0.0);

    {
        // 立方体 #1 变换结点
        SGTransformNodePtr node1 = SGTransformNode::create();
        node->addChild(node1);
        node1->setPosition(2.0, 0.0, 0.0);
        node1->setScale(1.2, 1.2, 1.2);
        node1->setOrientation(Radian(Math::PI / Real(6.0)), Vector3(0.0, 1.0, 0.0));

        {
            // 立方体 #1 可渲染物体结点
            SGBoxPtr box = SGBox::create("");
            node1->addChild(box);
        }

        // 立方体 #2 变换结点
        SGTransformNodePtr node2 = SGTransformNode::create();
        node->addChild(node2);
        node2->setPosition(-1.0, 0.0, 0.0);

        {
            // 立方体 #2 可渲染物体结点
            SGBoxPtr box = SGBox::create("");
            node2->addChild(box);
        }

        // 球体 #1 变换结点
        SGTransformNodePtr node3 = SGTransformNode::create();
        node->addChild(node3);
        node3->setPosition(-4.0, 0.0, 0.0);

        {
            // 球体 #1 可渲染物体结点
            SGSpherePtr sphere = SGSphere::create("");
            node3->addChild(sphere);
        }
    }

    // 球体 #2 变换结点
    node = SGTransformNode::create();
    root->addChild(node);
    node->setPosition(-10.0, 0.0, 0.0);

    {
        // 球体 #2 可渲染物体结点
        SGSpherePtr sphere = SGSphere::create("");
        node->addChild(sphere);
    }

    return true;
}

void TransformationApp::applicationDidEnterBackground()
{

}

void TransformationApp::applicationWillEnterForeground()
{

}

void TransformationApp::applicationWillTerminate()
{

}
