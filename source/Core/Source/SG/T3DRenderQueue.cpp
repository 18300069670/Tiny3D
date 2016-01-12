

#include "SG/T3DRenderQueue.h"
#include "Resource/T3DMaterial.h"
#include "SG/Renderable/T3DSGRenderable.h"
#include "Render/T3DRenderer.h"


namespace Tiny3D
{
    RenderGroup::RenderGroup()
    {

    }

    RenderGroup::~RenderGroup()
    {

    }

    void RenderGroup::addRenderable(const MaterialPtr &material, const SGRenderablePtr &renderable)
    {
        RenderablesItr itr = mRenderables.find(material);

        if (itr != mRenderables.end())
        {
            /// ����ͬ���ʵģ��ŵ���ͬ������Ⱦ�����б���
            RenderableList &renderables = itr->second;
            renderables.push_back(renderable);
        }
        else
        {
            /// û����ͬ���ʵģ��¼�һ��������Ⱦ�����б�
            RenderableList renderables(1, renderable);
            mRenderables.insert(RenderablesValue(material, renderables));
        }
    }

    void RenderGroup::clear()
    {
        mRenderables.clear();
    }

    void RenderGroup::render(const RendererPtr &renderer)
    {
        RenderablesItr itr = mRenderables.begin();

        while (itr != mRenderables.end())
        {
            const MaterialPtr material = itr->first;
            renderer->setMaterial(material);

            RenderableList &renderables = itr->second;
            
            RenderableListItr i = renderables.begin();

            while (i != renderables.end())
            {
                VertexDataPtr vertices =(*i)->getVertices();
                IndexDataPtr indices = (*i)->getIndices();

//                 renderer->drawIndexList(Renderer::E_PT_TRIANGLE_STRIP, vertices, indices, 0, indices->getIndexCount());
                ++i;
            }

            ++itr;
        }
    }

    ////////////////////////////////////////////////////////////////////////////

    RenderQueuePtr RenderQueue::create()
    {
        RenderQueue *rq = new RenderQueue();
        RenderQueuePtr queue(rq);
        rq->release();
        return queue;
    }

    RenderQueue::RenderQueue()
    {

    }

    RenderQueue::~RenderQueue()
    {

    }

    void RenderQueue::addRenderable(GroupID groupID, const SGRenderablePtr &renderable)
    {
        RenderableGroupItr itr = mGroups.find(groupID);

        if (itr != mGroups.end())
        {
            /// �Ѿ���������Ⱦ����
            RenderGroupPtr &group = itr->second;
            group->addRenderable(renderable->getMaterial(), renderable);
        }
        else
        {
            /// ������������Ⱦ����
            RenderGroup *group = new RenderGroup();
            RenderGroupPtr ptr(group);
            group->release();

            group->addRenderable(renderable->getMaterial(), renderable);
            mGroups.insert(RenderableGroupValue(groupID, group));
        }
    }

    void RenderQueue::clear()
    {
        mGroups.clear();
    }

    void RenderQueue::render(const RendererPtr &renderer)
    {
        RenderableGroupItr itr = mGroups.begin();

        while (itr != mGroups.end())
        {
            itr->second->render(renderer);
            ++itr;
        }
    }
}
