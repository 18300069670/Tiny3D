
#include "Render/T3DHardwareBuffer.h"


namespace Tiny3D
{
    HardwareBuffer::HardwareBuffer(Usage usage, bool systemMemory, bool useShadowBuffer)
        : mBufferSize(0)
        , mLockSize(0)
        , mLockOffset(0)
        , mUsage(usage)
        , mShadowBuffer(nullptr)
        , mSystemMemory(systemMemory)
        , mUseShadowBuffer(useShadowBuffer)
        , mIsLocked(false)
        , mIsShadowBufferDirty(false)
    {
        if (useShadowBuffer && usage == E_HBU_DYNAMIC)
        {
            mUsage = E_HBU_DYNAMIC_WRITE_ONLY;
        }
        else if (useShadowBuffer && usage == E_HBU_STATIC)
        {
            mUsage = E_HBU_STATIC_WRITE_ONLY;
        }
    }

    HardwareBuffer::~HardwareBuffer()
    {
        mShadowBuffer = nullptr;
    }

    void *HardwareBuffer::lock(size_t offset, size_t size, LockOptions options)
    {
        T3D_ASSERT(!isLocked());

        void *buffer = nullptr;

        if ((offset + size) > mBufferSize)
        {
            // Խ���� :(
        }
        else if (mUseShadowBuffer)
        {
            if (options != E_HBL_READ_ONLY)
            {
                // ����ֻ�����ǾͿ��ܻᱻ�ı䣬�Ȼ����ʱ��Ӱ��buffer����Ӳ��buffer
                mIsShadowBufferDirty = true;
            }

            buffer = mShadowBuffer->lock(offset, size, options);
        }
        else
        {
            // û��Ӱ��buffer������ʵ�����ӿ�
            buffer = lockImpl(offset, size, options);
        }

        if (buffer != nullptr)
        {
            mLockOffset = offset;
            mLockSize = size;
        }

        return buffer;
    }

    void *HardwareBuffer::lock(LockOptions options)
    {
        return lock(0, mBufferSize, options);
    }

    void HardwareBuffer::unlock()
    {
        T3D_ASSERT(isLocked());

        if (mUseShadowBuffer && mShadowBuffer->isLocked())
        {
            mShadowBuffer->unlock();
            updateFromShadow();
        }
        else
        {
            unlockImpl();
            mIsLocked = false;
        }
    }

    bool HardwareBuffer::copyData(const HardwareBufferPtr &srcBuffer, size_t srcOffset, size_t dstOffset, size_t size, bool discardWholeBuffer /* = false */)
    {
        bool ret = false;
        const void *src = srcBuffer->lock(srcOffset, size, E_HBL_READ_ONLY);
        if (src != nullptr)
        {
            ret = writeData(dstOffset, size, src, true);
            srcBuffer->unlock();
        }

        return ret;
    }

    bool HardwareBuffer::copyData(const HardwareBufferPtr &srcBuffer)
    {
        size_t size = std::min(getBufferSize(), srcBuffer->getBufferSize()); 
        return copyData(srcBuffer, 0, 0, size, true);
    }

    void HardwareBuffer::updateFromShadow()
    {
        if (mUseShadowBuffer && mIsShadowBufferDirty)
        {
            const void *src = mShadowBuffer->lock(mLockOffset, mLockSize, E_HBL_READ_ONLY);
            if (src != nullptr)
            {
                LockOptions options;
                if (mLockOffset == 0 && mLockSize == mBufferSize)
                {
                    options = E_HBL_DISCARD;
                }
                else
                {
                    options = E_HBL_NORMAL;
                }

                void *dst = lockImpl(mLockOffset, mLockSize, options);
                if (dst != nullptr)
                {
                    memcpy(dst, src, mLockSize);
                    unlockImpl();
                }

                mShadowBuffer->unlock();
                mIsShadowBufferDirty = false;
            }
        }
    }
}
