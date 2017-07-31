/***************************************************************************************************
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
 **************************************************************************************************/

#ifndef __T3D_HARDWARE_PIXEL_BUFFER_H__
#define __T3D_HARDWARE_PIXEL_BUFFER_H__


#include "Render/T3DHardwareBuffer.h"
#include "Misc/T3DCommon.h"


namespace Tiny3D
{
    class T3D_ENGINE_API HardwarePixelBuffer : public HardwareBuffer
    {
    public:
        /**
         * @brief ��������
         */
        virtual ~HardwarePixelBuffer();

        /**
         * @brief ��ȡӲ������������
         * @param [in] rect : Ҫ��ȡ���ݵ�����
         * @param [in] options : ��ȡ����ѡ��
         * @param [out] lockedPitch : �������������pitch
         * @return ����������Ӳ�����ݵ�ַ
         * @see enum LockOptions
         */
        virtual void *lock(const Rect &rect, LockOptions options, int32_t &lockedPitch);

        /**
         * @brief ��ȡӲ������������
         * @param [in] options : ��ȡ����ѡ��
         * @return ��������ָ���ַ
         * @note �����Ĭ�ϻ�ȡ�������ػ��������������
         * @see enum LockOptions
         */
        virtual void *lock(LockOptions options) override;

        /**
         * @brief ��ȡ����Ӳ����������ͬ��Ⱦ��ʵ�ֽӿ�
         * @param [in] rect : Ҫ��ȡ���ݵ�����
         * @param [in] options : ��ȡ����ѡ��
         * @param [out] lockedPitch : �������������pitch
         * @return ����������Ӳ�����ݵ�ַ
         * @see enum LockOptions
         */
        virtual void *lockImpl(const Rect &rect, LockOptions options, int32_t &lockedPitch) = 0;

        /**
         * @brief �������ݵ�����һ��HardwarePixelBuffer
         * @param [in] dst : Ŀ��pixel buffer
         * @param [in] dstRect : Ŀ����������Ĭ��Ϊnullptr��ʱ�򣬱�ʾ����Ŀ�����򣬻��Զ�����ƥ��Դ����
         * @param [in] srcRect : Դ��������Ĭ��Ϊnullptr��ʱ�򣬱�ʾ����Դ�������򣬻��Զ�����ƥ��Ŀ������
         * @return ���óɹ�����true�����򷵻�false
         * @note dstRect �� srcRect ��Ϊnullptr��ʱ�򣬻��Զ�����ƥ��Դ��Ŀ������
         */
        virtual bool copyTo(HardwarePixelBufferPtr dst, Rect *dstRect = nullptr, Rect *srcRect = nullptr);

        /**
         * @brief ����Դ�����image��ȡ���ݵ�Ŀ������
         * @param [in] image : Ҫ��ȡ��ͼ�����
         * @param [in] srcRect : Դ��������Ĭ��Ϊnullptr��ʱ�򣬱�ʾ����ԴĿ�����򣬻��Զ�����ƥ��Ŀ������
         * @param [in] dstRect : Ŀ����������Ĭ��Ϊnullptr��ʱ�򣬱�ʾ����Ŀ�����򣬻��Զ�����ƥ��Դ����
         * @return ���óɹ�����true�����򷵻�false
         * @note dstRect �� srcRect ��Ϊnullptr��ʱ�򣬻��Զ�����ƥ��Դ��Ŀ������
         */
        virtual bool readImage(const Image &image, Rect *srcRect = nullptr, Rect *dstRect = nullptr) = 0;

        /**
         * @brief ��ָ��Դ����Χ����д��image��Ŀ������
         * @param [in] image : Ҫд���ͼ�����
         * @param [in] dstRect : Ŀ������Ĭ��Ϊnullptr��ʱ�򣬱�ʾ����Ŀ�����򣬻��Զ�����ƥ��Դ����
         * @param [in] srcRect : Դ����Ĭ��Ϊnullptr��ʱ�򣬱�ʾ����ԴĿ�����򣬻��Զ�����ƥ��Ŀ������
         * @return ���óɹ�����true�����򷵻�false
         * @note dstRect �� srcRect ��Ϊnullptr��ʱ�򣬻��Զ�����ƥ��Դ��Ŀ������
         */
        virtual bool writeImage(Image &image, Rect *dstRect = nullptr, Rect *srcRect = nullptr) const = 0;

        /**
         * @brief �������ػ�����
         */
        uint32_t getWidth() const { return mWidth; }

        /**
         * @brief �������ػ���߶�
         */
        uint32_t getHeight() const { return mHeight; }

        /**
         * @brief ��ȡ���ػ����pitch
         */
        size_t getPitch() const { return mPitch; }

        /**
         * @brief ��ȡ���ػ�������ظ�ʽ
         */
        PixelFormat getFormat() const { return mFormat;}

    protected:
        /**
         * @brief ���캯��
         * @param [in] width : ���ػ��������
         * @param [in] height : ���ػ������߶�
         * @param [in] format : ���ػ�������ʽ
         * @param [in] usage : ��������;
         * @param [in] useSystemMemory : �Ƿ�ʹ��ϵͳ�ڴ�
         * @param [in] useShadowBuffer : �Ƿ�ʹ��ϵͳ�ڴ����GPU�Դ��д����
         */
        HardwarePixelBuffer(uint32_t width, uint32_t height, PixelFormat format,
            Usage usage, bool useSystemMemory, bool useShadowBuffer);

        int32_t getBPP() const;

    private:
        /**
         * @brief �Ӹ���̳ж������������ػ�������˵�����ӿ�û�����壬��ʹ��readImage������
         */
        virtual bool readData(size_t offset, size_t size, void *dst) override;

        /**
         * @brief �Ӹ���̳ж������������ػ�������˵�����ӿ�û�����壬��ʹ��writeImage������
         */
        virtual bool writeData(size_t offset, size_t size, const void *src, bool discardWholeBuffer /* = false */) override;

        /**
         * @brief �Ӹ���̳ж������������ػ�������˵�����ӿ�û�����壬��ʹ��lockImpl(const Rect &, LockOptions)������
         * @see void *lockImpl(const Rect &, LockOptions)
         */
        virtual void *lockImpl(size_t offset, size_t size, LockOptions options) override;

    protected:
        uint32_t    mWidth;         /// ���ػ������Ŀ��
        uint32_t    mHeight;        /// ���ػ������ĸ߶�
        size_t      mPitch;         /// ���ػ�������pitch
        PixelFormat mFormat;        /// ���ػ������ĸ�ʽ
    };
}


#endif  /*__T3D_HARDWARE_PIXEL_BUFFER_H__*/
