#ifndef BASICOMM_H
#define BASICCOMM_H




/*
NOTE- This is the prerequist for this code to work 

IMPORANT
1)You will need to put the include POCO folders inside your project in the Folder your Code is located in, TIP it is th efolder that contain your Main.cpp.

2)You will most likey need to include a path to the POCO folders(see expaned for full list of folders) in Project Option/Settings , use "$(ProjectDir)\" then the following file path EXAMPLE "$(ProjectDir)\Poco\Net\Include",
  what this does is replaces "$(ProjectDir)\" with the file path to your project this is if you take/pass your project arround multi compter or on a Memory stick. 

3)You will need to put Both pocoNetd.DLL and pocoFoundationd.DLL in Your Folder with the compiled EXE other wise your program will nto work, TIP this is the First DEBUG folder.



EXPANED
////////////////////////////////////////////
This are done under the C/C++ >> General >> Addtional Includes Directories
$(ProjectDir)\Poco\Net\Include
$(ProjectDir)\poco\foundation\include

This are done under the Linker >> General >> Addtional Libary Directories
$(ProjectDir)\poco\lib
////////////////////////////////////////////





This part of the code with need to be put ether in your main or in a shared Resource Header.

////////////////////////////////////////////

// all the poco 
#include"Poco\Net\DatagramSocket.h"
#include"Poco\Net\IPAddress.h"
#include"Poco\Net\Net.h"
#include"Poco\Net\SocketAddress.h"
#include"Poco\Net\Socket.h"

#include <windows.h> // needed for threading
#include <stdio.h> //also needed for threading
#include <process.h> //need for threading

#include<iostream>
#include<string>
#include<istream>

struct info
{
	std::string ID;
	std::string IP;
	unsigned short port 
};



#include <WinSock2.h>//stuff for native networking useing winsock



//this will included the required libary via complier commands/Flags insted of being inculded via Project settings
#pragma comment(lib, "pocoNetd.lib")
#pragma comment(lib, "pocoFoundationd.lib")
//winsock lib
#pragma comment(lib, "ws2_32.lib")


////////////////////////////////////////////



      __      __   ____    _   _                           _______   _                                                 
     / /     / /  / __ \  | | (_)                         |__   __| | |                                                
    / /     / /  | |  | | | |  _  __   __   ___   _ __       | |    | |__     __ _   _   _    ___   _ __    ___   _ __ 
   / /     / /   | |  | | | | | | \ \ / /  / _ \ | '__|      | |    | '_ \   / _` | | | | |  / _ \ | '__|  / _ \ | '__|
  / /     / /    | |__| | | | | |  \ V /  |  __/ | |         | |    | | | | | (_| | | |_| | |  __/ | |    |  __/ | |   
 /_/     /_/      \____/  |_| |_|   \_/    \___| |_|         |_|    |_| |_|  \__,_|  \__,_|  \___| |_|     \___| |_|   
  ______   ______   ______   ______   ______   ______   ______   ______   ______   ______   ______   ______   ______                                                                                                                                                                                                                                                                                  
 |______| |______| |______| |______| |______| |______| |______| |______| |______| |______| |______| |______| |______|  
                                                                                                                      
																													  
*/


#include "resources.h"
#include "PacketStorage.h"



class Comm
{
public:
	
	info * IF;
	HANDLE  MH;
	HRESULT  H;

	///constor/Destructor
	Comm();
	~Comm();


	// public func
	void SEND(); 
	void RECIVE();
	void TIMER();
	void setup(); // currenty set up in a chat client style,current only need the 
	void _getLocalIP(char * ip);


	void DummyCmd(); // random Nop command

	void timer();
	void writelog(char * stuff); //write to a log useful for debug ect

	unsigned int heart; //redumentry varible for checking that the peer is still achtive, NOTE-for now Heart with always be "3"
	unsigned short NetworkState; //keep treak of the network state will be change heavry from program to program a sit need to be tailer to it.
	unsigned short LastNetworkState; //keep track of the last change in network state

	int HeartIntervalsCounter;//keep track of time between"heartBeats"



	void send(short option); //the REAL send function-contains the send code to send information
	

	void recive(); // The REAL recive function-contains the code to recive information

private:
	


	/* 
	thread magic- ok this im still a litte(alot) unsure how it works,but basicly this function allow the class "Comm"(this class) to Run it own Member functions inside
	of it own object.
	
	static void Magic(void * ptr){
		reinterpret_cast<Comm *>(ptr)->send();
	};
	*/
	static void Magic1(void * ptr){
		reinterpret_cast<Comm *>(ptr)->recive();
	};

		static void Magic3(void * ptr){
		reinterpret_cast<Comm *>(ptr)->timer();
	};
};



Comm::~Comm()
{

	delete &IF;
	delete &MH;
	delete &H;
//	delete &code;
}

Comm::Comm()
{
	IF = new info;
	MH = new HANDLE;
	heart = 3;
	NetworkState = 0;
	LastNetworkState = 1;
 
}

void Comm::RECIVE()
{
	MH = (HANDLE)_beginthread(&Comm::Magic1,0,this);
}


void Comm::SEND()
{
	//MH = (HANDLE)_beginthread(&Comm::Magic,0,this);
}

void Comm::DummyCmd()
{
	std::cout  << "Dummy command done" << std::endl;
}

void Comm::recive()
{

	Poco::Net::SocketAddress sender;
	Poco::Net::SocketAddress sa(Poco::Net::IPAddress(),37776);
	Poco::Net::DatagramSocket rec(sa);

	
	//printf("failed to bind");


	char ReceivedBuffer[1024];
	
	while(true)
	{
		//rec.connect(sa);
		rec.receiveBytes(ReceivedBuffer,sizeof(ReceivedBuffer),0);


		switch(ReceivedBuffer[0])
		{
		case  '0':

		break;

		case  '1':

		break;

		case  '2':

		break;

		case  '3':
			{
				ClientConnectConfirm * SP = new ClientConnectConfirm;
				std::memcpy(SP,ReceivedBuffer,sizeof(struct ClientConnectConfirm));

				if(SP->confirm == '1')
				{
					Connected = true;
				}

				std::cout << "Connection confirmed \n";

			}
		break;

		case '4':
			ServerMsg * SP = new ServerMsg;
			std::memcpy(SP,ReceivedBuffer,sizeof(struct ClientConnectConfirm));

			switch(SP->msg)
			{
			case '0':
				printf("Server: error unknowed\n");
				break;

			case '1':
				printf("Server: Connection refused Max clients reached \n");
					break;

			default:
				printf("Defaulted unable to chose a Error msg IllFormed or incorect packet");
				break;



			}

			break;

		}









	}

}


void Comm::send(short option)
{

	
	std::string ID;
	std::string IP;
	int port;



	Poco::Net::SocketAddress addr(Poco::Net::IPAddress(IF->IP),IF->port);
	Poco::Net::DatagramSocket send;
	send.connect(addr);


	int temp2;
	int number = option;
	switch(number)
		{	
	case 0:
		{
			Ping * SP = new Ping;
			SP->PacketType ='0';
			send.sendBytes((char *)SP,sizeof(struct Ping),0);
		}
	break;
		case 1:
				{
					printf("sending case 1:simple packet \n");
					simplepacket *SP = new simplepacket;
					SP->PacketType ='1';
					SP->Return = 5;
					SP->test = 10;
					SP->test2 = '5';
					send.sendBytes((char *)SP,sizeof(struct simplepacket),0);
				}
			break;

			case 2:
				{
					printf("sending case 2:advance packet \n");
					AdvancePacket *SP = new AdvancePacket;
					SP->PacketType = '2';
					SP->Return = 5;
					SP->ID = IF->ID;
					send.sendTo((char *)SP,sizeof(struct AdvancePacket),addr);
				}
			break;
			
			case 3:
				{
					ClientConnect * SP = new ClientConnect;
					SP->PacketType = '3';
					SP->ID = IF->ID;
					_getLocalIP(SP->IP);
					//std::cout << SP->IP << "test" << "\n";
					send.sendBytes((char*)SP,sizeof(struct ClientConnect),0);
				}
				break;

		
			default:
				printf("Command switch sstatment has Defaulted \n");
			break;
	}

}





void Comm::setup()
{

	




	std::cout << "-----------------------" << std::endl;
	std::cout << "---Basic UDP Echange---" << std::endl;
	std::cout << "---------setup---------" << std::endl;
	 
	
	bool  correct = false;
	bool  end = false;
	while(end == false)
	{

		while(correct == false)
		{
			std::cout << "Enter Player ID: ";
			std::getline(std::cin, IF->ID);
		
			
				if(IF->ID == "")
				{

					std::cout << "ID has not been entered" << std::endl;
				}
				
				if(IF->ID != "")
				{
					correct = true;
					
				}

		}

		correct =false;

		while (correct == false)
		{
		std::cout << "Enter Server IP: ";
		std::getline(std::cin ,IF->IP);

		
				if(IF->IP == "")
				{
					std::cout << "IP has not been entered" << std::endl;
				}
				if(IF->IP != "")
				{
					correct = true;
					
				}

		}

		correct = false;

		while(correct == false)
		{
			std::string tmp;
			std::cout << "Enter Server Port: ";
			std::cin >> IF->port;

			if(IF->port > 65545)
			{
				std::cout << "No Port Entered" << std::endl;
			}


			if(IF->port < 65545 & IF->port > 1)
			{
				//IF->port
				correct = true;
			}



		}

		end = true;
	}

	
}



void Comm::_getLocalIP(char * ip)
{

WSADATA wsa_Data;
int wsa_ReturnCode = WSAStartup(0x101,&wsa_Data);

// Get the local hostname
char szHostName[255];
gethostname(szHostName, 255);
struct hostent *host_entry;
host_entry=gethostbyname(szHostName);
char * localip;
localip = inet_ntoa (*(struct in_addr *)*host_entry->h_addr_list);
WSACleanup();

std::strncpy(ip,localip,16);

}



void Comm::writelog(char * stuff)
{


std::ofstream myfile;
  myfile.open ("Log.txt");
  myfile << "\n" << stuff << "\n";
  myfile.close();



}



void Comm::timer()
{
	int timewaster = 0;
	for (int i = 0;i <= 1000000;i++)
	{

		timewaster = timewaster +5;

	}

		
	
}


#endif