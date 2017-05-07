

#ifndef __T3D_MODEL_H__
#define __T3D_MODEL_H__


#include "Resource/T3DResource.h"
#include "Render/T3DHardwareVertexBuffer.h"
#include "Render/T3DRenderer.h"


namespace tinyxml2
{
    class XMLElement;
}


namespace Tiny3D
{
    class T3D_ENGINE_API Model : public Resource
    {
    public:
        typedef std::vector<ObjectPtr>              GeometryDataList;
        typedef GeometryDataList::iterator          GeometryDataListItr;
        typedef GeometryDataList::const_iterator    GeometryDataListConstItr;

        typedef std::vector<ObjectPtr>              SkinDataList;
        typedef SkinDataList::iterator              SkinDataListItr;
        typedef SkinDataList::const_iterator        SkinDataListConstItr;

        typedef std::map<String, ObjectPtr>         AnimationData;
        typedef AnimationData::iterator             AnimationItr;
        typedef AnimationData::const_iterator       AnimationConstItr;
        typedef std::pair<String, ObjectPtr>        AnimationValue;

        enum FileType
        {
            E_FILETYPE_UNKNOWN = 0,     /// δ֪ģ���ļ���ʽ
            E_FILETYPE_TMB,             /// ������ģ���ļ���ʽ
            E_FILETYPE_TMT              /// XMLģ���ļ���ʽ
        };

        /**
         * @brief ����ģ�Ͷ���ʵ��.
         */
        static ModelPtr create(const String &name);

        /**
         * @brief Destructor
         */
        virtual ~Model();

        /**
         * @brief ��ȡ��Դ����ö�٣���Resource�̳������ķ���.
         */
        virtual Type getType() const override;

        /**
         * @brief ��ȡģ��ӵ�еļ����������б�.
         */
        const GeometryDataList &getGeometryDataList() const
        {
            return mGeometryData;
        }

        /**
         * @brief ��ȡģ�͵���Ƥ��Ϣ�����б�.
         */
        const SkinDataList &getSkinData() const
        {
            return mSkinData;
        }

        /**
         * @brief ��ȡ��������
         */
        const ObjectPtr &getSkeletonData() const
        {
            return mSkeletonData;
        }

        /**
         * @brief ��ȡ��������
         */
        const AnimationData &getAnimationData() const
        {
            return mAnimationData;
        }

        /**
         * @brief ģ�ͼ����������Ƿ��ö���ģʽ.
         */
        bool isSharedVertex() const
        {
            return mIsVertexShared;
        }

    protected:
        Model(const String &name);

        /**
         * @brief ����ģ����Դ����Resource�̳������ķ���.
         */
        virtual bool load() override;

        /**
         * @brief ж��ģ����Դ����Resource�̳������ķ���.
         */
        virtual void unload() override;
        
        /**
         * @brief ��¡һ��ģ����Դ������Ŀ�¡���������ģ��������ȫ������һ��.
         */
        virtual ResourcePtr clone() const override;

        /**
         * @brief ����ģ����չ������ȡ��Ӧ��ģ���ļ���ʽö��ֵ.
         */
        FileType parseFileType(const String &name) const;

        /**
         * @brief ��XML�ļ�����ģ����Դ.
         * @param [in] stream : ģ����Դ�����ڴ�����������
         * @return ���سɹ�������true�����򷵻�false.
         */
        bool loadFromXML(MemoryDataStream &stream);

        /**
         * @brief 
         */
        size_t parseVertexValue(const String &text, size_t &start, const VertexElement &attribute, void *value);
        size_t parseIndexValue(const String &text, size_t &start, bool is16bits, void *value);

        VertexElement::Semantic parseVertexSemantic(const String &name);
        VertexElement::Type parseVertexType(VertexElement::Semantic semantic, const String &name, size_t valueCount);
        Renderer::PrimitiveType parsePrimitiveType(const String &name);

        bool parseMesh(tinyxml2::XMLElement *pMeshElement);
        bool parseVertexBuffers(tinyxml2::XMLElement *pBuffersElement, void *attributes, void *buffers);
        bool parseVertexBuffer(tinyxml2::XMLElement *pBufferElement, void *attribute, void *buffer, size_t index);

        bool parseSubMeshes(tinyxml2::XMLElement *pMeshElement, void *attributes, void *buffers);
        bool parseSubMesh(tinyxml2::XMLElement *pSubMeshElement, void *attributes, void *buffers);

        bool parseSkin(tinyxml2::XMLElement *pSkinElement);
        bool parseBone(tinyxml2::XMLElement *pBoneElement, const ObjectPtr &bone);

        bool parseSkeleton(tinyxml2::XMLElement *pSkelElement);
        bool parseSkeleton(tinyxml2::XMLElement *pBoneElement, const ObjectPtr &parent);

        bool parseAnimation(tinyxml2::XMLElement *pAnimElement);
        bool parseAction(tinyxml2::XMLElement *pActionElement);
        bool parseKeyframe(tinyxml2::XMLElement *pKeyframeElement, const String &actionType, const String &boneName, size_t frameCount, const ObjectPtr &actionData);

        int32_t parseActionType(const String &type);

        bool loadFromBinary(DataStream &stream);

    protected:
        bool                mIsVertexShared;    /// �Ƿ���������
        GeometryDataList    mGeometryData;      /// ��Ⱦ��������
        SkinDataList        mSkinData;          /// ��Ƥ����
        ObjectPtr           mSkeletonData;      /// ��������
        AnimationData       mAnimationData;     /// ��������
    };
}

#endif  /*__T3D_MODEL_H__*/
