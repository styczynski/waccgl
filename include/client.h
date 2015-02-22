#ifndef INCLUDE_CLIENT_H__
#define INCLUDE_CLIENT_H__
#endif


inline void levmap_fromstr(string data) {
	for(int y=0;y<ny*3;++y) {
		for(int x=0;x<nx*3;++x) {
			levmap_set(x,y,0);
		}
	}

	disp = "levmap = {"+data+"}";
	removeAllPlayers();
	string buf = "";
	const int len = data.size();
	int x = 0;
	int y = 0;
	bool mode = false;
	bool marked_zero = false;
	for(int it=0;it<len;++it) {

		if(data[it]=='[') {
			mode = true;
		} else if(data[it]==']') {
			mode = false;
		} else if(data[it]==';') {
			if(mode) {
				char mark_ = buf[0];
				if(buf.size()>2) {
					string data = buf.substr(2);
					if(mark_=='0'&&(!marked_zero)) {
						playerRegMove = strToInt(data);
						marked_zero = true;
					} else {
						putNewPlayer(enemy_virtual_initializer.factory_produceEnemy());
						((enemy_virtual*) playerAiReg[playerAiReg.size()-1])->marker = buf[0];
						((enemy_virtual*) playerAiReg[playerAiReg.size()-1])->enemy_typename = data;
					}
				}
				
				buf="";
			} else {
				if(buf!="") {
					if(x<nx*3&&y<ny*3) {
						levmap_set(x,y,(char)strToInt(buf));
					}
					++x;
					if(x>=nx*3) {
						x = 0;
						++y;
					}
					if(y>=ny*3) {
						y = (ny*3)-1;
					}
				}
				buf="";
			}
			
		} else {
			buf+=str(data[it]);
		}
	}
}


namespace client {

	char client_marker = '?';
	bool client_initialized = false;
	int client_step_interval = 0;

	#define SIGINT 2
	#define SIGKILL 9
	#define SIGQUIT 3
	SOCKET sock, client;

	inline void forceClientUpdate() {
		sendNet(sock, FORCE_DATA_UPDATE);
		string buf = recvNet(sock);
		levmap_fromstr(buf);
	}

	/*decl_thread(client_updater) {
		while(runapp) {
			if(is_net_game_client) {
				forceClientUpdate();
				redraw();
			}
			Sleep(1000);
		}
		end_thread();
	}*/

	string client_chat_to_send = "";

	inline void clientPostMessage(string data) {
		client_chat_to_send = "[" + str(client_user_move_marker) + "]" + data;
	}

	inline void clientStep(bool quit_on_move_request = false) {
		if(!client_initialized) {
			return;
		}
		++client_step_interval;
		if(client_step_interval<1000) {
			return;
		} else {
			client_step_interval = 0;
		}

		//retry_connection:
		string buf = "";

		//Sleep(10);
		if(client_chat_to_send!="") {
			sendNet(sock, SEND_CHATDATA);
			Sleep(10);
			sendNet(sock, client_chat_to_send);
			client_chat_to_send = "";
			return;
		}
		sendNet(sock, CHECKING_PACKET);
		buf = recvNet(sock);

		if(buf == ORDER_DATA) {
			buf = recvNet(sock);
			//if(!isGoodNet()) {
			//	goto retry_connection;
			//}
			//Odbiór danych planszy
			levmap_fromstr(buf);
			can_client_move = false;
		}
		if(buf == ORDER_CHATDATA) {
			group_chat.push_back(recvNet(sock));
		}
		if(buf == REQUEST_MOVE) {
			//if(quit_on_move_request) {
			//	return;
			//}
			can_client_move = true;

			if(client_user_move_x<0||client_user_move_y<0) {
				sendNet(sock, ORDER_FAILED_MOVE);
			} else {
				//Trzeba siê ruszyæ...
				//sendNet(...);
				sendNet(sock, intToStr(client_user_move_x));
				Sleep(50);
				sendNet(sock, intToStr(client_user_move_y));
				client_user_move_x=-1;
				client_user_move_y=-1;
				Sleep(50);
				clientStep(true);
			}
			
		}
	}

	void s_handle(int s) {
	    if(sock)
	       closesocket(sock);
	    if(client)
	       closesocket(client);
	    WSACleanup();
	    Sleep(1000);
	    cout<<"EXIT SIGNAL :"<<s; cout.flush();
	    exit(0);
	}
	 
	 
	void s_cl(char *a, int x) {
	    cout<<a;
	    s_handle(x+1000);
	}
	 

	DWORD poll;
	int res,i=1,port=999;
	char buf[100];
	char msg[100] = "";
	char ip[15];
	WSADATA data;

	void exitClient(void);
	int runClient() {
		atexit(exitClient);
		removeAllPlayers();
		//test.blockMouse(true);

		client_user_move_x=-1;
		client_user_move_y=-1;

	    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	    SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	    SetConsoleTitle(" --===-- Styczynsky Digital Systems' Net Client 1.0 --===--");
	    
	    is_net_game_client = true;
	     
	    signal(SIGINT,s_handle);
	    signal(SIGKILL,s_handle);
	    signal(SIGQUIT,s_handle);
	     
	    cout<<"\t[ Styczynsky Digital Systems' Net Client 1.0 ]\n W E L C O M E !";cout.flush();

	    cout<<"\n\n\n\t\tEnter IP to connect to: ";cout.flush();
		const char* cnstip = string("192.168.2.2").c_str();
		for(int it=0;it<15;++it) ip[it] = cnstip[it];

		gets(ip);
	     
	    sockaddr_in ser;
	    sockaddr addr;
	     
	    ser.sin_family=AF_INET;
	    ser.sin_port=htons(123);                    //Set the port
	    ser.sin_addr.s_addr=inet_addr(ip);      //Set the address we want to connect to
	     
	    memcpy(&addr,&ser,sizeof(SOCKADDR_IN));
	     
	    res = WSAStartup(MAKEWORD(1,1),&data);      //Start Winsock
	    cout<<"\n\nWSAStartup"
	        <<"\nVersion: "<<data.wVersion
	        <<"\nDescription: "<<data.szDescription
	        <<"\nStatus: "<<data.szSystemStatus<<endl;cout.flush();
	 
	    if(res != 0)
	        s_cl("WSAStarup failed",WSAGetLastError());
	 
	    sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);       //Create the socket
	        if(sock==INVALID_SOCKET )
	            s_cl("Invalid Socket ",WSAGetLastError());
	        else if(sock==SOCKET_ERROR)
	            s_cl("Socket Error)",WSAGetLastError());
	        else
	            cout<<"Socket Established"<<endl;cout.flush();
	     
	     
	    	res=connect(sock,&addr,sizeof(addr)); //Connect to the server
	        if(res !=0 ) {
	            s_cl("SERVER UNAVAILABLE",res);
	        } else {
	            cout<< "\nConnected to Server: ";cout.flush();
	            memcpy(&ser,&addr,sizeof(SOCKADDR));
	        }

		   string s = recvNet(sock);
		   //ret = recv(sock,RecvdData,sizeof(RecvdData),0);
	       if(s == "connection_status{connected}") {
				cout<<"\nConnection estabilished successfuly.\n";
	       } else {
				cout<<"\n[Error!] when connecting - recv = \""<<s<<"\"\n";
	       }
		   string client_marker = recvNet(sock);

			removeAllPlayers();
			putNewPlayer(mainplayer.factory_produceEnemy());
			playerAiReg[playerAiReg.size()-1]->marker = client_marker[0];
			client_user_move_marker = client_marker[0];

		   //client_body_thread = run_thread(client_body);
		   //run_thread(client_body);

			cout<<"\nPlease wait... Initializing...\n";
		    cout.flush();
			Sleep(1000);
			client_initialized = true;
			Sleep(1000);
	    
	}
	
	void exitClient(void) {
		if(!is_net_game_client) {
			return;
		}
		client_initialized = false;
		Sleep(1000);

		is_net_game_client = false;
		sendNet(client, "exit");
		
		closesocket(client);
		WSACleanup();
		bool clear = true;
		DEBUG({
			clear = false;
		});
		if(clear) system("CLS");
		cout<<"Client was disconnected or could not connect the server you've requested.\n";
		cout.flush();
		Sleep(2500);

		DEBUG({
			cout<<"\n\n\n-------------------------------\n[RESULT] Closing client. Please enter any value to continue...\n";
			cout.flush();
			string x = "";
			cin>>x;
		});


		system("CLS");
		runClient();

	}

}

using namespace client;
