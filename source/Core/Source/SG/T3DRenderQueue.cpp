

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
                const Matrix4 &m = (*i)->getWorldMatrix();
                renderer->setWorldTransform(m);

                VertexDataPtr vertexData =(*i)->getVertexData();
                IndexDataPtr indexData = (*i)->getIndexData();

                Renderer::PrimitiveType priType = (*i)->getPrimitiveType();

                size_t primitiveCount = calcPrimitiveCount(priType, 
                    indexData->getIndexBuffer()->getIndexCount(), 
                    vertexData->getVertexBuffer()->getVertexCount(),
                    true);

                renderer->drawIndexList(priType, vertexData, indexData, 0, primitiveCount);
                ++i;
            }

            ++itr;
        }
    }

    size_t RenderGroup::calcPrimitiveCount(Renderer::PrimitiveType priType, size_t indexCount, size_t vertexCount, bool useIndex)
    {
        size_t primCount = 0;
        switch (priType)
        {
        case Renderer::E_PT_POINT_LIST:
            primCount = (useIndex ? indexCount : vertexCount);
            break;

        case Renderer::E_PT_LINE_LIST:
            primCount = (useIndex ? indexCount : vertexCount) / 2;
            break;

        case Renderer::E_PT_LINE_STRIP:
            primCount = (useIndex ? indexCount : vertexCount) - 1;
            break;

        case Renderer::E_PT_TRIANGLE_LIST:
            primCount = (useIndex ? indexCount : vertexCount) / 3;
            break;

        case Renderer::E_PT_TRIANGLE_STRIP:
            primCount = (useIndex ? indexCount : vertexCount) - 2;
            break;

        case Renderer::E_PT_TRIANGLE_FAN:
            primCount = (useIndex ? indexCount : vertexCount) - 2;
            break;
        }

        return primCount;
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
