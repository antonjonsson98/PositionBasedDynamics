class PBDSolver
{
public:
    PBDSolver();
    ~PBDSolver();
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
};

PBDSolver::PBDSolver()
{
    solverSteps = 5;
}

PBDSolver::~PBDSolver()
{
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

}

void PBDSolver::generateCollisionConstraints(float dt)
{

}

void PBDSolver::projectConstraints(float dt)
{

}

void PBDSolver::updateVelocities(float dt)
{

}

void PBDSolver::updatePositions()
{

}

void PBDSolver::modifyVelocities(float dt)
{

}