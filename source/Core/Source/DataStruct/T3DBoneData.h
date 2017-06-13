

#ifndef __T3D_BONE_DATA_H__
#define __T3D_BONE_DATA_H__


#include "T3DPrerequisitesInternal.h"
#include "T3DTypedefInternal.h"
#include "T3DNodeData.h"


namespace Tiny3D
{
    /**
     * @brief ��������
     */
    class BoneData : public NodeData
    {
    public:
        static BoneDataPtr create(const String &name);

        Matrix4     mOffsetMatrix;          /// ����ƫ�ƾ���
        bool        mIsMatrixDirty;         /// �Ƿ�Ҫ���¼���ƫ�ƾ���

    protected:
        BoneData(const String &name);

    private:
        BoneData(const BoneData &rkOther);
        BoneData &operator =(const BoneData &rkOther);
    };
}


#endif  /*__T3D_BONE_DATA_H__*/
