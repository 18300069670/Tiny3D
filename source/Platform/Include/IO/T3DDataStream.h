

#ifndef __T3D_DATA_STREAM_H__
#define __T3D_DATA_STREAM_H__


#include "T3DType.h"
#include "T3DMacro.h"
#include "T3DPlatformPrerequisites.h"


namespace Tiny3D
{
    class T3D_PLATFORM_API DataStream
    {
        T3D_DECLARE_INTERFACE(DataStream);

    public:
        /**
         * @brief ���������ж����ݵ�������.
         * @param [in] pBuffer : ���ݻ�����
         * @param [in] nSize : ���ݻ�������С
         * @return ���ض�ȡ�������ݴ�С.
         */
        virtual size_t read(void *pBuffer, size_t nSize) = 0;

        /**
         * @brief д���������ݵ���������.
         * @param [in] pBuffer : ���ݻ�����
         * @param [in] nSize : ���ݻ�������С
         * @return ����д������ݴ�С.
         */
        virtual size_t write(void *pBuffer, size_t nSize) = 0;

        /**
         * @brief ��������ָ���ƶ���ָ��λ��.
         * @param [in] llPos : ָ��ƫ��λ��
         * @param [in] relative : �Ƿ����λ��
         * @return �����óɹ�ʱ������true
         */
        virtual bool seek(long_t lPos, bool relative) = 0;

        /**
         * @brief ��ȡ��ǰ��������дλ��.
         * @return ���ص�ǰ��������дλ��.
         */
        virtual long_t tell() const = 0;

        /**
         * @brief ��ȡ�������Ĵ�С.
         * @return ���ص�ǰ�������Ĵ�С
         */
        virtual long_t size() const = 0;

        /**
         * @brief �Ƿ�������ĩβ.
         * @return ��ĩβ����true�����򷵻�false.
         */
        virtual bool eof() const = 0;

        /**
         * @brief �����������ֵ��������
         */
        DataStream &operator<<(bool val);
        DataStream &operator<<(int8_t val);
        DataStream &operator<<(uint8_t val);
        DataStream &operator<<(int16_t val);
        DataStream &operator<<(uint16_t val);
        DataStream &operator<<(int32_t val);
        DataStream &operator<<(uint32_t val);
        DataStream &operator<<(int64_t val);
        DataStream &operator<<(uint64_t val);
        DataStream &operator<<(float val);
        DataStream &operator<<(double val);
        DataStream &operator<<(const char *s);
        DataStream &operator<<(const String &s);

        /**
         * @brief ��������������������ֵ
         */
        DataStream &operator>>(bool &val);
        DataStream &operator>>(int8_t &val);
        DataStream &operator>>(uint8_t &val);
        DataStream &operator>>(int16_t &val);
        DataStream &operator>>(uint16_t &val);
        DataStream &operator>>(int32_t &val);
        DataStream &operator>>(uint32_t &val);
        DataStream &operator>>(int64_t &val);
        DataStream &operator>>(uint64_t &val);
        DataStream &operator>>(float &val);
        DataStream &operator>>(double &val);
        DataStream &operator>>(char *&s);
        DataStream &operator>>(String &s);
    };
}

#endif  /*__T3D_DATA_STREAM_H__*/
