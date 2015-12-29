

#ifndef __T3D_DATE_TIME_H__
#define __T3D_DATE_TIME_H__


#include "T3DType.h"
#include "T3DMacro.h"
#include "T3DPlatformPrerequisites.h"


namespace Tiny3D
{
    /**
     * @class T3DDateTime
     * @brief ����ʱ����ز�������.
     */
    class T3D_PLATFORM_API DateTime
    {
    public:
        enum ETimeFormat
        {
            E_HH_MM_SS_XXX = 0,     /// ת���ַ�����ʽΪ��HH:MM:SS.XXX
            E_HH_MM_SS,
            E_HH_MM,
        };

        enum EDateFormat
        {
            E_YY_MM_DD = 0,
            E_MM_DD,
            E_YY_MM,
        };

    public:
        /**
         * @brief Default Constructor for T3DDateTime.
         */
        DateTime();

        /**
         * @brief Constructor for T3DDateTime.
         * @param [in] nYear : ��
         * @param [in] nMonth : ��
         * @param [in] nDay : ��
         * @param [in] nHour : ʱ
         * @param [in] nMin : ��
         * @param [in] nSecond : ��
         * @param [in] millisecond : ����
         */
        DateTime(int32_t nYear, int32_t nMonth, int32_t nDay, int32_t nHour, int32_t nMin, int32_t nSecond, int32_t millisecond);

        /**
         * @brief ��T3DDateTime��ʱ��ת���ɴ�1970��1��1�տ�ʼ�ĺ�����.
         * @return ����ʱ�������.
         */
        uint64_t toMSecsSinceEpoch() const;

        /**
         * @brief ��VDataTime��ʱ��ת���ַ���.
         * @note �ַ�����ʽ���磺YYYY-MM-DD HH:MM:SS.XXX
         * @return ����std::string����
         */
        String toString() const;

        /**
         * @brief ��VDataTime��ʱ��ת���ַ���.
         * @note �ַ�����ʽ���磺HH:MM:SS.XXX
         * @return ����std::string����
         */
        String timeToString(ETimeFormat eFormat = E_HH_MM_SS_XXX) const;

        /**
         * @brief ��VDataTime��ʱ��ת���ַ���.
         * @note �ַ�����ʽ���磺YYYY-MM-DD
         * @return ����std::string����
         */
        String dateToString(EDateFormat eFormat = E_YY_MM_DD) const;

        /**
         * @brief �ж�ʱ���Ƿ����
         */
        bool operator ==(const DateTime &other) const;

        /**
         * @brief �ж�ʱ���Ƿ����
         */
        bool operator !=(const DateTime &other) const;

        /**
         * @brief �ж�ʱ���Ƿ����
         */
        bool operator <(const DateTime &other) const;

        /**
         * @brief �ж�ʱ���Ƿ����
         */
        bool operator <=(const DateTime &other) const;

        /**
         * @brief �ж�ʱ���Ƿ����
         */
        bool operator >(const DateTime &other) const;

        /**
         * @brief �ж�ʱ���Ƿ����
         */
        bool operator >=(const DateTime &other) const;

    public:
        /**
         * @brief ��̬�ӿڣ���ȡ��ǰʱ���T3DDateTime����.
         * @return ���ص�ǰʱ���T3DDateTime����.
         */
        static DateTime currentDateTime();

        /**
         * @brief ��̬�ӿڣ���ȡ��ǰ��������ʱ���T3DDateTime����.
         * @return ���ص�ǰ��������ʱ���T3DDateTime����.
         */
        static DateTime currentDateTimeUTC();

        /**
         * @brief ��̬�ӿڣ���ȡ��1970��1��1�յ����ڵ�ʱ������
         * @return ����ʱ������
         */
        static uint64_t currentSecsSinceEpoch();

        /**
         * @brief ��̬�ӿڣ���ȡ��1970��1��1�յ����ڵ�ʱ�������.
         * @return ����ʱ�������.
         */
        static uint64_t currentMSecsSinceEpoch();

        /**
         * @brief ��̬�ӿڣ��Ѵ�1970��1��1�տ�ʼ�ĺ�����ת����T3DDateTime����.
         * @param [in] msecs : ��1970��1��1�տ�ʼ�ĺ�����
         * @return ����T3DDateTime����.
         */
        static DateTime fromMSecsSinceEpoch(uint64_t msecs);

        /**
         * @brief ��̬�ӿڣ��Ѵ�1970��1��1�տ�ʼ������ת����T3DDateTime����.
         * @param [in] msecs : ��1970��1��1�տ�ʼ������
         * @return ����T3DDateTime����.
         */
        static DateTime fromSecsSinceEpoch(uint64_t sces);

    public:
        /** ������ */
        int32_t Year() const
        {
            return m_nYear;
        }
        /** ������ */
        int32_t Month() const
        {
            return m_nMonth;
        }
        /** ������ */
        int32_t Day() const
        {
            return m_nDay;
        }
        /** ����ʱ */
        int32_t Hour() const
        {
            return m_nHour;
        }
        /** ���ط� */
        int32_t Minute() const
        {
            return m_nMinute;
        }
        /** ������ */
        int32_t Second() const
        {
            return m_nSecond;
        }
        /** ���غ��� */
        int32_t Millisecond() const
        {
            return m_nMillisecond;
        }

    private:
        int32_t m_nYear;
        int32_t m_nMonth;
        int32_t m_nDay;
        int32_t m_nHour;
        int32_t m_nMinute;
        int32_t m_nSecond;
        int32_t m_nMillisecond;
    };
}


#endif  /*__T3D_DATE_TIME_H__*/
