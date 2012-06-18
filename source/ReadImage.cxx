#include "ReadImage.h"

using namespace std;

typedef itk::ImageFileReader<ImageType> ReaderType;

ReadImage::~ReadImage()
{

}

void ReadImage::operator () (const char *file)
{
	//Create an Image IO object using the ITK factory system
	itk::ImageIOBase::Pointer iobase = itk::ImageIOFactory::CreateImageIO(file, itk::ImageIOFactory::ReadMode);

	//Read the image information
	iobase->SetFileName(file);
	iobase->ReadImageInformation();

	//Set up the reader
	ReaderType::Pointer reader = ReaderType::New();
	reader->SetFileName(file);
	reader->SetImageIO(iobase);
	reader->Update();
	ImagePointer image = reader->GetOutput();
	levelset->m_ImageStack.push_back (image);
}
