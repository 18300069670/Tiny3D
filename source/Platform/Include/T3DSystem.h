

#ifndef __T3D_SYSTEM_H__
#define __T3D_SYSTEM_H__


#include "T3DSingleton.h"
#include "T3DPlatformPrerequisites.h"


namespace Tiny3D
{
    class FactoryInterface;
    class Console;
    class DeviceInfo;
    class TextCodec;
    class RunLoop;

    /**
     * @class VSystem
     * @brief ϵͳ��.
     * @note �����һЩȫ�ֵĵ����������ͷţ�Ϊ�ϲ��ṩ��ܲ��ϵͳ��ͳһ�ӿ�.
     */
    class T3D_PLATFORM_API System : public Singleton<System>
    {
        T3D_DISABLE_COPY(System);

    public:
        /**
         * @brief Constructor for VSystem.
         */
        System();

        /**
         * @brief Destructor for VSystem.
         */
        ~System();

        /**
         * @brief ÿ������ѭ�����ô���.
         * @return void
         */
        void process();

        /**
         * @brief ��ȡ����ϵͳ����㹤���ӿڶ���
         */
        FactoryInterface &getAdapterFactory()
        {
            return (*m_pAdapterFactory);
        }

        RunLoop &getMainRunLoop();

    private:
        FactoryInterface        *m_pAdapterFactory;
        TextCodec               *m_pTextCodec;
        Console                 *m_pConsole;
        DeviceInfo              *m_pDeviceInfo;
        RunLoop                 *m_pMainRunLoop;
    };

    #define T3D_SYSTEM              (System::getInstance())
    #define T3D_ADAPTER_FACTORY     (T3D_SYSTEM.getAdapterFactory())
    #define T3D_MAIN_RUNLOOP        (System::getInstance().getMainRunLoop())
}


#endif
