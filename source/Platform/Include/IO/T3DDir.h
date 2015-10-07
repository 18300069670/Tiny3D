

#ifndef __T3D_DIR_H__
#define __T3D_DIR_H__


#include "T3DType.h"
#include "T3DMacro.h"
#include "T3DPlatformMacro.h"


namespace Tiny3D
{
    class DirInterface;

    class T3D_PLATFORM_API Dir
    {
        T3D_DISABLE_COPY(Dir);

    public:
        static char NATIVE_SEPARATOR;

    public:
        /**
         * @brief Constructor for T3DDir.
         */
        Dir();

        /**
         * @brief Destructor for T3DDir.
         */
        ~Dir();

        /**
         * @brief ��ʼö������ָ��Ŀ¼�µ��ļ�.
         * @param [in] strPath : ָ��Ŀ¼�ļ���ʽ�ַ���
         * @return ���óɹ�����true��ʧ�ܷ���false.
         */
        bool findFile(const TString &strPath);

        /**
         * @brief ������һ���ļ�.
         * @return ö��û��������true�����򷵻�false��ʾö�ٽ���.
         */
        bool findNextFile();

        /**
         * @brief ������ǰö������.
         * @return void
         */
        void close();

        /**
         * @brief ��ȡö��Ŀ¼������·��.
         * @return ����ö��Ŀ¼��·������������std::string.
         */
        TString getRoot() const;

        /**
         * @brief ��ȡ��ǰö�ٵ��������ļ���.
         * @return ���ص�ǰö�ٵ��������ļ���������std::string.
         */
        TString getFileName() const;

        /**
         * @brief ��ȡ��ǰö�ٵ����ļ���ȫ·���������������ļ���.
         * @return ���ص�ǰö�ٵ����ļ���ȫ·����������std::string.
         */
        TString getFilePath() const;

        /**
         * @brief ��ȡ��ǰö�ٵ����ļ��ļ�������������չ��.
         * @return ���ص�ǰö�ٵ����ļ��ļ���������std::string.
         */
        TString getFileTitle() const;

        /**
         * @brief ��ȡ��ǰö�ٵ����ļ���С.
         * @return ���ص�ǰö�ٵ����ļ���С.
         */
        uint32_t getFileSize() const;

        /**
         * @brief �жϵ�ǰö�ٵ����ļ��Ƿ��Ŀ¼������'.'��'..' .
         * @return ��Ŀ¼����true�����򷵻�false.
         */
        bool isDots() const;

        /**
         * @brief �жϵ�ǰö�ٵ����ļ��Ƿ��ļ���.
         * @return �ļ�����true�����򷵻�false.
         */
        bool isDirectory() const;

        /**
         * @brief ��ȡ��ǰö�ٵ����ļ��Ĵ���ʱ���.
         * @return �����ļ�����ʱ�������ʱ���Ǵ�1970��1��1�յ���ǰ������
         */
        long_t getCreationTime() const;

        /**
         * @brief ��ȡ��ǰö�ٵ����ļ���������ʱ���.
         * @return �����ļ�������ʱ�������ʱ���Ǵ�1970��1��1�յ���ǰ������
         */
        long_t getLastAccessTime() const;

        /**
         * @brief ��ȡ��ǰö�ٵ����ļ�������޸�ʱ���.
         * @return �����ļ�����޸�ʱ�������ʱ���Ǵ�1970��1��1�յ���ǰ������
         */
        long_t getLastWriteTime() const;

        /**
         * @brief �����ļ���.
         * @note �ýӿڲ��ܴ����༶�ļ���.
         * @param [in] strDir : �ļ���·������
         * @return ���óɹ�����true�����򷵻�false.
         */
        static bool makeDir(const TString &strDir);

        /**
         * @brief ɾ���ļ���.
         * @note �ýӿڲ���ɾ���༶�ļ���.
         * @param [in] strDir : �ļ���·������
         * @return ���óɹ�����true�����򷵻�false.
         */
        static bool removeDir(const TString &strDir);

        /**
         * @brief ɾ���ļ�.
         * @param [in] strFileName : ��Ҫɾ���ļ�������.
         * @return ���óɹ�����true�����򷵻�false.
         */
        static bool remove(const TString &strFileName);

        /**
         * @brief �ж�·����Ӧ���ļ��Ƿ����.
         * @param [in] strPath : ����·����
         * @return �ļ����ڷ���true�����򷵻�false.
         */
        static bool exists(const TString &strPath);

        /**
         * @brief ��ȡӦ�ó��򻺴����ݴ洢·������ͬƽָ̨����Ӧ��·�����Զ��ϲ�͸������.
         * @return ����Ӧ�ó��򻺴����ݴ洢·��.
         */
        static TString getCachePath();

        /**
         * @brief ��ȡӦ�ó���·��.
         * @return ����Ӧ�ó���·��.
         */
        static TString getAppPath();

        /**
         * @brief ��ȡϵͳ��ص�·���ָ���
         */
        static char getNativeSeparator();

    protected:
        DirInterface    *m_pDirAdpater;

        static DirInterface *s_pDirAdapter;
    };
}


#endif  /*__T3D_DIR_H__*/
