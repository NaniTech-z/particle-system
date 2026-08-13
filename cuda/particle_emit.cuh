#pragma once

__global__ void initializeParticles(float3* positions, float3* velocities, int particleCount);

void launchInitializeParticles(float3* positions, float3* velocities, size_t particleCount);