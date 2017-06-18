

#ifndef __MCONV_FBX_CONVERTER_H__
#define __MCONV_FBX_CONVERTER_H__


#include "mconv_converter.h"


namespace mconv
{
    class Serializer;
    class Node;
    class Mesh;
    class Model;
    class Skeleton;
    class Bone;
    class Animation;
    class Action;
    class Material;
    class VertexAttribute;
    class VertexBuffer;
    class VertexBuffers;
    class Transform;
    class SubMesh;

    class FBXConverter : public ConverterImpl
    {
    public:
        FBXConverter(const Settings &settings);
        virtual ~FBXConverter();

    protected:
        virtual bool importScene() override;
        virtual bool exportScene() override;
        virtual bool convertToT3D() override;
        virtual void cleanup() override;

        void convertMatrix(const FbxAMatrix &fbxMat, Matrix4 &m);

        bool processFbxScene(FbxScene *pFbxScene, Node *pRoot);
        bool processFbxNode(FbxNode *pFbxNode, Node *pTransformNode, Node *pParent);
        bool processFbxAnimation(FbxNode *pFbxNode, Model *pModel);

        bool processFbxMesh(FbxNode *pFbxNode, Node *pParent, Transform *pTransform, Node *&pNode);
        bool processFbxSkin(FbxNode *pFbxNode, Node *pParent, Mesh *pMesh);
        bool processFbxSkeleton(FbxNode *pFbxNode, Node *pParent, Model *pModel, Node *&pNode);
        bool processFbxCamera(FbxNode *pFbxNode, Node *pParent, Node *&pNewNode);
        bool processFbxLight(FbxNode *pFbxNode, Node *pParent, Node *&pNewNode);
        bool processFbxMaterial(FbxNode *pFbxNode, Node *pParent);
        
        bool processBoundingBox(Node *pRoot);
        bool computeBoundingBox(SubMesh *pSubMesh);
        bool computeBoundingSphere(SubMesh *pSubMesh);
        bool computeAlignAxisBoundingBox(SubMesh *pSubMesh);
//         bool computeBoundingBox(Mesh *pMesh);
//         bool computeBoundingSphere(Model *pModel, Mesh *pMesh);
//         bool computeAlignAxisBoundingBox(Model *pModel, Mesh *pMesh);

        bool searchVertexBuffer(Mesh *pMesh, VertexBuffer *&pVertexBuffer);

        bool putVertexAttribute(VertexBuffer *pVertexBuffer, bool bHasAttributes, const VertexAttribute &rkSource, const VertexAttribute &rkOther);
        bool processVertexAttribute(FbxMesh *pFbxMesh, VertexBuffer *pVertexBuffer);
        bool readPosition(FbxMesh *pFbxMesh, int nControlPointIdx, Vector3 &pos);
        bool readColor(FbxMesh *pFbxMesh, int nControlPointIdx, int nVertexIndex, int nLayer, Vector4 &color);
        bool readUV(FbxMesh *pFbxMesh, int nControlPointIdx, int nUVIndex, int nLayer, Vector2 &uv);
        bool readNormal(FbxMesh *pFbxMesh, int nControlPointIdx, int nVertexIndex, int nLayer, Vector3 &normal);
        bool readTangent(FbxMesh *pFbxMesh, int nControlPointIdx, int nVertexIndex, int nLayer, Vector3 &tangent);
        bool readBinormal(FbxMesh *pFbxMesh, int nControlPointIdx, int nVertexIndex, int nLayer, Vector3 &binormal);
        bool readMaterial(FbxMesh *pFbxMesh, int nTriangleIndex, int &nMaterialIndex);

        bool optimizeMesh(Node *pNode);

        bool updateSkinInfo(FbxNode *pFbxNode, size_t boneIdx, const Matrix4 &m);
        bool updateBoneMatrix(FbxNode *pFbxNode, const Matrix4 &m, Node *pParent, Node *&pNode);
        bool fixBoneIndex(Bone *pBone);

//         // ����ĳ��Cluster��link node���ݻ�ȡ�������ڵ�
//         bool searchSkeletonRoot(FbxNode *pFbxNode, FbxNode *&pFbxRootNode);
//         // ���ݹ������ڵ㣬�������Ƿ��Ѿ����ɹ���Ӧ�Ĺ�������
//         bool searchSkeleton(FbxNode *pFbxNode);

        // ����ģ�����������Ƿ������ڱ�model�´����������ڵ�
        bool searchAnimation(const String &name, Node *pNode, Animation *&pAnim);
        // ���ݶ������ƣ������Ƿ��Ѿ����ڸö���
        bool searchAction(const String &name, Animation *pAnim, Action *&pAction);

        // ���¶����еĹ��������͹���Ȩ��ֵ
        bool updateVertexBlendIndexAndWeight(Mesh *pMesh, int nCtrlPointIdx, int nBlendIndex, double fBlendWeight);
        bool updateVertexBlendIndexAndWeight(VertexBuffer *pVB, int nCtrlPointIndex, int nBlendIndex, double fBlendWeight);
        void putVertexBlendAndWeightAttributes(VertexBuffer *pVB);

        // ��ӹ���Ȩ�غ͹�������������������
        void updateVertexBlendAttributes(Mesh *pMesh);

        // ��FBX������wrapģʽת�����ַ���
        String FbxWrapModeToString(FbxTexture::EWrapMode eWrapMode) const;

        bool searchMaterial(const String &name, Material *&pMaterial);

        String getFileName(const String &strPath);
        
        typedef std::map<FbxNode*, Skeleton*>       Skeletons;
        typedef Skeletons::iterator                 SkeletonsItr;
        typedef Skeletons::const_iterator           SkeletonsConstItr;
        typedef std::pair<FbxNode*, Skeleton*>      SkeletonsValue;

        typedef std::map<FbxNode*, Bone*>           Bones;
        typedef Bones::iterator                     BonesItr;
        typedef Bones::const_iterator               BonesConstItr;
        typedef std::pair<FbxNode*, Bone*>          BonesValue;

        Serializer  *mImporter;
        Serializer  *mExporter;

        void        *mSrcData;
        void        *mDstData;

        Node        *mCurScene;         // ��ǰ�����ڵ㣬����split mode�ǻ�仯�ģ�����merge��shared vertex��Զֻ��һ�������
        Node        *mCurModel;         // ��ǰģ�ͽڵ�
        Node        *mCurMesh;          // ���ڹ�����ģʽ�ĵ�ǰ����ڵ�
        Node        *mCurSubMeshes;     // ���ڹ�����ģʽ�ĵ�ǰ�����񼯺Ͻڵ�
        Node        *mCurSkeleton;      // �����ڵ�
        Node        *mCurAnimation;     // �����ڵ�
        Node        *mCurMaterials;     // ֻ����merge��shared vertex�ļ���ʽ��
//         Node        *mCurBound;         // ��ǰ����ײ����������spliteģʽ��mergeģʽ������shared vertexģʽ������modelֻ��һ��bound
        Node        *mRootTransform;    // �����任�����
        Node        *mCurSkin;          // ��ǰ��Ƥ��Ϣ���

        Bones       mBones;

        uint16_t    mMaxBoneIdx;        // �����������ֵ
        uint16_t    mBoneIdx;           // ��Ƥ��Ϣ�Ĺ�������

//         Skeletons   mSkeletons;
        bool        mHasSkeleton;
        bool        mHasVertexBlending;
        bool        mHasAnimation;

        int         mBoneCount;         // ������¼������������Ҫ���ڲ�֪��Ϊ��offset matrix��skeleton hiarachy����Ĺ������в���
    };
}


#endif  /*__MCONV_FBX_CONVERTER_H__*/
