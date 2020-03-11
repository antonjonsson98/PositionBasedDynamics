#pragma once

#include "PBDObject.h"

class FluidObject : public PBDObject
{
public:
    FluidObject(Vector4D pos, int w, int h, int d, float invDensity, float weight);
    ~FluidObject();
};

inline FluidObject::FluidObject(Vector4D pos, int w, int h, int d, float invDensity, float weight)
{
    isFluid = true;

    float individualInvMass = (w * h * d) / weight;

    Particle* list = new Particle[w * h * d];

    // Set position of each particle in box
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            for (int k = 0; k < d; k++)
            {
                list[k * (w*h) + j * w + i].pos = pos + Vector4D(-invDensity * (w / 2.0f) + invDensity * i, -invDensity * (h / 2.0f) + invDensity * j, -invDensity * (d / 2.0f) + invDensity * k);
                list[k * (w*h) + j * w + i].invMass = individualInvMass;
            }
        }    
    }

    setParticleList(list, w * h * d);
    
    // Add bounds constraint
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            for (int k = 0; k < d; k++)
            {
                constraints.push_back(new BoundsConstraint(k * (w*h) + j * w + i, this));
            }
        }    
    }
}

inline FluidObject::~FluidObject()
{
    delete[] particleList;
}