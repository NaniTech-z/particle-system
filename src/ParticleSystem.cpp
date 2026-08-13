#include "ParticleSystem.hpp"
#include "particle_emit.cuh"
#include "particle_kernels.cuh"

#include <cuda_runtime.h>
#include <iostream>
using namespace std;

bool ParticleSystem::initialize(size_t particleCount) {
    
    this->particleCount = particleCount;

    cudaError_t error;

    // allocate the velocities
    error = cudaMalloc(&velocities, particleCount * sizeof(float3));

    if (error != cudaSuccess) {
        cerr << "Error: Cannot allocate velocities: " << cudaGetErrorString(error) << '\n';

        // velocities cannot be allocated so change to nullptr
        
        velocities = nullptr;

        return false;
    }

    return true;
}
// function launch cuda kernel update everything, handle collisions, gravity, etc.
void ParticleSystem::update(float3* positions, float deltaTime) {
    launchUpdateParticles(positions, velocities, deltaTime, particleCount);

}

// free all allocated gpu memory and set particleCount to 0
void ParticleSystem::shutdown() {

    if (velocities != nullptr){
        cudaFree(velocities);
        velocities = nullptr;
    }

    particleCount = 0;
}

size_t ParticleSystem::getParticleCount() const{
    return particleCount;
}

void ParticleSystem::initializePositions(float3* positions) {
    launchInitializeParticles(positions, velocities, particleCount);
}