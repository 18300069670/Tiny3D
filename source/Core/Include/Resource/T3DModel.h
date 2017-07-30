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
