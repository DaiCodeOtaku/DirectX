#include "Resources.h"
#include "Base.h"
#include "VertexObject.h"


class TestUI : public Base
{

public:




	void UiControl();
	void Matrix();
	void SetRender(Vobj * InterObj);
	void Render();


	Vobj * InterInfoObj;



	int DrawVertex;
	int Offset;

private:

};

void TestUI::Render()
{


	UiControl();
	Matrix();
	devcon->Draw(DrawVertex,Offset);
}

void TestUI::UiControl()
{




}

void TestUI::Matrix()
{


}

void TestUI::SetRender(Vobj * InterObj)
{




}

