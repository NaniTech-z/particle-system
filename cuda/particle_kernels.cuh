#pragma once

__global__ void updateParticles (float3* positions, float3* velocities, float deltaTime, size_t particleCount);

void launchUpdateParticles(float3* positions, float3* velocities, float deltaTime, size_t particleCount);
