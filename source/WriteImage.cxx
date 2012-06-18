#include "WriteImage.h"

using namespace std;

typedef itk::ImageFileWriter<ImageType> WriterType;

WriteImage::~WriteImage()
{

}

void WriteImage::operator() (const char *file, int pos)
{
	//Get the input image
	if(levelset->m_ImageStack.size() == 0)
	{
		cout << "No data has been generated" << endl; 	
	}
	
	//Get the image at the given position
	if(pos < 0)
	{
		pos = levelset->m_ImageStack.size() - 1;
	}
	ImagePointer input = levelset->m_ImageStack[pos];

	//Create the output image
	ImageType::Pointer output = ImageType::New();
	output->SetRegions(input->GetBufferedRegion());
	output->SetSpacing(input->GetSpacing());
	output->SetOrigin(input->GetOrigin());
	output->SetDirection(input->GetDirection());
	output->Allocate();
	
	//Copy everything
	size_t n = input->GetBufferedRegion().GetNumberOfPixels();
	for (size_t i = 0; i<n; i++)
	{
		output->GetBufferPointer()[i] = (float) (input->GetBufferPointer()[i]);
	}

	//Write the image out
	WriterType::Pointer writer = WriterType::New();
	writer->SetInput(output);
	writer->SetFileName(file);
	writer->Update();
}
