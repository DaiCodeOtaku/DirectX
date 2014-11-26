

#include "Resources.h"

class TextureObj
{
public:

	TextureObj();

	std::string ID;
	int Tex;
};


TextureObj::TextureObj()
{
	ID = "NULL";
	Tex = 0;
}