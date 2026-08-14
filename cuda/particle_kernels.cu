#include "particle_kernels.cuh"
#include <cuda_runtime.h>

__global__ void updateParticles(float3* positions, float3* velocities, float deltaTime, size_t particleCount) {
    int index = blockIdx.x * blockDim.x + threadIdx.x; // get index for each particle 

    if (index >= particleCount)
        return;
    
    // physics constants
    const float gravity = -1.0f;
    const float restitution = 0.7f;
    const float drag = 0.05f;
    const float friction = 0.8f;
    const float floorY = -0.5f;

    // Apply gravity
    velocities[index].y += gravity * deltaTime;

    // Apply air drag
    velocities[index].x -= velocities[index].x * drag * deltaTime;
    velocities[index].y -= velocities[index].y * drag * deltaTime;
    velocities[index].z -= velocities[index].z * drag * deltaTime;

    // Update the positions
    positions[index].x += velocities[index].x * deltaTime;
    positions[index].y += velocities[index].y * deltaTime;
    positions[index].z += velocities[index].z * deltaTime;

    // Handle floor collision
    if (positions[index].y < floorY) {
        positions[index].y = floorY;

        // Bounce off the floor
        velocities[index].y *= -restitution;

        // add friction
        velocities[index].x *= friction;
        velocities[index].z *= friction;
    }
};

void launchUpdateParticles(float3* positions, float3* velocities, float deltaTime, size_t particleCount) {
    constexpr int blockSize = 256;

    // using 256 threads per block need to round up.
    int gridSize = static_cast<int>((particleCount + blockSize - 1) / blockSize); 

    // call the kernel
    updateParticles<<<gridSize, blockSize>>>(positions, velocities, deltaTime, particleCount);
};