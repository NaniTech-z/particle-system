#pragma once
using namespace std;

class ParticleSystem {
    public:
        bool initialize(size_t particleCount);
        void update(float deltaTime);
        void shutdown();

    private:
        size_t particleCount = 0;
};