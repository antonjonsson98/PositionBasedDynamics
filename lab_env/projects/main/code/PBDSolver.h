#pragma once

#include "PBDObject.h"

class PBDSolver
{
public:
    PBDSolver();
    ~PBDSolver();
    void addObject(PBDObject* obj);
    void simulateTimeStep(float dt);
    void applyExternalForces(float dt);
    void dampVelocities(float dt);
    void projectPositions(float dt);
    void generateCollisionConstraints(float dt);
    void projectConstraints(float dt);
    void updateVelocities(float dt);
    void updatePositions();
    void modifyVelocities(float dt);
private:
    int solverSteps;
    std::vector<PBDObject*> objectList;
    int particleAmount = 0;
};