#pragma once

#include "Constraints.h"
#include "Particle.h"

class PBDObject
{
public:
    PBDObject();
    virtual ~PBDObject();
    void setParticleList(Particle* list, int length);
    void draw(Matrix4D view, Matrix4D perspective, LightNode light, Vector4D cameraPos);
    void projectPositions(float dt);
    void projectConstraints(int simulationSteps);
    void deleteOneTimeConstraints();
    void updateVelocities(float dt);
    void updatePositions();
    void addForce(Vector4D force);
    void applyForces(float dt);
    int numParticles;
    Particle* particleList;
    Particle* projectedParticleList;
    std::vector<Constraint*> constraints;
    // True if object is affected by gravity
    bool gravity = true;
    static PBDObject* getBox(Vector4D pos, int w, int h, int d, float invDensity);

protected:
    // Forces to be applied next solver iteration
    std::vector<Vector4D> forceList;
};

inline PBDObject::PBDObject()
{
}

inline PBDObject::~PBDObject()
{
}

inline void PBDObject::setParticleList(Particle* list, int length)
{   
    numParticles = length;
    particleList = list;
    projectedParticleList = new Particle[numParticles];
    memcpy(projectedParticleList, particleList, sizeof(Particle) * numParticles);
}

inline void PBDObject::draw(Matrix4D view, Matrix4D perspective, LightNode light, Vector4D cameraPos)
{
    for (int i = 0; i < numParticles; i++)
    {
        particleList[i].draw(view, perspective, light, cameraPos);
    }
}

inline void PBDObject::projectPositions(float dt)
{
    for (int i = 0; i < numParticles; i++)
    {
        projectedParticleList[i].pos = particleList[i].pos + particleList[i].vel * dt;
    }
}

inline void PBDObject::projectConstraints(int simulationSteps)
{
    for (int i = 0; i < constraints.size(); i++)
    {
        constraints[i]->projectConstraint(simulationSteps);
    }
}

inline void PBDObject::deleteOneTimeConstraints()
{
    for (int i = constraints.size() - 1; i >= 0; i--)
    {
        if (constraints[i]->oneTime)
        {
            delete constraints[i];
            constraints.erase(constraints.begin() + i);
        }
    }
}

inline void PBDObject::updateVelocities(float dt)
{
    for (int i = 0; i < numParticles; i++)
    {
        particleList[i].vel = (projectedParticleList[i].pos - particleList[i].pos) * (1 / dt);
    }
}

inline void PBDObject::updatePositions()
{
    for (int i = 0; i < numParticles; i++)
    {
        particleList[i].pos = projectedParticleList[i].pos;
    }
}

inline void PBDObject::addForce(Vector4D force)
{
    forceList.push_back(force);
}

inline void PBDObject::applyForces(float dt)
{
    for (int i = 0; i < forceList.size(); i++)
    {
        for (int j = 0; j < numParticles; j++)
        {
            particleList[j].vel = particleList[j].vel + (forceList[i] * particleList[j].invMass) * dt;
        }
    }
    forceList.clear();
}