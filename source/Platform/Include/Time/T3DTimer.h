
#ifndef __T3D_TIMER_H__
#define __T3D_TIMER_H__


#include "T3DType.h"
#include "T3DMacro.h"
#include "T3DPlatformMacro.h"


namespace Tiny3D
{
	class TimerObserver;
	class TimerInterface;

	/**
	 * @class VTimer
	 * @brief ��ʱ����.
	 * @note �����ǲ���ϵͳƽ̨�޹ض�ʱ������ƽ̨�����Ľ�һ����װ.
	 */
	class T3D_PLATFORM_API Timer
	{
		T3D_DISABLE_COPY(Timer);

	public:
		/**
		 * @brief Constructor for VTimer.
		 */
		Timer();

		/**
		 * @brief Destructor for VTimer.
		 */
		~Timer();

		/**
		 * @brief ������ʱ��.
		 * @param [in] unInterval : ��ʱ������
		 * @return ��ʱ��ID  
		 */
		uint32_t start(uint32_t unInterval);

		/**
		 * @brief �رն�ʱ��.
		 * @return void  
		 */
		void stop();

		/**
		 * @brief ���ö�ʱ���۲��߶���.
		 * @param [in] pObserver : �۲��߶���
		 * @return void  
		 */
		void setObserver(TimerObserver *pObserver);

		/**
		 * @brief ��ȡ��ʱ��ID.
		 * @return ���ض�ʱ��ID  
		 */
		uint32_t getTimerID() const;

	protected:
		TimerInterface *m_pAdapter;
	};
}

#endif	/*__T3D_TIMER_H__*/
