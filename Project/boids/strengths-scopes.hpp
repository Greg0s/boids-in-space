#pragma once

struct strengths {
    const float boundsStrength     = 1;
    float       separationStrength = 0.04;
    float       alignementStrength = 0.03;
    float       cohesionStrength   = 0.01;
};

struct scopes {
    float       scope     = 0.2;
    const float wallScope = 0.1;
};