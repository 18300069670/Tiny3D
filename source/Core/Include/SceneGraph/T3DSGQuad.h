

#ifndef __T3D_SG_QUAD_H__
#define __T3D_SG_QUAD_H__


#include "SceneGraph/T3DSGRenderable.h"


namespace Tiny3D
{
    class T3D_ENGINE_API SGQuad : public SGRenderable
    {
    public:
        static SGQuadPtr create(uint32_t uID = E_NID_AUTOMATIC);

        virtual ~SGQuad();

        virtual Type getNodeType() const override;

    protected:
        SGQuad(uint32_t uID = E_NID_AUTOMATIC);

        virtual void frustumCulling(const BoundPtr &bound, const RenderQueuePtr &queue) override;

        virtual NodePtr clone() const override;

        virtual void cloneProperties(const NodePtr &node) const override;

        /**
        * @brief ������Ⱦ���ʶ���
        * @note ���п���Ⱦ��������Ҫ��д���ӿ��Է��ض�Ӧ����Ⱦ���ʶ���
        */
        virtual MaterialPtr getMaterial() const override;

        /**
        * @brief ������ȾԪ����
        * @see Renderer::PrimitiveType
        */
        virtual Renderer::PrimitiveType getPrimitiveType() const override;

        /**
        * @brief ���ض������ݶ���
        */
        virtual VertexDataPtr getVertexData() const override;

        /**
        * @brief �����������ݶ���
        */
        virtual IndexDataPtr getIndexData() const override;

        /**
        * @brief �Ƿ�ʹ�ö�������
        */
        virtual bool isIndicesUsed() const override;

    protected:
        VertexDataPtr   mVertexData;
    };
}


#endif  /*__T3D_SG_QUAD_H__*/
