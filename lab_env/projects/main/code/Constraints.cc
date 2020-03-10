#include "Constraints.h"
#include "PBDObject.h"
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

HeightConstraint::HeightConstraint(int i, PBDObject* obj, float height)
{
    numIndices = 1;
    indices = new int[numIndices];
    indices[0] = i;
    stiffness = 1;
    oneTime = false;
    parent = obj;
    this->height = height;
}

HeightConstraint::~HeightConstraint()
{
    delete[] indices;
}

void HeightConstraint::projectConstraint(int simulationSteps)
{
    if (parent->projectedParticleList[indices[0]].pos[1] < height)
    {
        parent->projectedParticleList[indices[0]].pos[1] = height;
    } 
}