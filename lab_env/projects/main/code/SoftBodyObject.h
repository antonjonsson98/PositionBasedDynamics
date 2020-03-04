#pragma once

#include "PBDObject.h"

class SoftBodyObject : public PBDObject
{
public:
    SoftBodyObject(Vector4D pos, int w, int h, int d, float invDensity, float weight, float stiffness);
    ~SoftBodyObject();
private:

};

inline SoftBodyObject::SoftBodyObject(Vector4D pos, int w, int h, int d, float invDensity, float weight, float stiffness)
{
    float individualInvMass = (w * h * d) / weight;

    Particle* list = new Particle[w * h * d];

    // Set position of each particle in box
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            for (int k = 0; k < d; k++)
            {
                list[k * (w*h) + j * w + i].pos = pos + Vector4D(-invDensity * (w / 2) + invDensity * i, -invDensity * (h / 2) + invDensity * j, -invDensity * (d / 2) + invDensity * k);
                list[k * (w*h) + j * w + i].invMass = individualInvMass;
            }
        }    
    }

    setParticleList(list, w * h * d);
    
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
                    constraints.push_back(new DistanceConstraint(k * (w*h) + j * w + i, k * (w*h) + j * w + i + 1, this));
                }
                // Add height distance constraints
                if (j != h - 1)
                {
                    constraints.push_back(new DistanceConstraint(k * (w*h) + j * w + i, k * (w*h) + (j+1) * w + i, this));
                }
                // Add depth distance constraints
                if (k != d - 1)
                {
                    constraints.push_back(new DistanceConstraint(k * (w*h) + j * w + i, (k+1) * (w*h) + j * w + i, this));
                }
                // Add xy diagonal disance constraints
                if (i != w - 1 && j != h - 1)
                {
                    constraints.push_back(new DistanceConstraint(k * (w*h) + j * w + i, k * (w*h) + (j+1) * w + i + 1, this));
                }
                // Add xz diagonal disance constraints
                if (i != w - 1 && k != d - 1)
                {
                    constraints.push_back(new DistanceConstraint(k * (w*h) + j * w + i, (k+1) * (w*h) + j * w + i + 1, this));
                }
                // Add yz diagonal disance constraints
                if (j != h - 1 && k != d - 1)
                {
                    constraints.push_back(new DistanceConstraint(k * (w*h) + j * w + i, (k+1) * (w*h) + (j+1) * w + i, this));
                }
                // Add xyz diagonal disance constraints
                if (i != w - 1 && j != h - 1 && k != d - 1)
                {
                    constraints.push_back(new DistanceConstraint(k * (w*h) + j * w + i, (k+1) * (w*h) + (j+1) * w + i + 1, this));
                }
            }
        }    
    }
}

inline SoftBodyObject::~SoftBodyObject()
{
    delete[] particleList;
}
