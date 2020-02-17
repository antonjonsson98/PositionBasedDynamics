#pragma once

class PBDObject;

class Constraint
{
public:
    virtual void projectConstraint(int simulationSteps) = 0;
    virtual ~Constraint();
    // Bool that determines if constraint should be removed at the end of solver cycle
    bool oneTime;
protected:
    int numIndices;
    int* indices;
    float stiffness; 
    PBDObject* parent;
};

class DistanceConstraint : public Constraint
{
public:
    DistanceConstraint(int i1, int i2, PBDObject* obj);
    ~DistanceConstraint();
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