#pragma once

#include "Constraints.h"
#include "Particle.h"

class PBDObject
{
public:
    PBDObject();
    ~PBDObject();
    void setParticleList(Particle* list, int length);
    void draw(Matrix4D view, Matrix4D perspective, LightNode light, Vector4D cameraPos);
    void projectPositions(float dt);
    void projectConstraints(int simulationSteps);
    void updateVelocities(float dt);
    void updatePositions();
    static PBDObject* getBox(int w, int h, int d, float invDensity);
    int numParticles;
    Particle* particleList;
    Particle* projectedParticleList;
    std::vector<Constraint*> constraints;

private:
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


inline PBDObject* PBDObject::getBox(int w, int h, int d, float invDensity)
{
    PBDObject* ret = new PBDObject();

    Particle* list = new Particle[w * h * d];

    // Set position of each particle in box
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            for (int k = 0; k < d; k++)
            {
                list[k * (w*h) + j * w + i].pos = Vector4D(-invDensity * (w / 2) + invDensity * i, -invDensity * (h / 2) + invDensity * j, -invDensity * (d / 2) + invDensity * k);
            }
        }    
    }

    ret->setParticleList(list, w * h * d);
    
    // Add disance constraint to each particle in box
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            for (int k = 0; k < d; k++)
            {
                // Add width distance constraints
                if (i != w - 1)
                {
                    ret->constraints.push_back(new DistanceConstraint(k * (w*h) + j * w + i, k * (w*h) + j * w + i + 1, ret));
                }
                // Add height distance constraints
                if (j != h - 1)
                {
                    ret->constraints.push_back(new DistanceConstraint(k * (w*h) + j * w + i, k * (w*h) + (j+1) * w + i, ret));
                }
                // Add depth distance constraints
                if (k != d - 1)
                {
                    ret->constraints.push_back(new DistanceConstraint(k * (w*h) + j * w + i, (k+1) * (w*h) + j * w + i, ret));
                }
                // Add xy diagonal disance constraints
                if (i != w - 1 && j != h - 1)
                {
                    ret->constraints.push_back(new DistanceConstraint(k * (w*h) + j * w + i, k * (w*h) + (j+1) * w + i + 1, ret));
                }
                // Add xz diagonal disance constraints
                if (i != w - 1 && k != d - 1)
                {
                    ret->constraints.push_back(new DistanceConstraint(k * (w*h) + j * w + i, (k+1) * (w*h) + j * w + i + 1, ret));
                }
                // Add yz diagonal disance constraints
                if (j != h - 1 && k != d - 1)
                {
                    ret->constraints.push_back(new DistanceConstraint(k * (w*h) + j * w + i, (k+1) * (w*h) + (j+1) * w + i, ret));
                }
                // Add xyz diagonal disance constraints
                if (i != w - 1 && j != h - 1 && k != d - 1)
                {
                    ret->constraints.push_back(new DistanceConstraint(k * (w*h) + j * w + i, (k+1) * (w*h) + (j+1) * w + i + 1, ret));
                }
                
            }
        }    
    }
    

    ret->particleList[0].vel = Vector4D(100, 0, 0);

    return ret;
}