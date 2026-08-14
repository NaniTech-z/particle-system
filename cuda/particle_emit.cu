#include "particle_emit.cuh"

__global__ void initializeParticles(float3* positions, float3* velocities, size_t particleCount) {
    int index = blockIdx.x * blockDim.x + threadIdx.x;

    if (index >= particleCount)
        return;
    
    // creating initial positions for each particle
    float x = ((index % 20) * 0.02f) - 0.2f;
    float y = ((index / 20) * 0.02f) + 0.2f;

    positions[index] = make_float3(x, y, 0.0f);

    // randomizing initial velocities
    float vx = ((index % 10) - 5) * 0.1f;
    float vy = ((index % 7) - 3) * 0.15f;
    float vz = ((index % 5) - 2) * 0.1f;

    velocities[index] = make_float3(vx, vy, vz);
}

void launchInitializeParticles(float3* positions, float3* velocities, size_t particleCount) {
    constexpr int blockSize = 256;

    int gridSize = static_cast<int>((particleCount + blockSize-1) / blockSize);

    initializeParticles<<<gridSize, blockSize>>>(positions, velocities, particleCount);
}