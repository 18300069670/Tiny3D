

#ifndef __T3D_TIMER_OBSERVER_H__
#define __T3D_TIMER_OBSERVER_H__


#include "T3DType.h"
#include "T3DMacro.h"
#include "T3DPlatformMacro.h"


namespace Tiny3D
{
	/**
	 * @class ITimerObserver
	 * @brief ��ʱ���۲��߽ӿ���.
	 * @note �̳и���ʵ�ֽӿ��ԶԶ�ʱ���¼�����.
	 */
	class T3D_PLATFORM_API TimerObserver
	{
		T3D_DECLARE_INTERFACE(TimerObserver);

	public:
		/**
		 * @brief ��ʱ��ʱ�䵽��ص�.
		 * @param [in] unTimerID : ����ʱ��Ķ�ʱ��ID
		 * @return void
		 */
		virtual void onTimer(uint32_t unTimerID) = 0;
	};
}


#endif	/*__T3D_TIMER_OBSERVER_H__*/
