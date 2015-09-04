

#ifndef __T3D_RUN_LOOP_H__
#define __T3D_RUN_LOOP_H__


#include "T3DSingleton.h"
#include "T3DPlatformMacro.h"
#include <map>


namespace Tiny3D
{
	#define T3D_INVALID_LOOP_ID		0

	class RunLoopObserver;

	/**
	 * @class T3DRunLoop
	 * @brief ����ѭ������
	 * @note ������ϵͳѭ��������ϵͳѭ����ʱ
	 */
	class T3D_PLATFORM_API RunLoop
	{
		T3D_DISABLE_COPY(RunLoop);

	public:
		/**
		 * @brief Constructor for T3DRunLoop.
		 */
		RunLoop();

		/**
		 * @brief Destructor for T3DRunLoop.
		 */
		~RunLoop();

		/**
		 * @brief ����ϵͳѭ����ʱ��.
		 * @param [in] unInterval : ��ʱ������
		 * @param [in] bRepeat : �Ƿ�ѭ����ʱ��
		 * @return ѭ��ID
		 */
		uint32_t start(uint32_t unInterval, bool bRepeat, RunLoopObserver *pObserver);
		
		/**
		 * @brief �򵥵�����ϵͳѭ��������ѭ���������ص�
		 * @param : void
		 * @return ѭ��ID
		 */
		uint32_t start(RunLoopObserver *pObserver);

		/**
		 * @brief �ر�ѭ����ʱ��.
		 * @param [in] unLoopID : ѭ��ID������start�ӿڷ���
		 * @return ��Ӧ��ѭ����ʱ��ID��Ч�ͷ���true�����򷵻�false
		 */
		bool stop(uint32_t unLoopID);

		/**
		 * @brief ִ�м�ʱ���������ɷ��ص�
		 */
		void execute();

	protected:
		struct RunLoopInfo
		{
			uint64_t			ullLastTimestamp;	/// �ϴμ�ʱʱ���
			uint64_t			ullInterval;		/// �趨��ʱ����
			RunLoopObserver	*pObserver;			/// �ص�����
			bool				bRepeat;			/// �Ƿ�ѭ����ʱ
		};

		typedef std::map<uint32_t, RunLoopInfo> T3DRunLoopInfos;
		typedef T3DRunLoopInfos::iterator		T3DRunLoopInfosItr;

		typedef std::pair<uint32_t, RunLoopInfo> T3DRunLoopValue;

		T3DRunLoopInfos	m_infos;
		static uint32_t m_unLoopID;
	};
}


#endif	/*__T3D_RUN_LOOP_H__*/