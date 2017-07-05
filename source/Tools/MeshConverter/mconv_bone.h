

#ifndef __MCONV_BONE_H__
#define __MCONV_BONE_H__


#include "mconv_node.h"


namespace mconv
{
    class Bone : public Node
    {
    public:
        Bone(const String &ID)
            : Node(ID)
            , mBoneIndex(0xFFFF)
        {

        }

        virtual ~Bone()
        {

        }

        void setID(const String &ID)
        {
            mID = ID;
        }

        virtual Type getNodeType() const override
        {
            return E_TYPE_BONE;
        }

        Matrix4     mLocalTransform;
        Matrix4     mOffsetMatrix;
        uint16_t    mBoneIndex;

        Matrix4     mKeyframeMatrix;    /// ר�Ÿ�ogre������������ؼ�֡���Ա��ر任�õ�
    };
}


#endif
