

#ifndef __T3D_DEVICE_INFO_H__
#define __T3D_DEVICE_INFO_H__


#include "T3DSingleton.h"
#include "T3DPlatformPrerequisites.h"


namespace Tiny3D
{
    class DeviceInfoInterface;
    class FactoryInterface;

    class T3D_PLATFORM_API DeviceInfo : public Singleton<DeviceInfo>
    {
        T3D_DISABLE_COPY(DeviceInfo);

    public:
        static const uint32_t PLATFORM_UNKNOWN;
        static const uint32_t PLATFORM_WINDOWS;
        static const uint32_t PLATFORM_MACOSX;
        static const uint32_t PLATFORM_LINUX;
        static const uint32_t PLATFORM_IOS;
        static const uint32_t PLATFORM_ANDROID;

        static const char* Unknown;
        static const char* Windows;
        static const char* MacOSX;
        static const char* Linux;
        static const char* iOS;
        static const char* Android;

    public:
        DeviceInfo(FactoryInterface *pAdapterFactory);
        virtual ~DeviceInfo();

        /**
         * @brief ��ȡƽ̨����
         */
        uint32_t getPlatform() const;

        /**
         * @brief ��ȡƽ̨�����ַ���
         */
        String getPlatformString() const;

        /**
         * @brief ��ȡ����汾���ַ���
         */
        String getSoftwareVersion() const;

        /**
         * @brief ��ȡ����ϵͳ�汾���ַ���
         */
        String getOSVersion() const;

        /**
         * @brief ��ȡ�豸���Ͱ汾��Ϣ�ַ���
         */
        String getDeviceVersion() const;

        /**
         * @brief ��ȡ��Ļ���.
         */
        int32_t getScreenWidth() const;

        /**
         * @brief ��ȡ��Ļ�߶�.
         */
        int32_t getScreenHeight() const;

        /**
         * @brief ��ȡ��Ļ�����ܶ�.
         */
        float getScreenDPI() const;

        /**
         * @brief ��ȡ�豸mac��ַ.
         */
        String getMacAddress() const;

        /**
         * @brief ��ȡCPU������Ϣ.
         */
        String getCPUType() const;

        /**
         * @brief ��ȡCPU����
         */
        int32_t getNumberOfProcessors() const;

        /**
         * @brief ��ȡ�ڴ���Ϣ.
         */
        uint32_t getMemoryCapacity() const;

        /**
         * @brief ��ȡ�豸ID.
         */
        String getDeviceID() const;

    protected:
        DeviceInfoInterface *m_pDevInfoAdapter;
    };

#define T3D_DEVICE_INFO     DeviceInfo::getInstance()
}


#endif  /*__T3D_DEVICE_INFO_H__*/
