#include "PBDSolver.h"

PBDSolver::PBDSolver()
{
    solverSteps = 2;
}

PBDSolver::~PBDSolver()
{
}

void PBDSolver::addObject(PBDObject* obj)
{
    particleAmount += obj->numParticles;
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
    for (int i = 0; i < objectList.size(); i++)
    {
        objectList[i]->applyForces(dt);
        
        if (objectList[i]->gravity)
        {
            objectList[i]->applyGravity(dt);
        }
    }
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
    for (int i = 0; i < objectList.size(); i++)
    {
        for (int j = i; j < objectList.size(); j++)
        {
            for (int k = 0; k < objectList[i]->numParticles; k++)
            {
                for (int l = 0; l < objectList[j]->numParticles; l++)
                {
                    if (i == j && k == l)
                    {
                        continue;
                    }
                    
                    if ((objectList[i]->particleList[k].pos - objectList[j]->particleList[l].pos).length() < objectList[i]->particleList[k].radius + objectList[j]->particleList[l].radius)
                    {
                        objectList[i]->constraints.push_back(new CollisionConstraint(k, l, objectList[i], objectList[j]));
                    }
                    

                }
                
            }
            
        }
        
    }
    
}

void PBDSolver::projectConstraints(float dt)
{
    for (int i = 0; i < solverSteps; i++)
    {
        for (int j = 0; j < objectList.size(); j++)
        {
            objectList[j]->projectConstraints(solverSteps);
        }
    }

    for (int i = 0; i < objectList.size(); i++)
    {
            objectList[i]->deleteOneTimeConstraints();
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