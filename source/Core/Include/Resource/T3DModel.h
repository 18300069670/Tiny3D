

#ifndef __T3D_MODEL_H__
#define __T3D_MODEL_H__


#include "Resource/T3DResource.h"
#include "Render/T3DHardwareVertexBuffer.h"


namespace Tiny3D
{
    class T3D_ENGINE_API Model : public Resource
    {
        friend class XMLModelSerializer;
        friend class BinModelSerializer;

    public:
        enum FileType
        {
            E_FILETYPE_UNKNOWN = 0,     /// δ֪ģ���ļ���ʽ
            E_FILETYPE_T3B,             /// ������ģ���ļ���ʽ
            E_FILETYPE_T3T              /// XMLģ���ļ���ʽ
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
         * @brief ��ȡģ�������������.
         */
        const ObjectPtr &getModelData() const
        {
            return mModelData;
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

    protected:
        ObjectPtr           mModelData;         /// ģ���������
    };
}

#endif  /*__T3D_MODEL_H__*/
