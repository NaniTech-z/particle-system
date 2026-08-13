#include "particle_kernels.cuh"
#include <cuda_runtime.h>

__global__ void updateParticles(float3* positions, float3* velocities, float deltaTime, size_t particleCount) {
    int index = blockIdx.x * blockDim.x + threadIdx.x; // get index for each particle 

    if (index >= particleCount)
        return;
    
    const float gravity = -0.5f;
    // change y velocity due to gravity
    velocities[index].y += gravity * deltaTime;

    // change the positions over time with velocity
    positions[index].x += velocities[index].x * deltaTime;
    positions[index].y += velocities[index].y * deltaTime;

    // create a boundary so the particles don't go off screen
    if (positions[index].y < -1.0f) {

        positions[index].y = -1.0f;
        
        // Multiply by -0.8f because it is the coefficient of restitution 
        // In other words it makes the particle bounce off the ground and slowly settles
        velocities[index].y *= -0.8f;
    }
};

void launchUpdateParticles(float3* positions, float3* velocities, float deltaTime, size_t particleCount) {
    constexpr int blockSize = 256;

    // using 256 threads per block need to round up.
    int gridSize = static_cast<int>((particleCount + blockSize - 1) / blockSize); 

    // call the kernel
    updateParticles<<<gridSize, blockSize>>>(positions, velocities, deltaTime, particleCount);
};