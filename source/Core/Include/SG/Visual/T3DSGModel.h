
#ifndef __T3D_SG_MODEL_H__
#define __T3D_SG_MODEL_H__


#include "SG/Visual/T3DSGShape.h"


namespace Tiny3D
{
    class T3D_ENGINE_API SGModel : public SGShape
    {
    public:
        enum RenderMode
        {
            E_RENDER_UNKNOWN = 0,
            E_RENDER_ENTITY,
            E_RENDER_SKELETON,
            E_RENDER_BOUND,
        };

        struct ActionInfo
        {
            String  mName;          /// ��������
            int64_t mDuration;      /// �ö�����������ʱ��
            int32_t mTotalFrames;   /// �ö��������ܹ��ؼ�֡֡��
        };

        typedef std::vector<ActionInfo>     ActionList;
        typedef ActionList::iterator        ActionListItr;
        typedef ActionList::const_iterator  ActionListConstItr;

        static SGModelPtr create(const String &modelName, uint32_t unID = E_NID_AUTOMATIC);

        virtual ~SGModel();

        void setRenderMode(RenderMode mode);

        virtual Type getNodeType() const override;

        virtual NodePtr clone() const override;

        /**
         * @brief ö�ٸ�ģ�����еĶ�������
         * @param [out] actions : ���������б�
         * @return void
         */
        void enumerateActionList(ActionList &actions);

        /**
         * @brief ����ָ���������ж�������
         * @param [in] name : ��������
         * @return ���óɹ�������true
         */
        bool runAction(const String &name, bool repeat = true, int32_t frame = 0);

        bool stopAction(const String &name);

        bool isActionRunning(const String &name) const;
        bool isActionRunning() const    { return mIsActionRunning; }

    protected:
        SGModel(uint32_t unID = E_NID_AUTOMATIC);

        virtual bool init(const String &modelName);

        virtual void updateTransform() override;

        void updateSkeleton();
        void updateBone(int64_t time, ObjectPtr skeleton);

    protected:
        ModelPtr    mModel;
        RenderMode  mRenderMode;

        Children        mMeshes;
        SGSkeletonPtr   mSkeleton;

        int64_t         mStarrTime;

        int32_t         mCurKeyFrameT;
        int32_t         mCurKeyFrameR;
        int32_t         mCurKeyFrameS;

        String          mCurActionName;
        bool            mIsActionRunning;
        bool            mIsLoop;

        ObjectPtr       mCurActionData;
    };
}


#endif  /*__T3D_SG_MODEL_H__*/
