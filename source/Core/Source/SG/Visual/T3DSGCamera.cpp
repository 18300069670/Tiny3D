

#include "SG/Visual/T3DSGCamera.h"
#include "SG/Node/T3DSGTransformNode.h"
#include "SG/Renderable/T3DSGRenderable.h"
#include "Math/T3DMath.h"
#include "Math/T3DMatrix4.h"
#include "Misc/T3DEntrance.h"
#include "Render/T3DRenderer.h"
#include "Math/T3DPlane.h"
#include "Math/T3DFrustum.h"
#include "Bound/T3DFrustumBound.h"


namespace Tiny3D
{
    SGCameraPtr SGCamera::create(uint32_t unID /* = E_NID_AUTOMATIC */)
    {
        SGCameraPtr camera = new SGCamera(unID);
        camera->release();
        return camera;
    }

    SGCamera::SGCamera(uint32_t unID /* = E_NID_AUTOMATIC */)
        : SGVisual(unID)
        , mFovY(Real(45.0))
        , mFarDistance(Real(2000.0))
        , mNearDistance(Real(1.0))
        , mAspectRatio(Real(4.0)/Real(3.0))
        , mProjType(E_PT_PERSPECTIVE)
        , mIsFrustumDirty(false)
    {
        mBound = FrustumBound::create(unID, this);
    }

    SGCamera::~SGCamera()
    {

    }

    SGNode::Type SGCamera::getNodeType() const
    {
        return E_NT_CAMERA;
    }

    SGNodePtr SGCamera::clone() const
    {
        SGCamera *node = new SGCamera();
        SGNodePtr ptr(node);
        node->release();
        cloneProperties(node);
        return ptr;
    }

    void SGCamera::cloneProperties(const SGNodePtr &node) const
    {
        SGVisual::cloneProperties(node);

        const SGCameraPtr &newNode = (const SGCameraPtr &)node;
        newNode->mFovY = mFovY;
        newNode->mFarDistance = mFarDistance;
        newNode->mNearDistance = mNearDistance;
        newNode->mAspectRatio = mAspectRatio;
        newNode->mProjType = mProjType;
        newNode->mViewMatrix = mViewMatrix;
        newNode->mProjMatrix = mProjMatrix;
    }

    void SGCamera::addChild(const SGNodePtr &child)
    {
        // Can't add any type node for child node.
        T3D_ASSERT(0);
    }

    void SGCamera::updateTransform()
    {
        bool isViewDirty = mIsViewDirty;
        bool isFrustumDirty = mIsFrustumDirty;

        getViewMatrix();
        getProjectionMatrix();

        // ����Ƚ����⣬ֱ���ȸ��������frustum���������������޷���frustum culling
        if (isViewDirty || isFrustumDirty)
        {
            updateBound();
        }

        SGVisual::updateTransform();
    }

    void SGCamera::setDirty(bool isDirty, bool recursive /* = false */)
    {
        SGVisual::setDirty(isDirty, recursive);
        mIsViewDirty = isDirty;
    }

    void SGCamera::renderScene(const ViewportPtr &viewport)
    {
        T3D_SCENE_MGR.renderScene(this, viewport);
    }

    const Matrix4 &SGCamera::getViewMatrix() const
    {
        if (mIsViewDirty)
        {
            // ��ͼ�����Ƶ���
            // ����C�������������任�ľ���T��ƽ�Ʊ任��R����ת�任��S�����ű任
            // �� C = T * R * S
            // �� C(-1) = (T * R * S) (-1) = S(-1) * R(-1) * T(-1)
            // 
            SGNode *parent = getParent();
            SGTransformNode *node = (SGTransformNode *)parent;
            T3D_ASSERT(node->getNodeType() == E_NT_TRANSFORM);

            const Transform &transform = node->getLocalToWorldTransform();
            // ��ת����
            Matrix4 R = transform.getOrientation();
            /// ��ת��������������������������������ת�þ���
            Matrix4 invertR = R.transpose();
            // ƽ�ƾ���
            Matrix4 invertT(false);
            invertT.makeTranslate(-transform.getTranslate());
            // ���ž���
            Matrix4 invertS(false);
            const Vector3 &scale = transform.getScale();
            invertS[0][0] = Real(1.0) / scale.x();
            invertS[1][1] = Real(1.0) / scale.y();
            invertS[2][2] = Real(1.0) / scale.z();

            mViewMatrix = invertS * invertR * invertT;

            Renderer *renderer = T3D_ENTRANCE.getActiveRenderer();
            renderer->setViewTransform(mViewMatrix);

            mIsViewDirty = false;
        }
        
        return mViewMatrix;
    }

    const Matrix4 &SGCamera::getProjectionMatrix() const
    {
        if (mIsFrustumDirty)
        {
            Renderer *renderer = T3D_ENTRANCE.getActiveRenderer();

            if (mProjType == E_PT_ORTHOGRAPHIC)
            {
                renderer->makeProjectionMatrix(mFovY, mAspectRatio, mNearDistance, mFarDistance, true, mProjMatrix);
            }
            else
            {
                renderer->makeProjectionMatrix(mFovY, mAspectRatio, mNearDistance, mFarDistance, false, mProjMatrix);
            }

            renderer->setProjectionTransform(mProjMatrix);

            mIsFrustumDirty = false;
        }

        return mProjMatrix;
    }

    void SGCamera::updateBound()
    {
        // ���ټ�������׶�����ü�ƽ��ԭ��
        //
        //  �����V'��ͶӰ�任��ĵ㣬V��ͶӰ�任ǰ�������ϵ�ĵ㣬M��ͶӰ�任������ɵã�
        //      V' = M * V
        //  ����
        //      V' = (x' y' z' w')
        //
        //      V = (x y z w), (w = 1)
        //
        //          | m00 m01 m02 m03 |
        //      M = | m10 m11 m12 m13 |
        //          | m20 m21 m22 m23 |
        //          | m30 m31 m32 m33 |
        //  ��
        //      | m00 m01 m02 m03 |   | x |   | x*m00 + y*m01 + z*m02 + w*m03 |   | V * row0 |
        //      | m10 m11 m12 m13 |   | y |   | x*m10 + y*m11 + z*m12 + w*m13 |   | V * row1 |
        //      | m20 m21 m22 m23 | * | z | = | x*m20 + y*m21 + z*m22 + w*m23 | = | V * row2 |
        //      | m30 m31 m32 m33 |   | w |   | x*m30 + y*m31 + z*m32 + w*m33 |   | V * row3 |
        //
        //  �����*����������rowi = (mi0 mi1 mi2 mi3)
        // 
        //  ����ת����V'����βü��ռ������ռ�ʵ���������Ѿ���һ�������ĺ��ӡ�
        //  ���V'��������ӿռ����任ǰ��V��Ҳ�����û�о����任�ĺ��ӿռ��
        //  ����Ҫ��һ��DX��OpenGL��������ΪͶӰ�ռ䲻һ����
        //
        //      1����DX�V'������ռ�����������Ĳ���ʽ����
        //          -w' < x' < w'
        //          -w' < y' < w'
        //            0 < z' < w'
        //
        Matrix4 M = mProjMatrix * mViewMatrix;

        Plane plane[Frustum::E_MAX_FACE];

        // Left
        plane[Frustum::E_FACE_LEFT][0] = M[3][0] + M[0][0];
        plane[Frustum::E_FACE_LEFT][1] = M[3][1] + M[0][1];
        plane[Frustum::E_FACE_LEFT][2] = M[3][2] + M[0][2];
        plane[Frustum::E_FACE_LEFT][3] = M[3][3] + M[0][3];
        plane[Frustum::E_FACE_LEFT].normalize();

        // Right
        plane[Frustum::E_FACE_RIGHT][0] = M[3][0] - M[0][0];
        plane[Frustum::E_FACE_RIGHT][1] = M[3][1] - M[0][1];
        plane[Frustum::E_FACE_RIGHT][2] = M[3][2] - M[0][2];
        plane[Frustum::E_FACE_RIGHT][3] = M[3][3] - M[0][3];
        plane[Frustum::E_FACE_RIGHT].normalize();

        // Bottom
        plane[Frustum::E_FACE_BOTTOM][0] = M[3][0] + M[1][0];
        plane[Frustum::E_FACE_BOTTOM][1] = M[3][1] + M[1][1];
        plane[Frustum::E_FACE_BOTTOM][2] = M[3][2] + M[1][2];
        plane[Frustum::E_FACE_BOTTOM][3] = M[3][3] + M[1][3];
        plane[Frustum::E_FACE_BOTTOM].normalize();

        // Top
        plane[Frustum::E_FACE_TOP][0] = M[3][0] - M[1][0];
        plane[Frustum::E_FACE_TOP][1] = M[3][1] - M[1][1];
        plane[Frustum::E_FACE_TOP][2] = M[3][2] - M[1][2];
        plane[Frustum::E_FACE_TOP][3] = M[3][3] - M[1][3];
        plane[Frustum::E_FACE_TOP].normalize();

        // Near
        plane[Frustum::E_FACE_NEAR][0] = M[3][0] + M[2][0];
        plane[Frustum::E_FACE_NEAR][1] = M[3][1] + M[2][1];
        plane[Frustum::E_FACE_NEAR][2] = M[3][2] + M[2][2];
        plane[Frustum::E_FACE_NEAR][3] = M[3][3] + M[2][3];
        plane[Frustum::E_FACE_NEAR].normalize();

        // Far
        plane[Frustum::E_FACE_FAR][0] = M[3][0] - M[2][0];
        plane[Frustum::E_FACE_FAR][1] = M[3][1] - M[2][1];
        plane[Frustum::E_FACE_FAR][2] = M[3][2] - M[2][2];
        plane[Frustum::E_FACE_FAR][3] = M[3][3] - M[2][3];
        plane[Frustum::E_FACE_FAR].normalize();

        FrustumBound *bound = ((FrustumBound *)(Bound *)mBound);
        bound->setParam(plane, Frustum::E_MAX_FACE);
    }
}
