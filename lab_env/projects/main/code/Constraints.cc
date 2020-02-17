#include "Constraints.h"
#include "PBDObject.h"
#include <cmath>

Constraint::~Constraint()
{

}

DistanceConstraint::DistanceConstraint(int i1, int i2, PBDObject* obj)
{
    numIndices = 2;
    indices = new int[numIndices];
    indices[0] = i1;
    indices[1] = i2;
    stiffness = 0.7f;
    oneTime = false;
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
    corr = corr * (1 - powf(1 - stiffness, 1.0f / simulationSteps));
    parent->projectedParticleList[indices[0]].pos = parent->projectedParticleList[indices[0]].pos + corr;
    parent->projectedParticleList[indices[1]].pos = parent->projectedParticleList[indices[1]].pos - corr;
}

CollisionConstraint::CollisionConstraint(int i1, int i2, PBDObject* obj1, PBDObject* obj2)
{
    numIndices = 2;
    indices = new int[numIndices];
    indices[0] = i1;
    indices[1] = i2;
    stiffness = 1;
    oneTime = true;
    parent = obj1;
    parent2 = obj2;
    invMass1 = 1 / parent->particleList[indices[0]].mass;
    invMass2 = 1 / parent2->particleList[indices[1]].mass;
    minDistance = parent->particleList[indices[0]].radius + parent2->particleList[indices[1]].radius;
}

CollisionConstraint::~CollisionConstraint()
{
    delete[] indices;
}

void CollisionConstraint::projectConstraint(int simulationSteps)
{
    float currentDistance = (parent->projectedParticleList[indices[0]].pos - parent2->projectedParticleList[indices[1]].pos).length();
    if (currentDistance < minDistance)
    {
        Vector4D corr = ((parent->projectedParticleList[indices[0]].pos - parent2->projectedParticleList[indices[1]].pos) * (1 / currentDistance)) * -(invMass1 / (invMass1 + invMass2)) * (currentDistance - minDistance);
        //corr = corr * (1 - powf(1 - stiffness, 1.0f / simulationSteps));
        parent->projectedParticleList[indices[0]].pos = parent->projectedParticleList[indices[0]].pos + corr;
        parent2->projectedParticleList[indices[1]].pos = parent2->projectedParticleList[indices[1]].pos - corr;
    } 
}