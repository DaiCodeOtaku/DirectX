#pragma once

#define MB 1000000




#include <Windows.h>
#include "Resources.h"
#include <sys\stat.h>
#include <ctype.h>

typedef unsigned int uint;

class Loader
{
public:
	
	Loader();
	~Loader();
	//obj stuff
	int LoadObj(std::string filename);
	void MoveToBuffer(int ModelToMove);
	void TestSize(std::string filename);

	std::vector <int> Vpostion;
	std::vector <int> Fpostion;
	std::vector <int> VTpostion;
	std::vector <int> VNpostion;



	void sortVetices();
	void sortTextCorrd();
	void sortIndices();
	void sortNormals();

	void Link(ModelObj * NewModel);

	ModelObj * NewModel;
	int vertcount;
	int vtcount;
	int facecount;
	int normalcount;

	bool Tw1;
	bool Tw2;
	bool Tw3;
	bool Tw4;

	

	static void Magic1(void * ptr){
		reinterpret_cast<Loader *>(ptr)->sortIndices();
	};

	static void Magic2(void * ptr){
		reinterpret_cast<Loader *>(ptr)->sortVetices();
	};

	static void Magic3(void * ptr){
		reinterpret_cast<Loader *>(ptr)->sortTextCorrd();
	};

	static void Magic4(void * ptr){
		reinterpret_cast<Loader *>(ptr)->sortNormals();
	};



	void tmp();

	//end of obj stuff



	//Texturestuff

	void loadTexture(LPCSTR File);



	int InitLoad(std::string filename);

	void InitModels();

	std::vector <int> TexturePostion;
	std::vector <int> ModelPostion; 

	

	//shared
	char * pData;  
	HANDLE MH;


private:
	HRESULT Result;

};

void Loader::tmp()
{


	time_t start;
	start = clock();
	int tmp1 = NewModel->Index->size();

	std::vector <index> I;
	for(int i = 0; i <tmp1;i++)
	{
		

		index IX;
	
		IX = NewModel->Index->at(i);

		for(int a = 0; a < tmp1;a++)
		{
			index IX1 = NewModel->Index->at(a);

			if(IX.Vertex == IX1.Vertex && IX.normal == IX1.normal && IX.Textcorrd == IX1.Textcorrd && IX.Index!= IX1.Index)
			{
				printf("found one \n");

				for(int i = 0;i<= I.size();i++)
				{
					index IXT = NewModel->Index->at(a);
					if(IX1.Vertex == IXT.Vertex && IX1.normal == IXT.normal && IX1.Textcorrd == IXT.Textcorrd && IX1.Index!= IXT.Index)
					{
						I.push_back(IX1);
					}
			}
			

		}


	}



}

start = clock() - start;
std::cout << "Completed in " << ((float)start)/CLOCKS_PER_SEC << " Seconds" << "\n";
}
Loader::Loader()
{
vertcount = 0;
vtcount = 0;
facecount =0;
normalcount = 0;

Vpostion.empty();
VNpostion.empty();
Fpostion.empty();
VTpostion.empty();

Tw1 = false;
Tw2 = false;
Tw3 = false;
Tw4 = false;
pData = new char; 
NewModel= new ModelObj;
}

Loader::~Loader()
{
	delete &pData;
	delete &NewModel;


}

void Loader::loadTexture(LPCSTR File)
{

	int i =0;
	bool scan = false;
	while(scan == false)
	{
		if(Textures[i] == 0)
			{
				HRESULT HR;
						HR = D3DX11CreateShaderResourceViewFromFile(dev,            // the Direct3D device
												File,    // load Wood.png in the local folder
											   NULL,           // no additional information
											   NULL,           // no multithreading
											   &Textures[i],      // address of the shader-resource-view
											   NULL); // no multithreading
				if (HR != S_OK) MessageBox(NULL,"ERrror","Texture load failed",MB_OK);
				if (HR == S_OK) std::cout << "Texture loaded" << std::endl;
				TextureObj * NewTex = new TextureObj;
				NewTex->ID = File;

				NewTex->Tex= i;
				scan =true;

				TextureList->push_back(NewTex);
			}
		i++;
			if(i < 100)
			{
				scan = true;
			}
	}
	
		
}



int Loader::InitLoad(std::string filename)
{
	struct stat statbuf;
	stat(filename.c_str(),&statbuf);


	HANDLE MappedFile;
	HANDLE File;

	DWORD FileSize;
	//DWORD FilemapSize;

	LPVOID lpMapAddress;

	      // pointer to the data
	

	File = CreateFileA(filename.c_str(),GENERIC_READ,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);

	if (File == INVALID_HANDLE_VALUE)
		{
			printf("error opening file \n");
			//do some error stuff
			return 1;
		}

		FileSize = GetFileSize(File,  NULL); //secondary size check,useing a Dword
			if(FileSize == NULL)
			{
				printf("Error FileSize is 0");
				return 2;
			}

			MappedFile = CreateFileMapping(File,0,PAGE_READONLY,0,statbuf.st_size,0);
				if (MappedFile == NULL)
				{
					printf("error createing fileView\n");
					return 3;
				}

				lpMapAddress = MapViewOfFile(MappedFile,FILE_MAP_READ,0,0,statbuf.st_size);
					if (lpMapAddress == NULL)
					{
						printf("LPmapadress is Null\n");
						return 4;
					}

	
pData = (char *) lpMapAddress; //contain all the data from the obj in a single long char Array

CloseHandle(File);// realses the program hold on the file,if this is not closed File cant be accesed till the program closes
CloseHandle(MappedFile);// oid not needed any more so has been closed




for(int a = 0;a < statbuf.st_size ;a++)
{
	if(pData[a] == 'M' && pData[a + 1] == ' ')
	{
		uint temp = (a +1);
		ModelPostion.push_back(temp);
	}

	if(pData[a] == 'T' && pData[a + 1] == ' ')
	{
		uint temp = (a +1);
		TexturePostion.push_back(temp);
	}



}

//if(ModelPostion.size() <= 0)
//{
	InitModels();
//}


}

void Loader::InitModels()
{
	printf("Starting Vertices Sort\n");
	time_t start;
	start = clock();
	for(int a = 0;a < ModelPostion.size();a++)
{
	int tmpp = ModelPostion.at(a);

	int tmp1=0;
	int tmp2=0;
	int firstCounter = 0; // postion
	int secondCounter=0; //
	bool btmp = false;
	
	std::string file;

	int CtmpVar = 1; 
		while(btmp == false)
		{

			if(pData[tmpp +tmp1] == 'm' && pData[tmpp +(tmp1 +1)] == ' ' )
		{
			char * tmpC = new char; // store the number we will std::stof
		
			int tmp3 = tmpp + (tmp1 +1); //put the start at the first char
			bool btmp2 =false; //for the scan while
			int Ctmp3 = 0; //keep track of how mnay postion we track from first charater
			bool stop = false;
			
			while(btmp2 ==  false)
			{

				if(pData[tmpp + tmp3] == '\n')
				{
					stop = true;
				}

				if(stop == false)
				{
				tmpC[tmp2] == pData[tmpp + tmp3];
				}
				
				if(stop == true)
				{
					btmp = true;
				}
			}
			
			//file  = tmpC; 		
//printf("nop");

			// do processing here
			secondCounter++;
		} //end of if

			btmp = true;
	} //end of big while
	


//	NewModel->vertices->push_back(Vertex);
//	std::cout << pData[tmpp] << "\n";

	
	}
}

int Loader::LoadObj(std::string filename)
{
	pData = new char; 
	NewModel= new ModelObj;
	
	vertcount =0;
	vtcount =0;
	facecount =0;
	normalcount =0;

	Vpostion.clear();
	VNpostion.clear();
	Fpostion.clear();
	VTpostion.clear();

	time_t start;
	start = clock();
	struct stat statbuf;
	stat(filename.c_str(),&statbuf);


	HANDLE MappedFile;
	HANDLE File;

	DWORD FileSize;
	

	LPVOID lpMapAddress;

	      // pointer to the data
	

	File = CreateFileA(filename.c_str(),GENERIC_READ,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);

	if (File == INVALID_HANDLE_VALUE)
		{
			printf("error opening file \n");
			//do some error stuff
			return 1;
		}

		FileSize = GetFileSize(File,  NULL); //secondary size check,useing a Dword
			if(FileSize == NULL)
			{
				printf("Error FileSize is 0");
				return 2;
			}

			MappedFile = CreateFileMapping(File,0,PAGE_READONLY,0,statbuf.st_size,0);
				if (MappedFile == NULL)
				{
					printf("error createing fileView\n");
					return 3;
				}

				lpMapAddress = MapViewOfFile(MappedFile,FILE_MAP_READ,0,0,statbuf.st_size);
					if (lpMapAddress == NULL)
					{
						printf("LPmapadress is Null\n");
						return 4;
					}

	
pData = (char *) lpMapAddress; //contain all the data from the obj in a single long char Array

CloseHandle(File);// realses the program hold on the file,if this is not closed File cant be accesed till the program closes
CloseHandle(MappedFile);// oid not needed any more so has been closed



//note zone
/*

currently esting with blender models 
max 31 postions per Vertex line 
pos 1 is the V,leaveing 30 postion for float numbers

look up atol ect, will be useful for converting cha rin to numbers
*/





for(int a = 0;a < statbuf.st_size ;a++)
{
	if(pData[a] == 'v' && pData[a+1] == ' ')
	{
		int tmp= a;
		Vpostion.push_back(a);
		vertcount++;	
	}
	
	if(pData[a] == 'v' && pData[a+1] == 't'  && pData[a+2] == ' ')
	{
		VTpostion.push_back(a);
		vtcount++;
	}

	if(pData[a] == 'f' && pData[a+1] == ' ')
	{
		Fpostion.push_back(a);
		facecount++;
	}
		
	if(pData[a] == 'v' && pData[a+1] == 'n' && pData[a+2] == ' ')
	{
		VNpostion.push_back(a);
		normalcount++;
	}

}

std::cout << "Loading Object: " << filename.c_str() << "\n";
std::cout <<" Object contains " << vertcount << " Vertices " <<  "\n";
std::cout <<" Object contains " << vtcount << " Texture Vertices " <<  "\n";
std::cout <<" Object contains " << facecount << " Faces " <<  "\n";
std::cout <<" Object contains " << normalcount << " normal " <<  "\n";

std::cout << "\n";

NewModel->ID = filename.c_str();


if(facecount != 0)
{
	sortIndices();
	//MH = (HANDLE)_beginthread(&Loader::Magic1,0,this);
}

if(vertcount != 0)
{
	sortVetices();
	//MH = (HANDLE)_beginthread(&Loader::Magic2,0,this);
}

if(vtcount != 0)
{
	sortTextCorrd();
	//MH = (HANDLE)_beginthread(&Loader::Magic3,0,this);
}

if(normalcount != 0)
{
	sortNormals();
	//MH = (HANDLE)_beginthread(&Loader::Magic4,0,this);
}

/*
bool tmpBool = false;
while(tmpBool == false)
{

	if(Tw2 == true && Tw1 == true && Tw3 == true && Tw4 == true )
	{
		tmpBool = true;
	}
}

*/
int tmp = ModelList->size();
ModelList->push_back(NewModel);
std::cout << "Adding Model " << NewModel->ID << "To Model List \n"; 
MoveToBuffer(tmp);

start = clock() - start;
std::cout << "Completed in " << ((float)start)/CLOCKS_PER_SEC << " Seconds" << "\n";

UnmapViewOfFile(MappedFile);
printf("End of Object loading\n \n");
return 5;
}

void Loader::TestSize(std::string filename)
{
	struct stat stat_buf;
	stat(filename.c_str(),&stat_buf);
	std::cout << "Size of File is : " << stat_buf.st_size << "\n";
}

void Loader::MoveToBuffer(int ModelToMove)
{

	int SizeOfV =sizeof(struct Ver);
	int size =  ModelList->at(ModelToMove)->Index->size() -1;



	int DrawAV =0;
	int DrawAI =0;
	
	int tmp1 =0;
	int tmp2 =0;
	ModelList->at(ModelToMove)->offsetI = offsetI;
	ModelList->at(ModelToMove)->offsetV = offsetV;


	for(int i = 0;i <= size; i++)
	{
		Ver vertex;
		
		int vert = ModelList->at(ModelToMove)->Index->at(i).Vertex-1;
		int normal = ModelList->at(ModelToMove)->Index->at(i).normal-1;
		int uv = ModelList->at(ModelToMove)->Index->at(i).Textcorrd-1;

		vertex.x = ModelList->at(ModelToMove)->vertices->at(vert).x;
		vertex.y = ModelList->at(ModelToMove)->vertices->at(vert).y;
		vertex.z = ModelList->at(ModelToMove)->vertices->at(vert).z;

		vertex.nx = ModelList->at(ModelToMove)->Normal->at(normal).nx;
		vertex.ny = ModelList->at(ModelToMove)->Normal->at(normal).ny;
		vertex.nz = ModelList->at(ModelToMove)->Normal->at(normal).nz;

		vertex.u= ModelList->at(ModelToMove)->TextCorrd->at(uv).u;
		vertex.v= ModelList->at(ModelToMove)->TextCorrd->at(uv).v;

		MVBuffer2[offsetV+ i] = vertex;
		Index[offsetI + i] =  ModelList->at(ModelToMove)->Index->at(i).Index-1;

		//incement area
		DrawAV++;
		DrawAI++;
		tmp1++;
		tmp2++;
	}
	
	offsetV = offsetV + tmp1;
	offsetI = offsetI + tmp2;

	ModelList->at(ModelToMove)->DrawAV = DrawAV; 
		
	UINT stride = sizeof(Ver);
    UINT offset = 0;

    devcon->IASetVertexBuffers(0, 1, &pVBuffer, &stride, &offset);
	devcon->IASetIndexBuffer(pIBuffer, DXGI_FORMAT_R32_UINT,0);

	devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//////////////////////////////////////////////////
	
	//////////////////////////////////////////////////
	
	D3D11_MAPPED_SUBRESOURCE ms;
	devcon->Map(pVBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &ms);    // map the buffer
	memcpy(ms.pData, MVBuffer2, sizeof(MVBuffer2));
    devcon->Unmap(pVBuffer, NULL);


	stride = sizeof(unsigned int);

	devcon->Map(pIBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);    // map the buffer
	memcpy(ms.pData,Index, sizeof(Index));                   // copy the data
    devcon->Unmap(pIBuffer, NULL);
	


};

void Loader::sortVetices()
{

	printf("Starting Vertices Sort\n");
	time_t start;
	start = clock();
for(int a = 0;a < Vpostion.size();a++)
{
	int tmpp = Vpostion.at(a);

	int firstCounter = 0; // postion
	int secondCounter=0; //
	bool btmp = false;
	
	V Vertex ;

	int CtmpVar = 1; 
	while(btmp == false)
	{
		
		if(pData[tmpp + firstCounter] == ' ' && pData[tmpp + (firstCounter +1)] == '-')
		{
			char * tmpC = new char; // store the number we will std::stof
		
			int tmp3 = tmpp + (firstCounter +1); //put the start at the first char
			bool btmp2 =false; //for the scan while
			int Ctmp3 = 0; //keep track of how mnay postion we track from first charater

			
			while(btmp2 ==  false)
			{
				tmpC[Ctmp3] = pData[tmp3 +Ctmp3];
				
				if(pData[tmp3 + Ctmp3] == ' ')
					{
						btmp2 = true;
					}
				
			//	if(!Ctmp3 <= 4)
			//	{
				Ctmp3++;
			//	}
			}
			
			switch(CtmpVar)
			{
			case 1:
				Vertex.x = std::stof(tmpC);
				CtmpVar++;
			break;

			case 2:
				Vertex.y = std::stof(tmpC);
				CtmpVar++;
			break;

			case 3:
				Vertex.z = std::stof(tmpC);
				CtmpVar++;
			break;

			}	
			secondCounter++;

		

		} //end of if

			if(pData[tmpp + firstCounter] == ' '&& isdigit(pData[tmpp + (firstCounter +1)]))
		{
			char * tmpC = new char; // store the number we will std::stof
		
			int tmp3 = tmpp + (firstCounter +1); //put the start at the first char
			bool btmp2 =false; //for the scan while
			int Ctmp3 = 0; //keep track of how mnay postion we track from first charater

			
			while(btmp2 ==  false)
			{
				tmpC[Ctmp3] = pData[tmp3 +Ctmp3];
				
				if(pData[tmp3 + Ctmp3] == ' ')
					{
						btmp2 = true;
					}


				//if(!Ctmp3 <= 4)
			//	{
				Ctmp3++;
			//	}
			}
			
			switch(CtmpVar)
			{
			case 1:
				Vertex.x = std::stof(tmpC);
				CtmpVar++;
			break;

			case 2:
				Vertex.y = std::stof(tmpC);
				CtmpVar++;
			break;

			case 3:
				Vertex.z = std::stof(tmpC);
				CtmpVar++;
			break;

			}	
			secondCounter++;
		} //end of if



		if(secondCounter == 3)
		{
			btmp = true;
		}

		firstCounter++;

	} //end of big while
	


	NewModel->vertices->push_back(Vertex);
//	std::cout << pData[tmpp] << "\n";

}

start = clock() - start;
std::cout << "Vertices Sort Completed in " << ((float)start)/CLOCKS_PER_SEC << " Seconds" << "\n" << "\n";

Tw1 = true;
}

void Loader::sortIndices()
{
	
	printf("Starting Index Sort\n");
	time_t start;
	start = clock();
	int indexcount = 0;

		for(int a = 0; a < Fpostion.size();a++)
		{
			

			index IX;
			IX.normal =0;
			IX.Textcorrd = 0;
			IX.Vertex = 0;
			IX.Index = 0;
			//std::cout << "beinging loop " << a << "\n";
			
	int pos = Fpostion.at(a) +2;

	int Tmp1 = 0;
	int Tmp2 = 0;
	int Tmp3 = 0;
	int Tmp4 = 1;
	int Tmp5 = 0;
	

	bool tempBool1 = false;
	bool tempBool2 = false;
	bool tempBool3 = false;

	bool space = false;
	bool devide = false;
	bool EndOfLine = false;
	bool Add = false;
	char * TmpC = new char;

	while(tempBool1 ==false)
	{

		while(tempBool2 == false)
		{
		if(pData[pos + Tmp1] == ' ' || 47 || '\n')
		{
			if(pData[pos + Tmp1] == ' ')
				{
						
				 space = true;


				}
				else
			{
				space = false;
			}


			if(pData[pos + Tmp1] == 47)
				{
					Add = true;
					devide = true;
					
					
				}
			else
			{
				devide = false;
			}

			if(pData[pos + Tmp1] == '\n') 
				{
					space = true;
					EndOfLine = true;
					tempBool1 = true;
					tempBool2= true;

				}
			else
			{
				EndOfLine = false;
			}

		} //end of limit checker



		if( devide == false && space == false && EndOfLine == false && isdigit(pData[pos + Tmp1]))
		{
			TmpC[Tmp2] = pData[pos + Tmp1];
		//	std::cout << TmpC[Tmp2];
		}


		Tmp1++;
		Tmp2++;
		if(devide == true || space == true)
		{

			switch(Tmp4)
			{
			case 1:
				{
			unsigned int xtemp;
			xtemp = atoi(TmpC);
			IX.Vertex = xtemp;
			Tmp2 = 0;
			TmpC = new char;
			Tmp4++;
			Add = false;
			
			//tempBool2 = false;
				}
				break;

				case 2:
					{
						unsigned int xtemp;
						xtemp = atoi(TmpC);
						IX.Textcorrd= xtemp;
						Tmp2 = 0;
						TmpC = new char;
						Tmp4++;
						Add = false;
						//tempBool2 = false;
					}
				break;

				case 3:
					{
						unsigned int xtemp;
						xtemp = atoi(TmpC);
						IX.normal= xtemp;
						Tmp2 = 0;
						TmpC = new char;
						Tmp4++;
						Add = false;
						//tempBool2 = false;
					}
				break;
		

			}

			if(Tmp4 ==4)
				{
					indexcount++;
					IX.Index = indexcount;
					NewModel->Index->push_back(IX);
					IX.Vertex = 0;
					IX.Textcorrd =0;
					IX.normal = 0;
					Tmp4 = 1;
				}
		
		}

		
		
		}




		

	}
		
		
	}



	start = clock() - start;
	std::cout << "Index Sort Completed in " << ((float)start)/CLOCKS_PER_SEC << " Seconds" << "\n" << "\n";
	Tw2 = true;
}

void Loader::sortTextCorrd()
{
	
	printf("Starting TextCorrd Sort\n");
	time_t start;
	start = clock();

for(int a = 0;a < VTpostion.size();a++)
{
	int tmpp = VTpostion.at(a);

	int firstCounter = 0; // postion
	int secondCounter=0; //
	bool btmp = false;
	
	Texcorrd VT; 

	int CtmpVar = 1; 

	while(btmp == false)
	{
		
			if(pData[tmpp + firstCounter] == ' '&& isdigit(pData[tmpp + (firstCounter +1)]))
		{
			char * tmpC = new char; // store the number we will std::stof
		
			int tmp3 = tmpp + (firstCounter +1); //put the start at the first char
			bool btmp2 =false; //for the scan while
			int Ctmp3 = 0; //keep track of how mnay postion we track from first charater

			
			while(btmp2 ==  false)
			{
				tmpC[Ctmp3] = pData[tmp3 +Ctmp3];
				
				if(pData[tmp3 + Ctmp3] == ' ')
					{
						btmp2 = true;
					}


			
				Ctmp3++;
				
			}
			switch(CtmpVar)
			{
			case 1:
				VT.u = (std::stof(tmpC));
				CtmpVar++;
			break;

			case 2:
				VT.v =(std::stof(tmpC));
				CtmpVar++;
			break;
		} 
			secondCounter++;
		} //end of if

			

		if(secondCounter == 2)
		{
			btmp = true;
		}

		firstCounter++;

	} //end of big while
	
//	std::cout << pData[tmpp] << "\n";
	NewModel->TextCorrd->push_back(VT);
}


start = clock() - start;
std::cout << "TextCord Sort Completed in " << ((float)start)/CLOCKS_PER_SEC << " Seconds" << "\n" << "\n";
Tw3 =true;
}

void Loader::sortNormals()
{
	printf("Starting Normal Sort \n");
	time_t start;
	start = clock();

	for(int a = 0;a < VNpostion.size();a++)
{
	int tmpp = VNpostion.at(a);

	int firstCounter = 0; // postion
	int secondCounter=0; //
	bool btmp = false;


	normal N;
	int CtmpVar = 1;
	while(btmp == false)
	{
		
		if(pData[tmpp + firstCounter] == ' ' && pData[tmpp + (firstCounter +1)] == '-')
		{
			char * tmpC = new char; // store the number we will std::stof
		
			int tmp3 = tmpp + (firstCounter +1); //put the start at the first char
			bool btmp2 =false; //for the scan while
			int Ctmp3 = 0; //keep track of how mnay postion we track from first charater

			
			while(btmp2 ==  false)
			{
				tmpC[Ctmp3] = pData[tmp3 +Ctmp3];
				
				if(pData[tmp3 + Ctmp3] == ' ')
					{
						btmp2 = true;
					}
				
				Ctmp3++;
			
			}
			
			switch(CtmpVar)
			{
			case 1:
				N.nx = std::stof(tmpC);
				CtmpVar++;
			break;

			case 2:
				N.ny = std::stof(tmpC);
				CtmpVar++;
			break;

			case 3:
				N.nz = std::stof(tmpC);
				CtmpVar++;
			break;
			}

			
			
			secondCounter++;

		

		} //end of if

			if(pData[tmpp + firstCounter] == ' '&& isdigit(pData[tmpp + (firstCounter +1)]))
		{
			char * tmpC = new char; // store the number we will std::stof
		
			int tmp3 = tmpp + (firstCounter +1); //put the start at the first char
			bool btmp2 =false; //for the scan while
			int Ctmp3 = 0; //keep track of how mnay postion we track from first charater

			
			while(btmp2 ==  false)
			{
				tmpC[Ctmp3] = pData[tmp3 +Ctmp3];
				
				if(pData[tmp3 + Ctmp3] == ' ')
					{
						btmp2 = true;
					}


				Ctmp3++;
				
			}
					switch(CtmpVar)
			{
			case 1:
				N.nx = std::stof(tmpC);
				CtmpVar++;
			break;

			case 2:
				N.ny = std::stof(tmpC);
				CtmpVar++;
			break;

			case 3:
				N.nz = std::stof(tmpC);
				CtmpVar++;
			break;
			}
			secondCounter++;
		} //end of if

			

		if(secondCounter == 3)
		{
			btmp = true;
		}

		firstCounter++;

	} //end of big while
	
//	std::cout << pData[tmpp] << "\n";
	NewModel->Normal->push_back(N);
}

start = clock() - start;
std::cout << "Normals Sort Completed in " << ((float)start)/CLOCKS_PER_SEC << " Seconds" << "\n" << "\n";
Tw4 = true;
}


void Loader::Link(ModelObj * NewModel)
{
	
}
