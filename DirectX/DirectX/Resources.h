#ifndef RESOURCES_H
#define RESOURCES_H

#define MB 1000000

///my stuff
#include "Base.h"



#include"Poco\Net\DatagramSocket.h"
#include"Poco\Net\IPAddress.h"
#include"Poco\Net\Net.h"
#include"Poco\Net\SocketAddress.h"
#include"Poco\Net\Socket.h"


#include <stdio.h>

	struct Ver
{
	FLOAT x, y, z;
	FLOAT nx ,ny ,nz;
	FLOAT u, v;
};

struct info
{
	std::string ID;
	std::string IP;
	unsigned short port; 
};

struct playerInfo
{
	int offset;
	std::string ID;

};

struct pack
{
	float x, y, z;
	char state;
	std::string ID;
};


#pragma comment(lib, "pocoNetd.lib")
#pragma comment(lib, "pocoFoundationd.lib")

#include <WinSock2.h>
//winsock lib
#pragma comment(lib, "ws2_32.lib")


//windows stuff
//#include <windows.h>
//#include <windowsx.h>
#include <process.h>


#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>
#include <string>

#include <vector>


//direct3D stuff
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>




#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")


//in bytes,the vertex memort size
#define VertexBufferSize 5000000//512 KB


//network area

int Mport1 = 37775;// server port 
int Mport2 = 37776; //client port recive port

bool Connected = false;

//short NS =0; // BasicComm no whas an internal Networkstate



//DirectX and Direct3D COM Object and buffers
#pragma region D3D
extern IDXGISwapChain *swapchain;             // the pointer to the swap chain interface
extern ID3D11Device *dev;                     // the pointer to our Direct3D device interface
extern ID3D11DeviceContext *devcon;           // the pointer to our Direct3D device context
extern ID3D11RenderTargetView *backbuffer;    // the pointer to our back buffer
extern ID3D11DepthStencilView *zbuffer;       // the pointer to our depth buffer
extern ID3D11InputLayout *pLayout;            // the pointer to the input layout
extern ID3D11VertexShader *pVS;               // the pointer to the vertex shader
extern ID3D11PixelShader *pPS;                // the pointer to the pixel shader
extern ID3D11Buffer *pVBuffer;                // the pointer to the vertex buffer
extern ID3D11Buffer *pCBuffer;	// the pointer to the constant buffer     
extern ID3D11ShaderResourceView *pTexture; 
extern ID3D11RasterizerState *pRS;


ID3D11ShaderResourceView *Textures[100];


static ID3D11Buffer *pIBuffer;


#pragma endregion Direct3D Vars

///msg Object
extern MSG msg;
//offset zone for tracking
extern int Moffset;

//Master contain of all game objects

#include"ModelObj.h"
#include"TextureObj.h"

// A list of Info for Vertex arrays to be used in the modifiy of the MVBuffer; 

//the Structure of the Vertex data useing in this direct X program
struct VERTEX {FLOAT X, Y, Z; D3DXVECTOR3 Normal; FLOAT U, V;};


bool globalneedToRevertex = false;

static std::vector<Base*> Mlist;
static std::vector<Base*> MlistTest;





static std::vector<TextureObj*> *  TextureList =  new std::vector<TextureObj*>;
static std::vector<ModelObj*> *  ModelList =  new std::vector<ModelObj*>;
static std::vector<playerInfo> * Peerlist = new   std::vector <playerInfo>;




//A windows HWMD and Handle for window fuction and Treading
HWND hWnd;
HANDLE myhandle;

//Camera
float cX,cY,cZ;

float Lx,Ly,Lz;


//pre Define Window size

int SW = 800;
int SH = 600;





//buffers



int offsetI =0;
int offsetV =0;
Ver MVBuffer2[MB * 5];
unsigned int Index[MB *5];














#endif