class PBDObject;

class Constraint
{
public:
    Constraint();
    ~Constraint();
    virtual void projectConstraint(int simulationSteps) = 0;
protected:
    int numIndices;
    int* indices;
    float stiffness;
    bool equality;
    PBDObject* parent;
};

class DistanceConstraint : Constraint
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