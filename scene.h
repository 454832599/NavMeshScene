#ifndef __NMS_SCENE_H__
#define __NMS_SCENE_H__

#include <memory>
#include <unordered_map>

namespace NavMeshScene {

    class Agent;
    class Detour;
    class Filter;

    class Scene {
    public:

        Scene(bool bStatic);
        virtual ~Scene();

        int Load(const char* path);
        void Simulation(float delta);
        void AddAgent(uint64_t id, const std::shared_ptr<Agent>& agent);
        void RemoveAgent(uint64_t id);

    public:
        inline Detour& GetDetour() { return *mDetour; }
        inline Filter& GetDefaultFilter() { return *mDefaultFilter; }

    protected:
        std::unique_ptr<Detour> mDetour;
        std::unordered_map<uint64_t, std::shared_ptr<Agent>> mAgents;
        std::unique_ptr<Filter> mDefaultFilter;
    };

    class StaticScene : public Scene {
    public:
        StaticScene() : Scene(true) {}
        virtual ~StaticScene() {}
    };

    class DynamicScene :public Scene {
    public:
        DynamicScene(int heightMode = HEIGHT_MODE_1);
        virtual ~DynamicScene();

        enum {
            HEIGHT_MODE_1 = 1,   // ԭʼ�ģ����Ȳ��Ǻܸߣ�����û�������ġ�
            HEIGHT_MODE_2 = 2,   // ͨ��������StaticScene�ϣ���ȡ��ȷ�߶�ֵ��
            HEIGHT_MODE_3 = 3,   // DynamicScene����ʱ���Լ����η����仯ʱ����������`��ȷ�߶���Ϣ`
        };

        unsigned int AddCapsuleObstacle(const float pos[3], const float radius, const float height);
        unsigned int AddBoxObstacle(const float bmin[3], const float bmax[3]);
        unsigned int AddBoxObstacle(const float center[3], const float halfExtents[3], const float yRadians);
        void RemoveObstacle(unsigned int obstacleId);
    };
}

#endif