
#ifndef GameObject_H
#define GameObject_H

#include "Base.h"
#include "Resources.h"
#include "VertexObject.h"
class TestObj : public Base
{

public:


	TestObj();


	void Render();
	void SetRender();
	void Matrix();
	void Control();
	void Delete();


	void VertexCopy();

#pragma region Vars

	//var Zone;
	
	MSG msg;
	D3DXMATRIX matFinal,matRotate,matTran,matScale,matView, matProjection;
	
	int DrawVertex;
	bool IsPlayer;

	bool IsNetPlayer;
	int Model;
	int tex;
//	ModelObj * iModel;

#pragma endregion Varibles


};



TestObj::TestObj()
{
Model = 0;
tex =0;
//iModel = new ModelObj;
//iModel = ModelList->at(Model);


X = 0;
Y = 0;

IsPlayer = false;
IsNetPlayer = false;
}


void TestObj::Delete()
{






}
void TestObj::Render()
{

	if(IsPlayer == true)
	{
	Control();
	}


	Matrix();
	devcon->PSSetShaderResources(0, 1, &Textures[tex]);
	devcon->Draw(ModelList->at(Model)->DrawAV,ModelList->at(Model)->offsetV);
	//devcon->DrawIndexed(500,0,0);

}


void TestObj::SetRender()
{


}
void TestObj::Matrix()
{
	
	// static float Time = 0.0f; Time += 0.0003f;

    // create a world matrices
    D3DXMatrixRotationY(&matRotate,0);

	
 // create a view matrix
    D3DXMatrixLookAtLH(&matView,
						&D3DXVECTOR3(cX, cY, cZ),   // the camera position
                       &D3DXVECTOR3(cX, cY, 0.0f),    // the look-at position
                       &D3DXVECTOR3(0.0f, 1.0f, 0.0f));   // the up direction

    // create a projection matrix
    D3DXMatrixPerspectiveFovLH(&matProjection,
                               (FLOAT)D3DXToRadian(45),                    // field of view
                               (FLOAT)SW / (FLOAT)SH, // aspect ratio
                               1.0f,                                       // near view-plane
                               500.0f);                                    // far view-plane


	D3DXMatrixTranslation(&matTran,X,Y,0);
	//D3DXMatrixRotationX(&matTran,0.5);

    // create the final transform
	matFinal = matTran * matView * matProjection;


struct CBUFFER
{
    D3DXMATRIX Final;
    D3DXMATRIX Rotation;
    D3DXVECTOR4 LightVector;
    D3DXCOLOR LightColor;
    D3DXCOLOR AmbientColor;
};

	CBUFFER cBuffer;

	cBuffer.LightVector = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.0f);
    cBuffer.LightColor = D3DXCOLOR(0.8f, 0.5f, 0.5f, 1.0f);
    cBuffer.AmbientColor = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
	cBuffer.Rotation = matRotate;
	cBuffer.Final = matFinal;

	devcon->UpdateSubresource(pCBuffer, 0, 0, &cBuffer, 0, 0);
	//devcon->UpdateSubresource(pCBuffer, 0, 0, &matFinal, 0, 0);
	
}

void TestObj::Control()
{
	 
	// if there is a windows message to process...
        if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
        {

		 if (msg.message == WM_KEYDOWN)
			{
				switch (msg.wParam)
				{

				case VK_UP:
					Y = Y + 0.1;
					break;

				case VK_DOWN:
					Y = Y - 0.1;
					break;

				case VK_LEFT:
					X = X - 0.1;
					break;

				case VK_RIGHT:
					X = X + 0.1;
					break;


				}
			}
			else 
				{
			
				
                
				}
		}





}


void TestObj::VertexCopy()
{
	
}


#endif