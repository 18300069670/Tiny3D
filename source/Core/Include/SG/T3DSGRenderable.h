

#ifndef __T3D_SG_RENDERABLE_H__
#define __T3D_SG_RENDERABLE_H__


#include "SG//T3DSGNode.h"
#include "Resource/T3DMaterial.h"
#include "Misc/T3DIndexData.h"
#include "Misc/T3DVertexData.h"
#include "Render/T3DRenderer.h"


namespace Tiny3D
{
    class T3D_ENGINE_API SGRenderable : public SGNode
    {
    protected:
        SGRenderable(uint32_t unID = E_NID_AUTOMATIC);

    public:
        /**
         * @brief Destructor
         */
        virtual ~SGRenderable();

        /**
         * @brief ������Ⱦ���ʶ���
         * @note ���п���Ⱦ��������Ҫ��д���ӿ��Է��ض�Ӧ����Ⱦ���ʶ���
         */
        virtual MaterialPtr getMaterial() const = 0;

        /**
         * @brief ���ص�ǰ��Ⱦ��������仯����
         */
        virtual const Matrix4 &getWorldMatrix() const;

        /**
         * @brief ������ȾԪ����
         * @see Renderer::PrimitiveType
         */
        virtual Renderer::PrimitiveType getPrimitiveType() const = 0;

        /**
         * @brief ���ض������ݶ���
         */
        virtual VertexDataPtr getVertexData() const = 0;

        /**
         * @brief �����������ݶ���
         */
        virtual IndexDataPtr getIndexData() const = 0;

        /**
         * @brief �Ƿ�ʹ�ö�������
         */
        virtual bool isIndicesUsed() const = 0;
    };
}


#endif  /*__T3D_SG_RENDERABLE_H__*/

