#include "Resources.h"



struct index
{
	unsigned int Vertex;
	unsigned int Textcorrd;
	unsigned int normal;
	unsigned int Index;
};


struct Texcorrd
{
	float u, v;
};

struct normal
{
	float nx ,ny ,nz;
};


struct V
{
	float x, y, z;
};


class ModelObj
{
	public:

		ModelObj();

		std::vector <V> *vertices;
		std::vector <Texcorrd> * TextCorrd;
		std::vector <index> * Index;
		std::vector <normal> * Normal;

		int offsetI;
		int offsetV;
		int DrawAV;
		int DrawAI;

		std::string ID;
	private:
};


ModelObj::ModelObj()
{

	ID = "NULL";
	offsetI = 0;
	offsetV = 0;
	DrawAV=0;
	DrawAI = 0;
	vertices = new std::vector <V>;
	Index = new std::vector <index>;
	TextCorrd = new std::vector<Texcorrd>;
	Normal = new std::vector<normal>;


}