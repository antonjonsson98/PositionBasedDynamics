#include "Constraints.h"
#include "PBDObject.h"
#include "Vector4D.h"
#include <cmath>

Constraint::~Constraint()
{

}

DistanceConstraint::DistanceConstraint(int i1, int i2, PBDObject* obj, float stiffness)
{
    numIndices = 2;
    indices = new int[numIndices];
    indices[0] = i1;
    indices[1] = i2;
    this->stiffness = stiffness;
    strength = 1.2f;
    oneTime = false;
    parent = obj;
    invMass1 = parent->particleList[indices[0]].invMass;
    invMass2 = parent->particleList[indices[1]].invMass;
    if (invMass1 == 0 && invMass2 == 0)
    {
        oneTime = true;
    }
    
    initialDistance = (parent->particleList[indices[0]].pos - parent->particleList[indices[1]].pos).length();
}

DistanceConstraint::~DistanceConstraint()
{
    delete[] indices;
}

void DistanceConstraint::projectConstraint(int simulationSteps)
{
    float currentDistance = (parent->projectedParticleList[indices[0]].pos - parent->projectedParticleList[indices[1]].pos).length();
    
    if ((currentDistance / initialDistance) > strength)
    {
        // Break constraint by setting it to remove after this cycle
        oneTime = true;
        return;
    }

    if (invMass1 == 0 && invMass2 == 0)
    {
        oneTime = true;
        return;
    }
    
    Vector4D corr = ((parent->projectedParticleList[indices[0]].pos - parent->projectedParticleList[indices[1]].pos) * (1 / currentDistance)) * (currentDistance - initialDistance);
    parent->projectedParticleList[indices[0]].pos = parent->projectedParticleList[indices[0]].pos + corr * -(invMass1 / (invMass1 + invMass2)) * (1 - powf(1 - stiffness, 1.0f / simulationSteps));;
    parent->projectedParticleList[indices[1]].pos = parent->projectedParticleList[indices[1]].pos + corr * (invMass2 / (invMass1 + invMass2)) * (1 - powf(1 - stiffness, 1.0f / simulationSteps));;
}

FluidDistanceConstraint::FluidDistanceConstraint(int i1, int i2, PBDObject* obj)
{
    numIndices = 2;
    indices = new int[numIndices];
    indices[0] = i1;
    indices[1] = i2;
    stiffness = 0.0005f;
    oneTime = true;
    parent = obj;
    invMass1 = parent->particleList[indices[0]].invMass;
    invMass2 = parent->particleList[indices[1]].invMass;
    
    initialDistance = parent->particleList[indices[0]].radius + parent->particleList[indices[1]].radius;
}

FluidDistanceConstraint::~FluidDistanceConstraint()
{
    delete[] indices;
}

void FluidDistanceConstraint::projectConstraint(int simulationSteps)
{
    float currentDistance = (parent->projectedParticleList[indices[0]].pos - parent->projectedParticleList[indices[1]].pos).length();
    
    Vector4D corr = ((parent->projectedParticleList[indices[0]].pos - parent->projectedParticleList[indices[1]].pos) * (1 / currentDistance)) * (currentDistance - initialDistance);
    parent->projectedParticleList[indices[0]].pos = parent->projectedParticleList[indices[0]].pos + corr * -(invMass1 / (invMass1 + invMass2)) * (1 - powf(1 - stiffness, 1.0f / simulationSteps));;
    parent->projectedParticleList[indices[1]].pos = parent->projectedParticleList[indices[1]].pos + corr * (invMass2 / (invMass1 + invMass2)) * (1 - powf(1 - stiffness, 1.0f / simulationSteps));;
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
    invMass1 = parent->particleList[indices[0]].invMass;
    invMass2 = parent2->particleList[indices[1]].invMass;
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
        Vector4D corr = ((parent->projectedParticleList[indices[0]].pos - parent2->projectedParticleList[indices[1]].pos) * (1 / currentDistance)) * (currentDistance - minDistance);
        //corr = corr * (1 - powf(1 - stiffness, 1.0f / simulationSteps));
        parent->projectedParticleList[indices[0]].pos = parent->projectedParticleList[indices[0]].pos + corr * -(invMass1 / (invMass1 + invMass2));
        parent2->projectedParticleList[indices[1]].pos = parent2->projectedParticleList[indices[1]].pos + corr * (invMass2 / (invMass1 + invMass2));
    } 
}

BoundsConstraint::BoundsConstraint(int i, PBDObject* obj)
{
    numIndices = 1;
    indices = new int[numIndices];
    indices[0] = i;
    stiffness = 1;
    oneTime = false;
    parent = obj;
    min = Vector4D(-5, -5, -5);
    max = Vector4D(5, 10, 5);
}

BoundsConstraint::~BoundsConstraint()
{
    delete[] indices;
}

void BoundsConstraint::projectConstraint(int simulationSteps)
{
    if (parent->projectedParticleList[indices[0]].pos[0] < min[0])
    {
        parent->projectedParticleList[indices[0]].pos[0] = min[0];
    }
    else if (parent->projectedParticleList[indices[0]].pos[0] > max[0])
    {
        parent->projectedParticleList[indices[0]].pos[0] = max[0];
    }

    if (parent->projectedParticleList[indices[0]].pos[1] < min[1])
    {
        parent->projectedParticleList[indices[0]].pos[1] = min[1];
    }
    else if (parent->projectedParticleList[indices[0]].pos[1] > max[1])
    {
        parent->projectedParticleList[indices[0]].pos[1] = max[1];
    }

    if (parent->projectedParticleList[indices[0]].pos[2] < min[2])
    {
        parent->projectedParticleList[indices[0]].pos[2] = min[2];
    }
    else if (parent->projectedParticleList[indices[0]].pos[2] > max[2])
    {
        parent->projectedParticleList[indices[0]].pos[2] = max[2];
    }

    
}