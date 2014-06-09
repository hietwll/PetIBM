#include <sys/stat.h>
#include <sstream>
#include <iomanip>

template <>
void NavierStokesSolver<2>::writeData(std::string caseFolder)
{
	PetscErrorCode  ierr;
	PetscInt        rank;

	MPI_Comm_rank(PETSC_COMM_WORLD, &rank);

	if(rank==0)
	{
		PetscInt its1, its2;
		std::string filename = caseFolder + "/iterationCount.txt";
		if(timeStep==1)
			iterationsFile.open(filename.c_str());
		else	
			iterationsFile.open(filename.c_str(), std::ios::out | std::ios::app);
		ierr = KSPGetIterationNumber(ksp1, &its1); CHKERRV(ierr);
		ierr = KSPGetIterationNumber(ksp2, &its2); CHKERRV(ierr);
		iterationsFile << timeStep << '\t' << its1 << '\t' << its2 << std::endl;
		iterationsFile.close();
	}

	if(timeStep%simParams->nsave == 0)
	{
		Vec             qxGlobal, qyGlobal;
		std::string     savePointDir, fileName;
		PetscViewer     viewer;
		
		// create output folder
		std::stringstream ss;
		ss << caseFolder << "/" << std::setfill('0') << std::setw(7) << timeStep;
		savePointDir = ss.str();
		
		mkdir(savePointDir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		
		ierr = DMCompositeGetAccess(qPack, q, &qxGlobal, &qyGlobal); CHKERRV(ierr);
		
		// print qx to file
		ss.str("");
		ss.clear();
		ss << savePointDir << "/qx.dat";
		fileName = ss.str();
		ierr = PetscViewerBinaryOpen(PETSC_COMM_WORLD, fileName.c_str(), FILE_MODE_WRITE, &viewer); CHKERRV(ierr);
		ierr = VecView(qxGlobal, viewer); CHKERRV(ierr);
		ierr = PetscViewerDestroy(&viewer); CHKERRV(ierr);

		// print qx to file
		ss.str("");
		ss.clear();
		ss << savePointDir << "/qy.dat";
		fileName = ss.str();
		ierr = PetscViewerBinaryOpen(PETSC_COMM_WORLD, fileName.c_str(), FILE_MODE_WRITE, &viewer); CHKERRV(ierr);
		ierr = VecView(qyGlobal, viewer); CHKERRV(ierr);
		ierr = PetscViewerDestroy(&viewer); CHKERRV(ierr);

		ierr = PetscPrintf(PETSC_COMM_WORLD, "Data written to folder %s.\n", savePointDir.c_str()); CHKERRV(ierr);
		
		ierr = DMCompositeRestoreAccess(qPack, q, &qxGlobal, &qyGlobal); CHKERRV(ierr);
	}
}

template <>
void NavierStokesSolver<3>::writeData(std::string caseFolder)
{
	PetscErrorCode  ierr;
	PetscInt        rank;

	MPI_Comm_rank(PETSC_COMM_WORLD, &rank);

	if(rank==0)
	{
		PetscInt its1, its2;
		std::string filename = caseFolder + "/iterationCount";
		if(timeStep==1)
			iterationsFile.open(filename.c_str());
		else	
			iterationsFile.open(filename.c_str(), std::ios::out | std::ios::app);
		ierr = KSPGetIterationNumber(ksp1, &its1); CHKERRV(ierr);
		ierr = KSPGetIterationNumber(ksp2, &its2); CHKERRV(ierr);
		iterationsFile << timeStep << '\t' << its1 << '\t' << its2 << std::endl;
		iterationsFile.close();
	}

	if(timeStep%simParams->nsave == 0)
	{
		Vec             qxGlobal, qyGlobal, qzGlobal;
		std::string     savePointDir, fileName;
		PetscViewer     viewer;

		// create output folder
		std::stringstream ss;
		ss << caseFolder << "/" << std::setfill('0') << std::setw(7) << timeStep;
		savePointDir = ss.str();
		
		mkdir(savePointDir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		
		ierr = DMCompositeGetAccess(qPack, q, &qxGlobal, &qyGlobal, &qzGlobal); CHKERRV(ierr);
		
		// print qx to file
		ss.str("");
		ss.clear();
		ss << savePointDir << "/qx.dat";
		fileName = ss.str();
		ierr = PetscViewerBinaryOpen(PETSC_COMM_WORLD, fileName.c_str(), FILE_MODE_WRITE, &viewer); CHKERRV(ierr);
		ierr = VecView(qxGlobal, viewer); CHKERRV(ierr);
		ierr = PetscViewerDestroy(&viewer); CHKERRV(ierr);

		// print qy to file
		ss.str("");
		ss.clear();
		ss << savePointDir << "/qy.dat";
		fileName = ss.str();
		ierr = PetscViewerBinaryOpen(PETSC_COMM_WORLD, fileName.c_str(), FILE_MODE_WRITE, &viewer); CHKERRV(ierr);
		ierr = VecView(qyGlobal, viewer); CHKERRV(ierr);
		ierr = PetscViewerDestroy(&viewer); CHKERRV(ierr);

		// print qz to file
		ss.str("");
		ss.clear();
		ss << savePointDir << "/qz.dat";
		fileName = ss.str();
		ierr = PetscViewerBinaryOpen(PETSC_COMM_WORLD, fileName.c_str(), FILE_MODE_WRITE, &viewer); CHKERRV(ierr);
		ierr = VecView(qzGlobal, viewer); CHKERRV(ierr);
		ierr = PetscViewerDestroy(&viewer); CHKERRV(ierr);

		ierr = PetscPrintf(PETSC_COMM_WORLD, "Data written to folder %s.\n", savePointDir.c_str()); CHKERRV(ierr);
		
		ierr = DMCompositeRestoreAccess(qPack, q, &qxGlobal, &qyGlobal, &qzGlobal); CHKERRV(ierr);
	}
}