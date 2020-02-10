#pragma once

#include "Particle.h"

class PBDObject
{
public:
    PBDObject();
    ~PBDObject();
    void setParticleList(Particle* list, int length);
    void draw(Matrix4D view, Matrix4D perspective, LightNode light, Vector4D cameraPos);
    static PBDObject getBox(int w, int h, int d, float invDensity);

private:
    Particle* particleList;
    int numParticles;
};

inline PBDObject::PBDObject()
{
}

inline PBDObject::~PBDObject()
{
}

inline void PBDObject::setParticleList(Particle* list, int length)
{
    if (particleList)
    {
        delete[] particleList;
    }
    
    particleList = list;
    numParticles = length;
}

inline void PBDObject::draw(Matrix4D view, Matrix4D perspective, LightNode light, Vector4D cameraPos)
{
    for (int i = 0; i < numParticles; i++)
    {
        particleList[i].draw(view, perspective, light, cameraPos);
    }
}

inline PBDObject PBDObject::getBox(int w, int h, int d, float invDensity)
{
    PBDObject ret = PBDObject();

    Particle* list = new Particle[w * h * d];

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

    ret.setParticleList(list, w * h * d);

    return ret;
}