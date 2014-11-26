//#ifdef BASE_H
//#define BASE_H
#pragma once

class Base
{
public:
	float X, Y, Z;
	virtual void Render(); 
};

void Base::Render()
{
	//dummy command 
};


//#endif