#include "Constraints.h"
#include "PBDObject.h"
#include <cmath>

DistanceConstraint::DistanceConstraint(int i1, int i2, PBDObject* obj)
{
    numIndices = 2;
    indices = new int[numIndices];
    indices[0] = i1;
    indices[1] = i2;
    stiffness = 0.5f;
    equality = true;
    parent = obj;
    invMass1 = 1 / parent->particleList[indices[0]].mass;
    invMass2 = 1 / parent->particleList[indices[1]].mass;
    initialDistance = (parent->particleList[indices[0]].pos - parent->particleList[indices[1]].pos).length();
}

DistanceConstraint::~DistanceConstraint()
{
    delete[] indices;
}

void DistanceConstraint::projectConstraint(int simulationSteps)
{
    float currentDistance = (parent->projectedParticleList[indices[0]].pos - parent->projectedParticleList[indices[1]].pos).length();
    Vector4D corr = ((parent->projectedParticleList[indices[0]].pos - parent->projectedParticleList[indices[1]].pos) * (1 / currentDistance)) * -(invMass1 / (invMass1 + invMass2)) * (currentDistance - initialDistance);
    corr = corr * (1 - powf(1 - stiffness, 1 / simulationSteps));
    parent->projectedParticleList[indices[0]].pos = parent->projectedParticleList[indices[0]].pos + corr;
    parent->projectedParticleList[indices[0]].pos = parent->projectedParticleList[indices[0]].pos - corr;
}