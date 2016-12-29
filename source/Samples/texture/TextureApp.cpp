

#include "TextureApp.h"
#include <Tiny3D.h>


using namespace Tiny3D;


TextureApp::TextureApp()
{

}

TextureApp::~TextureApp()
{

}

int32_t TextureApp::go()
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

bool TextureApp::applicationDidFinishLaunching()
{
    Renderer *renderer = T3D_ENTRANCE.getActiveRenderer();
    renderer->setLightEnabled(true);
    renderer->setRenderMode(Renderer::E_RM_WIREFRAME);
//     renderer->setRenderMode(Renderer::E_RM_SOLID);
    renderer->setAmbientLight(Color4::WHITE);

//     T3D_ENTRANCE.getActiveRenderer()->setCullingMode(Renderer::E_CULL_NONE);

    SGNodePtr root = T3D_SCENE_MGR.getRoot();
    
    // ����任���
    SGTransformNodePtr node = SGTransformNode::create();
    root->addChild(node);

    node->lookAt(Vector3(0.0, -200.0, 0.0), Vector3::ZERO, Vector3::UNIT_Z);
//     node->lookAt(Vector3(0.0, 2.0, 10.0), Vector3::ZERO, Vector3::UNIT_Y);

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

    // �任���
//     node = SGTransformNode::create();
//     root->addChild(node);
//     node->setPosition(1.0, 0.0, 0.0);
//     node->setOrientation(Radian(Math::PI * Real(0.5)), Vector3(0.0, 1.0, 0.0));
// 
//     {
//         // ������ #1 �任���
//         SGTransformNodePtr node1 = SGTransformNode::create();
//         node->addChild(node1);
//         node1->setPosition(2.0, 0.0, 0.0);
//         node1->setScale(1.2, 1.2, 1.2);
//         node1->setOrientation(Radian(Math::PI / Real(6.0)), Vector3(0.0, 1.0, 0.0));
// 
//         {
//             // ������ #1 �ɼ�������
//             SGShapePtr shape = SGShape::create();
//             node1->addChild(shape);
// 
//             {
//                 // ������ #1 ����Ⱦ������
//                 SGBoxPtr box = SGBox::create("");
//                 shape->addChild(box);
//             }
//         }
// 
//         // ������ #2 �任���
//         SGTransformNodePtr node2 = SGTransformNode::create();
//         node->addChild(node2);
//         node2->setPosition(-1.0, 0.0, 0.0);
// 
//         {
//             // ������ #2 �ɼ�������
//             SGShapePtr shape = SGShape::create();
//             node2->addChild(shape);
// 
//             {
//                 // ������ #2 ����Ⱦ������
//                 SGBoxPtr box = SGBox::create("");
//                 shape->addChild(box);
//             }
//         }
// 
//         // ���� #1 �任���
//         SGTransformNodePtr node3 = SGTransformNode::create();
//         node->addChild(node3);
//         node3->setPosition(-4.0, 0.0, 0.0);
// 
//         {
//             // ���� #1 �ɼ�������
//             SGShapePtr shape = SGShape::create();
//             node3->addChild(shape);
// 
//             {
//                 // ���� #1 ����Ⱦ������
//                 SGSpherePtr sphere = SGSphere::create("");
//                 shape->addChild(sphere);
//             }
//         }
//     }
// 
//     // ���� #2 �任���
//     node = SGTransformNode::create();
//     root->addChild(node);
//     node->setPosition(-10.0, 0.0, 0.0);
// 
//     {
//         // ���� #2 �ɼ�������
//         SGShapePtr shape = SGShape::create();
//         node->addChild(shape);
// 
//         {
//             // ���� #2 ����Ⱦ������
//             SGSpherePtr sphere = SGSphere::create("");
//             shape->addChild(sphere);
//         }
//     }

    // ģ�� #1 �任���
    node = SGTransformNode::create();
    root->addChild(node);
    node->setPosition(0.0, 0.0, 0.0);
//     node->setOrientation(Radian(-Math::PI*0.5), Vector3::UNIT_X);
//     node->setScale(10.0f, 10.0f, 10.0f);

    {
        // ģ�� #1 �ɼ�������
//         SGModelPtr model = SGModel::create("dahu01.tmt");
//         SGModelPtr model = SGModel::create("knight.tmt");
        SGModelPtr model = SGModel::create("skeleton.tmt");
//         model->setRenderMode(SGModel::E_RENDER_SKELETON);
        node->addChild(model);
//         model->runAction("Take 001", false);
//         SGShapePtr shape = SGShape::create();
//         node->addChild(shape);
// 
//         SGBoxPtr box = SGBox::create("");
//         shape->addChild(box);
    }

    return true;
}

void TextureApp::applicationDidEnterBackground()
{

}

void TextureApp::applicationWillEnterForeground()
{

}

void TextureApp::applicationWillTerminate()
{

}
