

#ifndef __T3D_MODEL_DATA_H__
#define __T3D_MODEL_DATA_H__


#include "Misc/T3DObject.h"
#include "T3DPrerequisitesInternal.h"
#include "T3DTypedefInternal.h"

#include "T3DMeshData.h"
#include "T3DNodeData.h"
#include "T3DBoneData.h"
#include "T3DActionData.h"


namespace Tiny3D
{
    /**
     * @brief ģ������
     */
    class ModelData : public Object
    {
    public:
        typedef std::vector<MeshDataPtr>        MeshDataList;
        typedef MeshDataList::iterator          MeshDataListItr;
        typedef MeshDataList::const_iterator    MeshDataListConstItr;

        typedef std::vector<BoneDataPtr>        BoneDataList;
        typedef BoneDataList::iterator          BoneDataListItr;
        typedef BoneDataList::const_iterator    BoneDataListConstItr;

        typedef std::vector<NodeDataPtr>        NodeDataList;
        typedef NodeDataList::iterator          NodeDataListItr;
        typedef NodeDataList::const_iterator    NodeDataListConstItr;

        typedef std::map<String, ObjectPtr>     AnimationData;
        typedef AnimationData::iterator         AnimationItr;
        typedef AnimationData::const_iterator   AnimationConstItr;
        typedef std::pair<String, ObjectPtr>    AnimationValue;

        static ModelDataPtr create();

        bool            mIsVertexShared;        /// ���������Ƿ����㻺��
        MeshDataList    mMeshes;                /// ���������б�
        BoneDataList    mBones;                 /// ���������б�
        AnimationData   mAnimations;            /// ���������б�
        NodeDataList    mNodes;                 /// �任��������б�

    protected:
        ModelData();

    protected:
        ModelData(const ModelData &rkOther);
        ModelData &operator =(const ModelData &rkOther);
    };
}


#endif  /*__T3D_MODEL_DATA_H__*/
