#include "PBDSolver.h"

PBDSolver::PBDSolver()
{
    solverSteps = 1;
}

PBDSolver::~PBDSolver()
{
}

void PBDSolver::addObject(PBDObject* obj)
{
    objectList.push_back(obj);
}

void PBDSolver::simulateTimeStep(float dt)
{
    applyExternalForces(dt);
    dampVelocities(dt);
    projectPositions(dt);
    generateCollisionConstraints(dt);
    projectConstraints(dt);
    updateVelocities(dt);
    updatePositions();
    modifyVelocities(dt);
}

void PBDSolver::applyExternalForces(float dt)
{

}

void PBDSolver::dampVelocities(float dt)
{

}

void PBDSolver::projectPositions(float dt)
{
    for (int i = 0; i < objectList.size(); i++)
    {
        objectList[i]->projectPositions(dt);
    }
}

void PBDSolver::generateCollisionConstraints(float dt)
{

}

void PBDSolver::projectConstraints(float dt)
{
    for (int i = 0; i < solverSteps; i++)
    {
        for (int i = 0; i < objectList.size(); i++)
        {
            objectList[i]->projectConstraints(solverSteps);
        }
    }
}

void PBDSolver::updateVelocities(float dt)
{
    for (int i = 0; i < objectList.size(); i++)
    {
        objectList[i]->updateVelocities(dt);
    }
}

void PBDSolver::updatePositions()
{
    for (int i = 0; i < objectList.size(); i++)
    {
        objectList[i]->updatePositions();
    }
}

void PBDSolver::modifyVelocities(float dt)
{

}