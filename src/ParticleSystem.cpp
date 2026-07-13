#include "ParticleSystem.hpp"
using namespace std;

bool ParticleSystem::initialize(size_t particleCount) {
    this->particleCount = particleCount;
    return true;
    // later allocate gpu mem, initilize pos, velocity, colors
}

void ParticleSystem::update(float deltaTime) {
    // launch cuda kernel update everything, handle collisions, gravity, etc.
}

void ParticleSystem::shutdown() {
    // free all allocated gpu memory
}