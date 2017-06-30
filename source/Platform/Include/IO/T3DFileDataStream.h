

#ifndef __T3D_FILE_DATA_STREAM_H__
#define __T3D_FILE_DATA_STREAM_H__



#include "IO/T3DDataStream.h"
#include <stdio.h>


namespace Tiny3D
{
    /**
     * @class T3DFileDataStream
     * @brief �ļ�����.
     * @note �����ṩ�ļ�����д����.
     */
    class T3D_PLATFORM_API FileDataStream : public DataStream
    {
        T3D_DISABLE_COPY(FileDataStream);

    public:
        /**
         * @brief �ļ�����ģʽ
         */
        enum EOpenMode
        {
            E_MODE_NOT_OPEN = 0x00000000L,      /**< �ļ�û�д� */
            E_MODE_READ_ONLY = 0x00000001L,     /**< ֻ����ʽ�� */
            E_MODE_WRITE_ONLY = 0x00000002L,        /**< ֻд��ʽ�� */
            E_MODE_READ_WRITE = E_MODE_READ_ONLY | E_MODE_WRITE_ONLY,   /**< ��д��ʽ�� */
            E_MODE_APPEND = 0x00000004L,            /**< ׷�ӷ�ʽ�� */
            E_MODE_TRUNCATE = 0x00000008L,      /**< �ļ��Ѿ�����ʱ���ԭ�����ݴ� */
            E_MODE_TEXT = 0x00000010L           /**< �ı��ļ� */
        };

        /**
         * @brief Constructor for T3DFileDataStream.
         */
        FileDataStream();

        /**
         * @brief Destructor for T3DFileDataStream.
         */
        virtual ~FileDataStream();

        /**
         * @brief ���ļ���.
         * @param [in] szFileName : �ļ���
         * @param [in] eMode : �򿪷�ʽ
         * @return �򿪳ɹ�����true�����򷵻�false.
         * @see enum EOpenMode
         */
        bool open(const char *szFileName, uint32_t unMode);

        /**
         * @brief �ر��ļ���.
         * @return void
         */
        void close();

        /**
         * @brief ��ȡ�ļ���.
         * @param [in] pBuffer : ���ݻ�����
         * @param [in] nSize : ���ݻ�������С
         * @return ��ȡ�������ݴ�С.
         */
        virtual size_t read(void *pBuffer, size_t nSize) override;

        /**
         * @brief д���ļ���.
         * @param [in] pBuffer : ��д�����ݻ�����
         * @param [in] nSize : ���ݻ�������С
         * @return д������ݴ�С
         */
        virtual size_t write(void *pBuffer, size_t nSize) override;

        /**
         * @brief ���ļ��������ڴ������ȫ��ǿ��д���ļ���
         */
        void flush();

        /**
         * @brief �����ļ�����дƫ��λ��.
         * @param [in] llPos : ƫ��λ��
         * @return �����óɹ�ʱ�����ص�ǰ��дλ�ã�������ʱ������-1
         */
        virtual bool seek(long_t lPos, bool relative) override;

        /**
         * @brief ��ȡ��ǰ�ļ�����ǰ��дλ��.
         * @return �����ļ�����ǰ��дλ��
         */
        virtual long_t tell() const override;

        /**
         * @brief ��ȡ�ļ���С.
         * @return �����ļ���С
         */
        virtual long_t size() const override;

        /**
         * @brief ��ȡ�Ƿ��ļ���ĩβ.
         * @return �ѵ��ļ���ĩβ
         */
        virtual bool eof() const override;

        bool isOpened() const   { return m_bIsOpened; }

    protected:
        FILE                *m_pFileHandle;     /**< �ļ�����ָ�� */
        mutable long_t      m_lSize;            /**< �ļ���С */
        bool                m_bIsOpened;        /**< �ļ��Ƿ�� */
    };
}


#endif  /*__T3D_FILE_DATA_STREAM_H__*/
