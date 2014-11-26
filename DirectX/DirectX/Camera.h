#ifndef CAMERA_H
#define CAMERA_H


#include "Base.h"
#include "Resources.h"

class Cam : public Base
{
public:

	Cam();

	void Control();
	void Render();

	//vars
	MSG msg;

};


Cam::Cam()
{

}

void Cam::Render()
{
	Control();
}

void Cam::Control()
{

	// if there is a windows message to process...
        if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
        {

		 if (msg.message == WM_KEYDOWN)
			{
				switch (msg.wParam)
				{

				case 0x57:
					cY = cY + 1.5f;
					break;

				case 0x53:
					cY = cY - 1.5f;
					break;

				case 0x41:
					cX = cX - 1.5f;
					break;

				case 0x44:
					cX = cX + 1.5f;
					break;

				case 0x51:
					cZ= cZ + 1.5f;
					break;
					
				case 0x45:
					cZ= cZ - 1.5f;
					break;
					/*
				case VK_LEFT:
					Lx = Lx + 0.5f;
					break;

				case VK_RIGHT:
					Lx = Lx - 0.5f;
					break;

				case VK_UP:
					Ly = Ly + 0.5f;
					break;
				
				case VK_DOWN:
					Ly = Ly - 0.5f;
					break;
					
					*/




				}
			}
			else 
				{
			
					TranslateMessage( &msg );
					DispatchMessage( &msg );
                
				}
		}



}


#endif