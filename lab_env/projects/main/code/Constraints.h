#pragma once

#include "Vector4D.h"

class PBDObject;

class Constraint
{
public:
    virtual void projectConstraint(int simulationSteps) = 0;
    virtual ~Constraint();
    // Bool that determines if constraint should be removed at the end of solver cycle
    bool oneTime;
protected:
    float stiffness; 
    int numIndices;
    int* indices;
    PBDObject* parent;
};

class DistanceConstraint : public Constraint
{
public:
    DistanceConstraint(int i1, int i2, PBDObject* obj, float stiffness);
    ~DistanceConstraint();
    void projectConstraint(int simulationSteps);
private:
    float invMass1;
    float invMass2;
    float initialDistance;
    // Strength indicates to how much of original distance stretching is allowed before breaking
    float strength;
};

class FluidDistanceConstraint : public Constraint
{
public:
    FluidDistanceConstraint(int i1, int i2, PBDObject* obj);
    ~FluidDistanceConstraint();
    void projectConstraint(int simulationSteps);
private:
    float invMass1;
    float invMass2;
    float initialDistance;
};

class CollisionConstraint : public Constraint
{
public:
    CollisionConstraint(int i1, int i2, PBDObject* obj1, PBDObject* obj2);
    ~CollisionConstraint();
    void projectConstraint(int simulationSteps);
private:
    PBDObject* parent2;
    float invMass1;
    float invMass2;
    float minDistance;
};

class BoundsConstraint : public Constraint
{
public:
    BoundsConstraint(int i, PBDObject* obj);
    ~BoundsConstraint();
    void projectConstraint(int simulationSteps);
private:
    Vector4D min;
    Vector4D max;
};

