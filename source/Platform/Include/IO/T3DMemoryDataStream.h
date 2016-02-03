

#ifndef __T3D_MEMORY_DATA_STREAM_H__
#define __T3D_MEMORY_DATA_STREAM_H__


#include "IO/T3DDataStream.h"


namespace Tiny3D
{
    /**
     * @class T3DMemoryDataStream
     * @brief �ڴ���������.
     * @note �����ṩ�����ڴ��������Ĵ洢����.
     */
    class T3D_PLATFORM_API MemoryDataStream : public DataStream
    {
    public:
        static const uint32_t MEMORY_BUFFER_SIZE;   /**< Ĭ���ڴ�����С */

        MemoryDataStream();

        /**
         * @brief Constructor for T3DMemoryDataStream.
         * @note �ù��캯���ڲ����Զ�����ռ䣬ֱ�ӶԴ���Ļ���������
         * @param [in] pBuffer : ���ݻ���
         * @param [in] unSize : �����С
         * @param [in] reallocate : �Ƿ��ڲ����·���ռ䣬Ĭ�������ڲ����·���ռ�洢����
         */
        MemoryDataStream(uchar_t *pBuffer, size_t unSize, bool reallocate = true);

        /**
         * @brief Constructor for T3DMemoryDataStream.
         * @note �ڲ��Զ�����ռ�.
         * @param [in] unSize : ����ռ��С��Ĭ��ΪV_MEMORY_DATA_STREAM_BUFFER_SIZE.
         * @see V_MEMORY_DATA_STREAM_BUFFER_SIZE
         */
        MemoryDataStream(size_t unSize);

        /**
         * @brief Constructor for T3DMemoryDataStream.
         * @note ��������.
         * @param [in] other : Դ����
         */
        MemoryDataStream(const MemoryDataStream &other);

        /**
         * @brief Destructor for T3DMemoryDataStream.
         */
        virtual ~MemoryDataStream();

        /**
         * @brief ���ظ�ֵ������.
         */
        MemoryDataStream &operator =(const MemoryDataStream &other);

        /**
         * @brief ��ȡ�ڴ�������.
         * @param [in] pBuffer : ���ݻ�����
         * @param [in] nSize : ���ݻ�������С
         * @return ��ȡ�������ݴ�С
         */
        size_t read(void *pBuffer, size_t nSize);

        /**
         * @brief д���ڴ�������.
         * @param [in] pBuffer : ���ݻ�����
         * @param [in] nSize : ���ݻ�������С
         * @return д�����ݴ�С
         */
        size_t write(void *pBuffer, size_t nSize);

        /**
         * @brief �����ڴ���������дƫ��λ��.
         * @param [in] unPos : ƫ��λ��
         * @return void
         */
        void seek(long_t lPos);

        /**
         * @brief ��ȡ��ǰ�ڴ���������дƫ��λ��.
         * @return ���ض�дƫ��λ��
         */
        long_t tell() const;

        /**
         * @brief ��ȡ�ڴ���������С.
         * @return �����ڴ���������С
         */
        long_t size() const;

        /**
         * @brief �Ƿ񵽴��ڴ�������ĩβ.
         * @return ����ĩβ����true�����򷵻�false.
         */
        bool eof() const;

        void setBuffer(uint8_t *buffer, size_t bufSize, bool reallocate = true);

        void getBuffer(uint8_t *&buffer, size_t &bufSize) const;

    protected:
        void copy(const MemoryDataStream &other);

    protected:
        uchar_t     *m_pBuffer;     /**< ���ݻ����� */
        long_t      m_lSize;        /**< ���ݻ�������С */
        long_t      m_lCurPos;      /**< ��ǰ��дλ�� */

        bool        m_bCreated;     /**< �Ƿ��ڴ洴����� */
    };
}


#endif  /*__T3D_MEMORY_DATA_STREAM_H__*/
