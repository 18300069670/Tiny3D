/*******************************************************************************
 * This file is part of Tiny3D (Tiny 3D Graphic Rendering Engine)
 * Copyright (C) 2015-2017  Answer Wong
 * For latest info, see https://github.com/asnwerear/Tiny3D
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ******************************************************************************/

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
