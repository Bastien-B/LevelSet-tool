#ifndef DEF_SEGMENTATION_H
#define DEF_SEGMENTATION_H

#include "LevelSet.h"
#include <itkThresholdSegmentationLevelSetFunction.h>
#include <itkParallelSparseFieldLevelSetImageFilter.h>

using namespace std;

class Segmentation
{
	public:
		Segmentation(LevelSet *levelset) : levelset(levelset){};
		~Segmentation();

		void operator() (int nb_iter);

	private:
		LevelSet *levelset;
};

#endif
