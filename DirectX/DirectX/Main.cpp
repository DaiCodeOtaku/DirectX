


#include "Resources.h"
#include "Setup.h"
#include "Camera.h"
#include "GameObject.h"
#include "VertexObject.h"

#include "BasicComm.h"

//#include "ModelObj.h"
#include "Loader.h"

IDXGISwapChain *swapchain;             // the pointer to the swap chain interface
ID3D11Device *dev;                     // the pointer to our Direct3D device interface
ID3D11DeviceContext *devcon;           // the pointer to our Direct3D device context
ID3D11RenderTargetView *backbuffer;    // the pointer to our back buffer
ID3D11DepthStencilView *zbuffer;       // the pointer to our depth buffer
ID3D11InputLayout *pLayout;            // the pointer to the input layout
ID3D11VertexShader *pVS;               // the pointer to the vertex shader
ID3D11PixelShader *pPS;                // the pointer to the pixel shader
ID3D11Buffer *pVBuffer;    // the pointer to the vertex buffer
ID3D11Buffer *pCBuffer;  // the pointer to the constant buffer

//tex
ID3D11ShaderResourceView *pTexture;

ID3D11RasterizerState *pRS;




	int Moffset = 0;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{




#pragma region win_set


    WNDCLASSEX wc;

    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = "WindowClass";

    RegisterClassEx(&wc);

    RECT wr = {0, 0, SW, SH};
    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

    hWnd = CreateWindowEx(NULL,
                          "WindowClass",
                          "DirextX",
                          WS_DLGFRAME,
                          300,
                          300,
                          wr.right - wr.left,
                          wr.bottom - wr.top,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    ShowWindow(hWnd, nCmdShow);

	#pragma endregion Window_Setup


	

	//spawn a console window,useful for debugging ect
	AllocConsole() ;
    AttachConsole( GetCurrentProcessId() ) ;
	freopen("CONIN$", "r", stdin); 
	freopen("CONOUT$", "w", stdout); 
	freopen("CONOUT$", "w", stderr); 

	



////////////////////////////////////////////////////

////////////////////////////////////////////////////
	/*
	Comm * NewComm = new Comm;
	
	NewComm->setup();
	
	NewComm->RECIVE();

	*/


	//setup object
	DxSetup * DX = new DxSetup;

	DX->InitD3D();
	DX->InitPipeline();
	

	Loader *load = new Loader;

	load->loadTexture("Kan.png");
	//load->InitLoad("AssetList.txt");
	load->LoadObj("cube.obj");
	load->LoadObj("spit.obj");
	load->LoadObj("box.obj");
	



	//camera obj
	Cam * CamOverView = new Cam;
	MlistTest.push_back(CamOverView);

	//set inittal Camrea postion
	cX = 0.0f;
	cY = 0.0f;
	cZ = -50.0f;

	
	MSG msg;

	devcon->ClearRenderTargetView(backbuffer, D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f));
    devcon->ClearDepthStencilView(zbuffer, D3D11_CLEAR_DEPTH, 1.0f, 0);



    while(1)
    {
		  if( PeekMessage( &msg, NULL, 0, 0,PM_NOREMOVE ) )
        {
			
			//std::cout<<msg.message << std::endl; // output the current windows msg

		 if (msg.message ==  WM_QUIT)
			{}
		 	
		 if (msg.message == WM_KEYDOWN)
			{
				switch (msg.wParam)
				{



				case VK_F1:
					{
						float x = std::rand() % 20 + 1;
						float y = std::rand() % 20 + 1;


						TestObj * TOVT = new TestObj;
						TOVT->X = x;
						TOVT->Y = y;
						TOVT->Model = 0;
						MlistTest.push_back(TOVT);
					}


					break;

				case VK_F2:
					{
						float x = std::rand() % 20 + 1;
						float y = std::rand() % 20 + 1;


						TestObj * TOVT = new TestObj;
						TOVT->X = x;
						TOVT->Y = y;
						TOVT->Model = 1;
						MlistTest.push_back(TOVT);
					}
					break;


				case VK_F4:
					{
						
						
					}
				break;

				case VK_F5:
					{
					std::cout << "current Camera postion" << std::endl;
					std::cout << "----------------------" << std::endl;
					std::cout << "X =" <<cX << std::endl;
					std::cout << "Y =" <<cY << std::endl;
					std::cout << "Z =" <<cZ << std::endl;
					}
				break;

				case VK_F7:
					std::cout << "Max size is: " << MlistTest.max_size() << std::endl;
				break;



				case VK_ESCAPE:
					DX->CleanD3D();
					exit(0);
					break;

				default:
					break;
				
				}
			}

		 else 
				{
					//TranslateMessage( &msg );
					//DispatchMessage( &msg );           
				}	
		  }
	
		


		/*

		  if(NS == 1)
		  {
				TestObj * TOVT = new TestObj;
				MlistTest.push_back(TOVT);
				TOVT->X = 1.0f;
				TOVT->Y = 1.0f;
				TOVT->AltVertexInBufferTest = false;
				TOVT->InterInfoObj = obj2;
				TOVT->IsNetPlayer = true;
				MlistTest.push_back(TOVT);
		  }

		  */


		  for(int i = 0; i < MlistTest.size();i++)
		  {
			  MlistTest.at(i)->Render();
		  }

		  if(globalneedToRevertex =true)
		  {globalneedToRevertex = false;}

		  
	swapchain->Present(0, 0);	
	devcon->ClearRenderTargetView(backbuffer, D3DXCOLOR(0.1f, 0.5f, 0.1f, 1.0f));
	devcon->ClearDepthStencilView(zbuffer, D3D11_CLEAR_DEPTH, 1.0f, 0);


    }

    // clean up DirectX and COM

	DX->CleanD3D();
    return msg.wParam;
}

	

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
        case WM_DESTROY:
            {
                PostQuitMessage(0);
                return 0;
            } break;
    }

    return DefWindowProc (hWnd, message, wParam, lParam);
}