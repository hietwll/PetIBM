#if !defined(CARTESIAN_MESH_H)
#define CARTESIAN_MESH_H

#include <petscsys.h>
#include <string>
#include <vector>

class CartesianMesh
{
public:
	PetscInt               nx, ny, nz;
	std::vector<PetscReal> x, y, z;
	std::vector<PetscReal> dx, dy, dz;
    
    CartesianMesh();
	CartesianMesh(std::string fileName);
};

#endif
