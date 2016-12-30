

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
        bool processFbxNode(FbxNode *pFbxNode, Node *pParent);
        bool processFbxAnimation(FbxNode *pFbxNode, Model *pModel);

        bool processFbxMesh(FbxNode *pFbxNode, Node *pParent, Node *&pNode);
        bool processFbxSkin(FbxNode *pFbxNode, Node *pParent, Mesh *pMesh);
        bool processFbxSkeleton(FbxNode *pFbxNode, Node *pParent, Model *pModel);
        bool processFbxCamera(FbxNode *pFbxNode, Node *pParent, Node *&pNewNode);
        bool processFbxLight(FbxNode *pFbxNode, Node *pParent, Node *&pNewNode);
        bool processFbxMaterial(FbxNode *pFbxNode, Node *pParent);
        
        bool computeBoundingBox(Mesh *pMesh);
        bool computeBoundingSphere(Model *pModel, Mesh *pMesh);
        bool computeAlignAxisBoundingBox(Model *pModel, Mesh *pMesh);

        bool putVertexAttribute(Mesh *pMesh, bool bHasAttributes, const VertexAttribute &rkSource, const VertexAttribute &rkOther);
        bool processVertexAttribute(FbxMesh *pFbxMesh, Mesh *pMesh);
//         bool readPosition(FbxMesh *pFbxMesh, int nControlPointIdx, FbxVector3 &pos);
        bool readPosition(FbxMesh *pFbxMesh, int nControlPointIdx, Vector3 &pos);
//         bool readColor(FbxMesh *pFbxMesh, int nControlPointIdx, int nVertexIndex, int nLayer, FbxVector4 &color);
        bool readColor(FbxMesh *pFbxMesh, int nControlPointIdx, int nVertexIndex, int nLayer, Vector4 &color);
//         bool readUV(FbxMesh *pFbxMesh, int nControlPointIdx, int nUVIndex, int nLayer, FbxVector2 &uv);
        bool readUV(FbxMesh *pFbxMesh, int nControlPointIdx, int nUVIndex, int nLayer, Vector2 &uv);
//         bool readNormal(FbxMesh *pFbxMesh, int nControlPointIdx, int nVertexIndex, int nLayer, FbxVector3 &normal);
//         bool readTangent(FbxMesh *pFbxMesh, int nControlPointIdx, int nVertexIndex, int nLayer, FbxVector3 &tangent);
//         bool readBinormal(FbxMesh *pFbxMesh, int nControlPointIdx, int nVertexIndex, int nLayer, FbxVector3 &binormal);
        bool readNormal(FbxMesh *pFbxMesh, int nControlPointIdx, int nVertexIndex, int nLayer, Vector3 &normal);
        bool readTangent(FbxMesh *pFbxMesh, int nControlPointIdx, int nVertexIndex, int nLayer, Vector3 &tangent);
        bool readBinormal(FbxMesh *pFbxMesh, int nControlPointIdx, int nVertexIndex, int nLayer, Vector3 &binormal);
        bool readMaterial(FbxMesh *pFbxMesh, int nTriangleIndex, int &nMaterialIndex);

        bool optimizeMesh(Node *pRoot);

        // ����ĳ��Cluster��link node���ݻ�ȡ�������ڵ�
        bool searchSkeletonRoot(FbxNode *pFbxNode, FbxNode *&pFbxRootNode);
        // ���ݹ������ڵ㣬�������Ƿ��Ѿ����ɹ���Ӧ�Ĺ�������
        bool searchSkeleton(FbxNode *pFbxNode);

        // ����ģ�����������Ƿ������ڱ�model�´����������ڵ�
        bool searchAnimation(const String &name, Node *pNode, Animation *&pAnim);
        // ���ݶ������ƣ������Ƿ��Ѿ����ڸö���
        bool searchAction(const String &name, Animation *pAnim, Action *&pAction);

        // ���¶����еĹ��������͹���Ȩ��ֵ
        bool updateVertexBlendIndexAndWeight(Mesh *pMesh, int nCtrlPointIdx, int nBlendIndex, double fBlendWeight);

        // ��ӹ���Ȩ�غ͹�������������������
        void updateVertexBlendAttributes(Mesh *pMesh);

        // ��FBX������wrapģʽת�����ַ���
        String FbxWrapModeToString(FbxTexture::EWrapMode eWrapMode) const;

        bool searchMaterial(const String &name, Material *&pMaterial);

        struct SceneInfo
        {
            void    *mRoot;
            String  mName;
        };

        typedef std::map<FbxNode*, Skeleton*>       Skeletons;
        typedef Skeletons::iterator                 SkeletonsItr;
        typedef Skeletons::const_iterator           SkeletonsConstItr;
        typedef std::pair<FbxNode*, Skeleton*>      SkeletonsValue;

        typedef std::list<SceneInfo>                SceneList;
        typedef SceneList::iterator                 SceneListItr;
        typedef SceneList::const_iterator           SceneListConstItr;

        Serializer  *mImporter;
        Serializer  *mExporter;

        void        *mSrcData;
//         void        *mDstData;

        Node        *mCurScene;         // ��ǰ�����ڵ㣬����split mode�ǻ�仯�ģ�����merge��shared vertex��Զֻ��һ�������
        Node        *mCurModel;         // ��ǰģ�ͽڵ�
        Node        *mCurMesh;          // ���ڹ�����ģʽ�ĵ�ǰ����ڵ�
        Node        *mCurSkin;          // ��ǰ��Ƥ�ڵ�
        Node        *mCurSkeleton;      // �����ڵ�
        Node        *mCurAnimation;     // �����ڵ�
        Node        *mCurMaterials;     // ֻ����merge��shared vertex�ļ���ʽ��
        Node        *mCurBound;         // ��ǰ����ײ����������spliteģʽ��mergeģʽ������shared vertexģʽ������modelֻ��һ��bound

        SceneList   mSceneList;

        Skeletons   mSkeletons;
        bool        mHasSkeleton;
        bool        mHasVertexBlending;
        bool        mHasAnimation;

#ifdef _DEBUG
        int         mTabCount;
#endif
    };
}


#endif  /*__MCONV_FBX_CONVERTER_H__*/
