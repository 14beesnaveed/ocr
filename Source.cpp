#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <iostream>
#include <fstream>
#include <conio.h>

int main(int argc, char **argv)
{
	system("mode CON: COLS=100 LINES=300");
	int x=1;
	while(x==1)
	{
	// checking for existence of source file
	 std::ifstream inFile(argv[1]);

	 if(!inFile.is_open()){
		 std::cerr << "\n\nFile \""<< argv[1] << "\" not found.";
		 
		 inFile.close();
		 exit(1);
		
		 }
	 inFile.close();

	 // checking for existence of destination file
	 std::ifstream inFile2(argv[2]);

	 if(inFile2.is_open()){
		 std::cout << "\n\nFile \""<< argv[2] << "\" already exists. Want to append it? [y/n]";
		 
		 char c=_getch();

		 if(c=='N' || c=='n'){

			 inFile2.close();
			 exit(1);
			}
		 }
	 inFile2.close();

	 
	std::ofstream outFile(argv[2],std::ios::app); // file in which data is to stored

	 std::cout << "\n\nProcessing.............\n\n";

  // converting image to pixel array here
  Pix *image1 = pixRead(argv[1]);
  tesseract::TessBaseAPI *api1 = new tesseract::TessBaseAPI();
  api1->Init(NULL, "eng");
  api1->SetImage(image1);
  api1->Recognize(0);
  tesseract::ResultIterator* ri = api1->GetIterator();
  tesseract::PageIteratorLevel level = tesseract::RIL_WORD;

  // printing each word with its location
  std::cout<< "Word                Location\n";
  std::cout<< "---------------------\n";
  int counter =0;
  if (ri != 0) {
	do {
	  const char* word = ri->GetUTF8Text(level);
	  int x1, y1, x2, y2;
	  ri->BoundingBox(level, &x1, &y1, &x2, &y2);
	  if (counter == 2)
	  {
		  printf("\n");
		  counter = 0;
	  }

	  
	  printf("%-10s         %d,%d,%d,%-10d\t", word, x1, y1, x2, y2);
	  
	  counter++;
	  
	  
	  // saving to a file
	  outFile << word << " " << x1 << " " << y1 <<  " " << x2 << " " << y2 << "\n";

	} while (ri->Next(level));
  }

  std::cout << "\n\nSaved to " << argv[2] << ". Press any Key to Continue.....";

		// Destroy used object and release memory
		api1->End();
		pixDestroy(&image1);

	}

  getchar();
	return 0;
}

