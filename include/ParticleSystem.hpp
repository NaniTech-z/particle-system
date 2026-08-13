#pragma once
#include <cuda_runtime.h>
using namespace std;

class ParticleSystem {
    public:
        bool initialize(size_t particleCount);
        void initializePositions(float3* positions);
        void update(float3* positions, float deltaTime);
        void shutdown();

        float3* getPositions();
        size_t getParticleCount() const;

    private:
        size_t particleCount = 0;
        float3* velocities = nullptr;
};