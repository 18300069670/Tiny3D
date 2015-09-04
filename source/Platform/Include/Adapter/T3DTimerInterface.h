

#ifndef __T3D_TIMER_INTERFACE_H__
#define __T3D_TIMER_INTERFACE_H__


#include "T3DType.h"
#include "T3DMacro.h"


namespace Tiny3D
{
	class TimerObserver;

	const uint32_t T3D_INVALID_TIMER_ID = 0;		/**< ��Ч��ʱ��ID */

	/**
	 * @class ITimerAdapter
	 * @brief ����ϵͳƽ̨��صĶ�ʱ���ӿ���.
	 * @note ��ز���ϵͳƽ̨��Ҫ�̳иýӿ���ʵ�־���ƽ̨��ع���.
	 */
	class TimerInterface
	{
		T3D_DECLARE_INTERFACE(TimerInterface);

	public:
		/**
		 * @brief ������ʱ������ʱ����ѭ����ʱ.
		 * @param [in] unInterval : ��ʱ��ʱ����������
		 * @return ���ض�ʱ����ӦID.  
		 */
		virtual uint32_t start(uint32_t unInterval) = 0;

		/**
		 * @brief �رն�ʱ��.
		 * @return void  
		 */
		virtual void stop() = 0;

		/**
		 * @brief ���ö�ʱ���ص��۲��߶���.
		 * @param [in] pObserver : �۲��߶���
		 * @return void
		 * @see class ITimerObserver
		 */
		virtual void setObserver(TimerObserver *pObserver) = 0;

		/**
		 * @brief ��ȡ��ʱ�������Ӧ�Ķ�ʱ��ID 
		 * @note ��ǰ��ʱ�����ڼ�ʱ���򷵻غϷ��Ķ�Ӧ�Ķ�ʱ��ID�����򷵻���Ч��ʱ��ID.
		 * @return ���ض�ʱ��ID  
		 */
		virtual uint32_t getTimerID() const = 0;
	};
}



#endif	/*__T3D_TIMER_ADPATER_INTERFACE_H__*/
