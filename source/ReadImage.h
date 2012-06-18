#ifndef DEF_READIMAGE_H
#define DEF_READIMAGE_H

#include "LevelSet.h"
#include <itkImage.h>
#include <itkImageFileReader.h>

using namespace std;

class ReadImage
{
	public:
		ReadImage(LevelSet *levelset) : levelset(levelset){};
		~ReadImage();

		void operator() (const char *file);

	private:
		LevelSet *levelset;
};

#endif
