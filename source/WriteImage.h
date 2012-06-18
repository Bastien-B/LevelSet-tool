#ifndef DEF_WRITEIMAGE_H
#define DEF_WRITEIMAGE_H

#include "LevelSet.h"
#include <itkImage.h>
#include <itkImageFileWriter.h>

using namespace std;

typedef itk::Image<float,3> imagetype_float;
typedef itk::ImageFileWriter<imagetype_float> writertype;

class WriteImage
{
	public:
		WriteImage(LevelSet *levelset) : levelset(levelset){};
		~WriteImage();

		void operator() (const char *file, int pos=-1);
	private:
		LevelSet *levelset;
};		

#endif
