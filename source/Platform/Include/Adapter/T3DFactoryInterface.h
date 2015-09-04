

#ifndef __T3D_FACTORY_INTERFACE_H__
#define __T3D_FACTORY_INTERFACE_H__


#include "T3DType.h"
#include "T3DMacro.h"


namespace Tiny3D
{
	class ConsoleInterface;
	class DeviceInfoInterface;
	class DirInterface;
	class TimerInterface;


	enum EPlatform
	{
		E_PLATFORM_UNKNOWN = 0,
		E_PLATFORM_WIN32 = 1,
		E_PLATFORM_MACOSX,
		E_PLATFORM_LINUX,
		E_PLATFORM_IOS,
		E_PLATFORM_ANDROID,
	};

	/**
	 * @class IAdapterFactory
	 * @brief ����ϵͳ����㹤���ӿ�.
	 * @note ��ͬ����ϵͳƽ̨��Ҫʵ�ּ̳и���ʵ�־���ƽ̨�ӿ�
	 */
	class FactoryInterface
	{
		T3D_DECLARE_INTERFACE(FactoryInterface);

	public:
		/**
		 * @brief ��������ϵͳ��صĿ���̨����.
		 * @return ���ؿ���̨������Ҫ�û�����delete�ͷ���Դ
		 */
		virtual ConsoleInterface *createConsoleAdapter() = 0;

		/**
		 * @brief ��������ϵͳ��صĶ�ʱ������.
		 * @return ���ض�ʱ��������Ҫ�û�����delete�ͷ���Դ
		 */
		virtual TimerInterface *createTimerAdapter() = 0;

		/**
		 * @brief ��������ϵͳ��ص�����·������.
		 * @return ��������·��������Ҫ�û�����delete�ͷ���Դ
		 */
		virtual DirInterface *createDirAdapter() = 0;
		
		/**
		 * @brief ��������ϵͳ��ص��豸��Ϣ����.
		 * @return �����豸��Ϣ����������Ҫ�û�����delete�ͷ���Դ
		 */
		virtual DeviceInfoInterface *createDeviceInfoAdapter() = 0;

		/**
		 * @brief ��ȡ��ǰƽ̨����.
		 * @return ���ص�ǰƽ̨����
		 */
		virtual EPlatform getPlatform() = 0;
	};

	/**
	 * @brief ��������ϵͳ��ص�����㹤������.
	 * @note ��ͬ����ϵͳƽ̨��Ҫʵ�ָýӿ��Է��ز���ϵͳ����㹤������ 
	 * @return ��������㹤��������Ҫ�û�����delete�ͷ���Դ
	 */
	FactoryInterface *createAdapterFactory();
}


#endif	/*__T3D_FACTORY_INTERFACE_H__*/
