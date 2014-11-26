#pragma once

//This file will contain all the diffrent Structures used by the program for the simplicy of them being all in one place instead of being scatered

#include "resources.h"


struct Ping //'0
{
unsigned char PacketType;
unsigned int Return;
};


struct simplepacket //1
{
	unsigned char PacketType;
	unsigned int Return;
	int test;
	char test2;

};



struct AdvancePacket//2
{
	unsigned char PacketType;
	std::string ID;
	unsigned int Return;

};


struct ClientConnect//3
{
	unsigned char PacketType;
	std::string ID;
	char IP[16];
};

struct ClientConnectConfirm//4
{
	unsigned char PacketType;
	char confirm;
	
};


struct ServerMsg//5
{
	unsigned char PacketType;
	char msg;

};

struct Location//6
{
	unsigned char PacketType;
	std::string ID;
	int x,y,z;

};

struct AddPlayer//7
{
	unsigned char PacketType;
	std::string ID;
	char IP[16];
	int x,y,z;

};

/*

NOTES
-----

The first part of a structure inteded to be a packet need to be a unsigned char so that you can use use the first of the reclive buffer to check it packet type
also the first bype of a struct will be the first byte of what eve is the first varible in your struct












*/