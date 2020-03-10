#pragma once

#include "PBDObject.h"

class ClothObject : public PBDObject
{
public:
    ClothObject(Vector4D pos, int w, int h, int d, float invDensity, float weight, float stiffness);
    ~ClothObject();
private:

};

inline ClothObject::ClothObject(Vector4D pos, int w, int h, int d, float invDensity, float weight, float stiffness)
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
                list[k * (w*h) + j * w + i].pos = pos + Vector4D(-invDensity * (w / 2.0f) + invDensity * i, -invDensity * (h / 2.0f) + invDensity * j, -invDensity * (d / 2.0f) + invDensity * k);
                if (j == h - 1)
                {
                    list[k * (w*h) + j * w + i].invMass = 0;
                }
                else
                {
                    list[k * (w*h) + j * w + i].invMass = individualInvMass;
                }
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
                    constraints.push_back(new DistanceConstraint(k * (w*h) + j * w + i, k * (w*h) + j * w + i + 1, this, stiffness));
                }
                // Add height distance constraints
                if (j != h - 1)
                {
                    constraints.push_back(new DistanceConstraint(k * (w*h) + j * w + i, k * (w*h) + (j+1) * w + i, this, stiffness));
                }
                // Add depth distance constraints
                if (k != d - 1)
                {
                    constraints.push_back(new DistanceConstraint(k * (w*h) + j * w + i, (k+1) * (w*h) + j * w + i, this, stiffness));
                }
                // Add xy diagonal disance constraints
                if (i != w - 1 && j != h - 1)
                {
                    constraints.push_back(new DistanceConstraint(k * (w*h) + j * w + i, k * (w*h) + (j+1) * w + i + 1, this, stiffness));
                }
                // Add xz diagonal disance constraints
                if (i != w - 1 && k != d - 1)
                {
                    constraints.push_back(new DistanceConstraint(k * (w*h) + j * w + i, (k+1) * (w*h) + j * w + i + 1, this, stiffness));
                }
                // Add yz diagonal disance constraints
                if (j != h - 1 && k != d - 1)
                {
                    constraints.push_back(new DistanceConstraint(k * (w*h) + j * w + i, (k+1) * (w*h) + (j+1) * w + i, this, stiffness));
                }
                // Add xyz diagonal disance constraints
                if (i != w - 1 && j != h - 1 && k != d - 1)
                {
                    constraints.push_back(new DistanceConstraint(k * (w*h) + j * w + i, (k+1) * (w*h) + (j+1) * w + i + 1, this, stiffness));
                }

                constraints.push_back(new BoundsConstraint(k * (w*h) + j * w + i, this));
            }
        }    
    }
}

inline ClothObject::~ClothObject()
{
    delete[] particleList;
}
