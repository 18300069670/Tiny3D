
#include "T3DLogger.h"
#include "T3DLogItem.h"
#include "T3DLogTask.h"
#include <sstream>
#include <stdarg.h>


namespace Tiny3D
{
    T3D_INIT_SINGLETON(Logger);

    int32_t Logger::asyncWorkingProcedure(Logger *pThis)
    {
        return pThis->workingProcedure();
    }

    Logger::Logger()
    {

    }

    Logger::~Logger()
    {

    }

    void Logger::setLevel(Level eLevel)
    {
        if (eLevel != mStrategy.eLevel)
        {
            if (mIsRunning)
            {
                if (mStrategy.eLevel == E_LEVEL_OFF)
                {
                    mStrategy.eLevel = eLevel;
                    startup(mAppID, mTag, mIsForced);
                }
                else if (eLevel == E_LEVEL_OFF)
                {
                    shutdown();
                    mStrategy.eLevel = eLevel;
                }
                
                mStrategy.eLevel = eLevel;
            }
        }
    }

    void Logger::setMaxCacheSize(uint32_t unMaxCacheSize)
    {
        mStrategy.unMaxCacheSize = unMaxCacheSize;
    }

    void Logger::setExpired(uint32_t unExpired)
    {
        mStrategy.unExpired = unExpired;
    }

    void Logger::setMaxCacheTime(uint32_t unMaxCacheTime)
    {
        if (unMaxCacheTime != mStrategy.unMaxCacheTime)
        {
            mStrategy.unMaxCacheTime = unMaxCacheTime;

            stopFlushTimer();
            startFlushTimer();
        }
    }

    void Logger::setStrategy(const Strategy &strategy)
    {
        setMaxCacheSize(strategy.unMaxCacheSize);
        setMaxCacheTime(strategy.unMaxCacheTime);
        setExpired(strategy.unExpired);
        setLevel(strategy.eLevel);
    }

    bool Logger::startup(uint32_t appID, const String &tag, bool force /* = false */)
    {
        mAppID = appID;
        mTag = tag;
        mIsForced = force;

        if (mStrategy.eLevel != E_LEVEL_OFF)
        {
            /// ���ǹر���־�������Ҫ�ȴ���־
            if (openLogFile())
            {
                /// ������ʱ������ʱ�ύд���첽����
                stopFlushTimer();
                startFlushTimer();
            }
        }

        /// �����Ƿ�Ҫ�����־�����ύһ����������־�ļ����첽����
        commitCheckExpiredTask();

        return true;
    }

    void Logger::trace(Level level, const char *filename, int32_t line, const char *fmt, ...)
    {
        if (!mIsForced && level > mStrategy.eLevel)
            return;

        va_list args;
        char content[2048] = {0};

        va_start(args, fmt);
        vsnprintf(content, sizeof(content)-1, fmt, args);
        va_end(args);

        /// ��ȡ·����ֱ�ӻ�ȡԴ���ļ���
        String name = getFileName(filename);

        /// ����һ����־��
        LogItem *item = new LogItem(level, filename, line, content);
        
        /// ���������̨
        item->outputConsole();

        mItemCache[mCacheIndex].push_back(item);

        if (mItemCache[mCacheIndex].size() >= mStrategy.unMaxCacheSize)
        {
            commitFlushCacheTask();
        }
    }

    void Logger::shutdown()
    {
        /// ֹͣ����д���ļ������ʱ��
        stopFlushTimer();

        /// �����л��涼ͬ��д���ļ���
        flushCache();

        /// �ر��ļ�
        closeLogFile();
    }

    void Logger::enterBackground()
    {

    }

    void Logger::enterForeground()
    {

    }

    String Logger::getLogPath() const
    {
        String cachePath = Dir::getCachePath();
        String path = cachePath + "Log" + Dir::NATIVE_SEPARATOR;
        return path;
    }

    String Logger::makeLogFileName(uint32_t appID, const String &tag, const DateTime &dt)
    {
        String logPath = getLogPath();

        std::stringstream ss;
        ss<<appID<<"_"<<tag<<"_"<<dt.dateToString(DateTime::E_YY_MM_DD)<<"_"<<dt.Hour()<<".log";

        String fullPath = logPath + "/" + ss.str();
        return fullPath;
    }

    bool Logger::openLogFile()
    {
        /// �ȴ�����־�ļ���
        String logPath = getLogPath();
        Dir dir;
        dir.makeDir(logPath);

        DateTime dt = DateTime::currentDateTime();
        String filename = makeLogFileName(mAppID, mTag, dt);
        bool ret = false;
        if (ret = mFileStream.open(filename.c_str(), FileDataStream::E_MODE_APPEND|FileDataStream::E_MODE_TEXT))
        {
            mCurLogFileTime = dt;
        }

        return ret;
    }

    void Logger::writeLogFile(int32_t cacheIndex)
    {

    }

    void Logger::closeLogFile()
    {

    }

    void Logger::startFlushTimer()
    {
        mFlushCacheTimerID = T3D_MAIN_RUNLOOP.start(mStrategy.unMaxCacheTime, true, this);
    }

    void Logger::stopFlushTimer()
    {
        if (mFlushCacheTimerID != T3D_INVALID_LOOP_ID)
        {
            T3D_MAIN_RUNLOOP.stop(mFlushCacheTimerID);
            mFlushCacheTimerID = T3D_INVALID_LOOP_ID;
        }
    }

    void Logger::onExecute(uint32_t unLoopID, uint64_t dt)
    {

    }

    String Logger::getFileName(const String &path) const
    {
        int32_t pos = path.rfind(Dir::NATIVE_SEPARATOR) + 1;
        String name = path.substr(pos, path.length()- pos+1);
        return name;
    }

    void Logger::startAsyncTask()
    {
        if (!mWorkingThread.joinable())
        {
            /// �����첽�߳�
            mWorkingThread = std::thread(Logger::asyncWorkingProcedure, this);
            mIsRunning = true;
        }
        else
        {
            // �첽�߳��Ѿ�������
            if (mIsSuspended)
            {
                /// �첽�̱߳���������
                resumeAsyncProcedure();
            }
        }
    }
}