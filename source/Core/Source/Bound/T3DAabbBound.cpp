

#include "Bound/T3DSphereBound.h"
#include "Bound/T3DAabbBound.h"
#include "Bound/T3DObbBound.h"
#include "Bound/T3DFrustumBound.h"
#include "T3DMath.h"
#include "SG/Node/T3DSGNode.h"
#include "SG/Renderable/T3DSGBox.h"
#include "T3DTransform.h"


namespace Tiny3D
{
    AabbBoundPtr AabbBound::create(uint32_t unID, SGNode *node)
    {
        AabbBoundPtr bound = new AabbBound(unID, node);
        bound->release();
        return bound;
    }

    AabbBound::AabbBound(uint32_t unID, SGNode *node)
        : Bound(unID, node)
    {

    }

    AabbBound::~AabbBound()
    {

    }

    void AabbBound::setParam(Real minX, Real maxX, Real minY, Real maxY, Real minZ, Real maxZ)
    {
        mOriginalAabb.setParam(Vector3(minX, minY, minZ), Vector3(maxX, maxY, maxZ));
    }

    Bound::Type AabbBound::getType() const
    {
        return E_BT_AABB;
    }

    SGRenderablePtr AabbBound::getRenderable()
    {
        return mRenderable;
    }

    BoundPtr AabbBound::clone() const
    {
        AabbBoundPtr bound = new AabbBound(getID(), getNode());
        cloneProperties(bound);
        return bound;
    }

    void AabbBound::cloneProperties(const BoundPtr &bound) const
    {
        Bound::cloneProperties(bound);

        const AabbBoundPtr &aabbBound = (const AabbBoundPtr &)bound;

        aabbBound->mAabb = mAabb;
        aabbBound->mOriginalAabb = mOriginalAabb;
        aabbBound->mRenderable = smart_pointer_cast<SGBox>(mRenderable->clone());
    }

    bool AabbBound::testSphere(const SphereBoundPtr &bound) const
    {
        return Math::intersects(bound->getOriginalSphere(), mAabb);
    }

    bool AabbBound::testAabb(const AabbBoundPtr &bound) const
    {
        return Math::intersects(mAabb, bound->getAlignAxisBox());
    }

    bool AabbBound::testObb(const ObbBoundPtr &bound) const
    {
        return Math::intersects(mAabb, bound->getObb());
    }

    bool AabbBound::testFrustum(const FrustumBoundPtr &bound) const
    {
        return Math::intersects(mAabb, bound->getFrustum());
    }

    void AabbBound::updateBound(const Transform &transform)
    {
        // ���ﲻ�ô�ͳ�ı任8�����㣬Ȼ������Ƚϻ�ȡ���x,y,z����������AABB
        // ����ʹ�ÿ��ٱ任�ķ��������پ���任�����Ŀ�����ԭ�����£�
        // 
        // ��ײ��8�����������һ��ΪP���任��һ��ΪP'���任����ΪM����ɵã�
        //      P' = M * P
        // ����
        //      P' = (x' y' z' 1)
        //
        //      P = (x y z 1)
        //
        //          | m00 m01 m02 tx|
        //      M = | m10 m11 m12 ty|
        //          | m20 m21 m22 tz|
        //          | 0   0   0   1 |
        // ��
        //      p'x' = px * m00 + py * m01 + pz * m02 + tx
        //      p'y' = px * m10 + py * m11 + pz * m12 + ty
        //      p'z' = px * m20 + py * m21 + pz * m22 + tz
        // ����ֻҪ��������p'x'��p'y'��p'z'�Ϳ��Եó�������Сֵ�ˡ�
        // �������
        //      �� m00 > 0ʱ����px = min_xʱ����px * m00��С��
        //      �� m00 < 0ʱ����px = max_xʱ����px * m00��С
        //  ͬ�����Ը�����Сֵ���㷽���������ֵ������������ƣ�����p'y'��p'z'

        const Vector3 &translate = transform.getTranslate();
        const Matrix4 &M = transform.getAffineMatrix();

        Vector3 vMin = translate;
        Vector3 vMax = translate;

        // Calculate min x & max x
        if (M[0][0] > Real(0.0))
        {
            vMin.x() += M[0][0] * mOriginalAabb.getMinX();
            vMax.x() += M[0][0] * mOriginalAabb.getMaxX();
        }
        else
        {
            vMin.x() += M[0][0] * mOriginalAabb.getMaxX();
            vMax.x() += M[0][0] * mOriginalAabb.getMinX();
        }

        if (M[0][1] > Real(0.0))
        {
            vMin.x() += M[0][1] * mOriginalAabb.getMinY();
            vMax.x() += M[0][1] * mOriginalAabb.getMaxY();
        }
        else
        {
            vMin.x() += M[0][1] * mOriginalAabb.getMaxY();
            vMax.x() += M[0][1] * mOriginalAabb.getMinY();
        }

        if (M[0][2] > Real(0.0))
        {
            vMin.x() += M[0][2] * mOriginalAabb.getMinZ();
            vMax.x() += M[0][2] * mOriginalAabb.getMaxZ();
        }
        else
        {
            vMin.x() += M[0][2] * mOriginalAabb.getMaxZ();
            vMax.x() += M[0][2] * mOriginalAabb.getMinZ();
        }

        // Calculate min y & max y
        if (M[1][0] > Real(0.0))
        {
            vMin.y() += M[1][0] * mOriginalAabb.getMinX();
            vMax.y() += M[1][0] * mOriginalAabb.getMaxX();
        }
        else
        {
            vMin.y() += M[1][0] * mOriginalAabb.getMaxX();
            vMax.y() += M[1][0] * mOriginalAabb.getMinX();
        }

        if (M[1][1] > Real(0.0))
        {
            vMin.y() += M[1][1] * mOriginalAabb.getMinY();
            vMax.y() += M[1][1] * mOriginalAabb.getMaxY();
        }
        else
        {
            vMin.y() += M[1][1] * mOriginalAabb.getMaxY();
            vMax.y() += M[1][1] * mOriginalAabb.getMinY();
        }

        if (M[1][2] > Real(0.0))
        {
            vMin.y() += M[1][2] * mOriginalAabb.getMinZ();
            vMax.y() += M[1][2] * mOriginalAabb.getMaxZ();
        }
        else
        {
            vMin.y() += M[1][2] * mOriginalAabb.getMaxZ();
            vMax.y() += M[1][2] * mOriginalAabb.getMinZ();
        }

        // Calculate min z & max z
        if (M[2][0] > Real(0.0))
        {
            vMin.z() += M[2][0] * mOriginalAabb.getMinX();
            vMax.z() += M[2][0] * mOriginalAabb.getMaxX();
        }
        else
        {
            vMin.z() += M[2][0] * mOriginalAabb.getMaxX();
            vMax.z() += M[2][0] * mOriginalAabb.getMinX();
        }

        if (M[2][1] > Real(0.0))
        {
            vMin.z() += M[2][1] * mOriginalAabb.getMinY();
            vMax.z() += M[2][1] * mOriginalAabb.getMaxY();
        }
        else
        {
            vMin.z() += M[2][1] * mOriginalAabb.getMaxY();
            vMax.z() += M[2][1] * mOriginalAabb.getMinY();
        }

        if (M[2][2] > Real(0.0))
        {
            vMin.z() += M[2][2] * mOriginalAabb.getMinZ();
            vMax.z() += M[2][2] * mOriginalAabb.getMaxZ();
        }
        else
        {
            vMin.z() += M[2][2] * mOriginalAabb.getMaxZ();
            vMax.z() += M[2][2] * mOriginalAabb.getMinZ();
        }

        mAabb.setParam(vMin, vMax);
    }
}

