
#ifndef __T3D_DEVICE_INFO_WINDOWS_H__
#define __T3D_DEVICE_INFO_WINDOWS_H__


#include "Adapter/T3DDeviceInfoInterface.h"


namespace Tiny3D
{
    class DeviceInfo_Windows : public DeviceInfoInterface
    {
        T3D_DISABLE_COPY(DeviceInfo_Windows);

    public:
        DeviceInfo_Windows();
        virtual ~DeviceInfo_Windows();

        /**
         * @brief ��ȡƽ̨����
         */
        virtual uint32_t getPlatform() const;

        /**
         * @brief ��ȡ����汾���ַ���
         */
        virtual String getSoftwareVersion() const;

        /**
         * @brief ��ȡ����ϵͳ�汾���ַ���
         */
        virtual String getOSVersion() const;

        /**
         * @brief ��ȡ�豸���Ͱ汾��Ϣ�ַ���
         */
        virtual String getDeviceVersion() const;

        /**
         * @brief ��ȡ��Ļ���.
         */
        virtual int32_t getScreenWidth() const;

        /**
         * @brief ��ȡ��Ļ�߶�.
         */
        virtual int32_t getScreenHeight() const;

        /**
         * @brief ��ȡ��Ļ�����ܶ�.
         */
        virtual float getScreenDPI() const;

        /**
         * @brief ��ȡ�豸mac��ַ.
         */
        virtual String getMacAddress() const;

        /**
         * @brief ��ȡCPU������Ϣ.
         */
        virtual String getCPUType() const;

        /**
         * @brief ��ȡCPU����
         */
        virtual int32_t getNumberOfProcessors() const;

        /**
         * @brief ��ȡ�ڴ���Ϣ.
         */
        virtual uint32_t getMemoryCapacity() const;

        /**
         * @brief ��ȡ�豸ID.
         */
        virtual String getDeviceID() const;
    };
}


#endif  /*__T3D_DEVICE_INFO_WINDOWS_H__*/