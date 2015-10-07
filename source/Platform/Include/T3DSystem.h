

#ifndef __T3D_SYSTEM_H__
#define __T3D_SYSTEM_H__


#include "T3DSingleton.h"
#include "T3DPlatformMacro.h"


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
    class T3D_PLATFORM_API T3DSystem : public Singleton<T3DSystem>
    {
        T3D_DISABLE_COPY(T3DSystem);

    public:
        /**
         * @brief Constructor for VSystem.
         */
        T3DSystem();

        /**
         * @brief Destructor for VSystem.
         */
        ~T3DSystem();

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
        TextCodec                   *m_pTextCodec;
        Console                     *m_pConsole;
        DeviceInfo                  *m_pDeviceInfo;
        RunLoop                     *m_pMainRunLoop;
    };

#define T3D_SYSTEM              (T3DSystem::getInstance())
#define T3D_ADAPTER_FACTORY     (T3D_SYSTEM.getAdapterFactory())
#define T3D_MAIN_RUNLOOP        (T3DSystem::getInstance().getMainRunLoop())
}


#endif
