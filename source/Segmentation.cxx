#include "Segmentation.h"

using namespace std;

typedef itk::ParallelSparseFieldLevelSetImageFilter<ImageType, ImageType> SegFilter;
typedef itk::ThresholdSegmentationLevelSetFunction<ImageType, ImageType> SegFunction;

Segmentation::~Segmentation()
{

}

void Segmentation::operator() (int nb_iter)
{
	//Check input availability
	if(levelset->m_ImageStack.size() < 2)
	{
		cout << "Levelset segmentation requires 2 images as input" << endl;
		return;
	}

	//Get the last two images
	ImagePointer i1 = levelset->m_ImageStack[levelset->m_ImageStack.size() - 1];
	ImagePointer i2 = levelset->m_ImageStack[levelset->m_ImageStack.size() - 2];

	//Create a segmentation filter
	SegFilter::Pointer fltSegment = SegFilter::New();
	
	//Create the segmentation function
	SegFunction::Pointer fnSegment = SegFunction::New();

	//Set up the radius
	SegFunction::RadiusType rad;
	rad[0] = rad[1] = rad[2] = 1;
	fnSegment->Initialize(rad);
	fnSegment->SetSpeedImage(i2);
	fnSegment->SetCurvatureWeight(levelset->m_curvature);
	cout << "Curvature1 = " << fnSegment->GetCurvatureWeight() << endl;
	fnSegment->SetAdvectionWeight(levelset->m_advection);
	cout << "Advection = " << fnSegment->GetAdvectionWeight() << endl;
	
	fnSegment->SetPropagationWeight(0.8);
	cout << "Propagation Weight  = " << fnSegment->GetPropagationWeight() << endl;
	

	//Set the inputs to the segmentation filter
	//ParallelSparseField filter
	fltSegment->SetInput(i1);
	fltSegment->SetNumberOfLayers(3);
	fltSegment->SetIsoSurfaceValue(0.5);
	cout << "nb_iter = " << nb_iter << endl;
	fltSegment->SetNumberOfIterations(nb_iter);
	fltSegment->SetDifferenceFunction(fnSegment);

	cout << "Function2 = " << fltSegment->GetDifferenceFunction() << endl;
	
	// Execute the filter
	fltSegment->Update();

	// Take the output
	levelset->m_ImageStack.pop_back();
	levelset->m_ImageStack.pop_back();
	levelset->m_ImageStack.push_back(fltSegment->GetOutput());
}
