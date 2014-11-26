#pragma once

#include "Resources.h"


class Vobj
{
public:
	///constructor
	Vobj();


	int size;
	char Name[20];
	void Vload(VERTEX * vertex,char name[20],int Size);
	std::vector <VERTEX> *InterVerArray;


private:

};

Vobj::Vobj()
{
	InterVerArray = new std::vector <VERTEX>;

}


void Vobj::Vload(VERTEX * vertex,char name[20],int Size)
{
	std::cout << "New object: " << name <<std::endl;
	memcpy(Name,name,sizeof(name));
	size = Size;
	
	short count = 0;

	for(int i = 0;i < Size;i ++)
	{
		InterVerArray->push_back(vertex[i]);
		count++;
	}
	std::cout << "added " << count << " Vertices to buffer \n" << std::endl;



	//std::cout<< Vlist2->size();
	
	/*
		char buff[80];

 std::ifstream infile("input.txt");
  std::stringstream ss;

  while(infile.getline(buff,80))
  {
	  ss << buff;

	  while(ss.getline(buff,10,','))
	  {

	  }
	  std::cout << "done" ;
	  
  }
  */

}