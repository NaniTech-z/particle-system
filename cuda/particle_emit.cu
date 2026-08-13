#include "particle_emit.cuh"

__global__ void initializeParticles(float3* positions, float3* velocities, size_t particleCount) {
    int index = blockIdx.x * blockDim.x + threadIdx.x;

    if (index >= particleCount)
        return;
    
    float x = (index % 50) * 0.02f - 0.5f;
    float y = (index / 50) * 0.02f - 0.2f;

    positions[index] = make_float3(x, y, 0.0f);

    velocities[index] = make_float3(0.0f, 0.0f, 0.0f);
}

void launchInitializeParticles(float3* positions, float3* velocities, size_t particleCount) {
    constexpr int blockSize = 256;

    int gridSize = static_cast<int>((particleCount + blockSize-1) / blockSize);

    initializeParticles<<<gridSize, blockSize>>>(positions, velocities, particleCount);
}