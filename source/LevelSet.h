#ifndef DEF_LEVELSET_H
#define DEF_LEVELSET_H

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include "itkImage.h"

using namespace std;

typedef itk::Image<float,3> ImageType;
typedef ImageType::Pointer ImagePointer;

class LevelSet
{
	public:
		LevelSet();	//Constructor
		~LevelSet();	//Destructor

		void PrintCommandListing();	//Print the command listing when asked by the user
		int ProcessCommandLine(int argc, char *argv[]);	//Check the input parameters in the command line
		int ProcessCommand(char *argv[]);	//Process the command asked by the user
		vector<ImagePointer> m_ImageStack;	//Stack of images from the command line

		double m_propagation;	//Propagation coefficient (alpha)
		double m_curvature;	//Curvature coefficient (beta)
		double m_advection;	//Advection coefficient (gamma)

	private:
		int m_iterations;	//Number of iterations
};

#endif
