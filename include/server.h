#ifndef INCLUDE_SERVER_H__
#define INCLUDE_SERVER_H__
#endif

#include <winsock.h>
#include <conio.h>
#include <signal.h>
#include <deque>

string logger = "";

int NET_ERROR = 0;
#define NET_MAX_DATA_SIZE 900
#define NET_BAD 0x01
#define NET_TIMEOUT 0x02
#define NET_GOOD 0x00
#define isGoodNet() ((NET_ERROR == NET_GOOD))
#define NET_NULL ("<null>")
#define isNetNull(X) (X==NET_NULL)

#define ORDER_DATA (string("order::data"))
#define ORDER_CHATDATA (string("order::chatdata"))
#define SEND_CHATDATA (string("order::data"))
#define REQUEST_MOVE (string("request::move"))
#define CHECKING_PACKET (string("checking_packet"))
#define ORDER_FAILED_MOVE (string("order::failed_move"))
#define FORCE_DATA_UPDATE (string("order::force_data"))

#undef NET_DEBUG

inline void sendRawNet(SOCKET socket, string data) {
	send(socket, data.c_str(), sizeof(data.c_str()), 0);
}

inline string recvRawNet(SOCKET socket) {
	char data[NET_MAX_DATA_SIZE];
	for(int it=0;it<NET_MAX_DATA_SIZE;++it) {
		data[it] = '\0';
	}
	if(recv(socket, data, NET_MAX_DATA_SIZE, 0)==0x00)  {
		NET_ERROR = NET_GOOD;
	} else {
		NET_ERROR = NET_BAD;
	}
	return string(data);
}

string recvRawNetTimeoutReceiver_output___;
SOCKET recvRawNetTimeoutReceiver_input___;
thread(recvRawNetTimeoutReceiver___) {
	recvRawNetTimeoutReceiver_output___ = recvRawNet(recvRawNetTimeoutReceiver_input___);
	ExitThread(0);
}

inline string recvRawNet(SOCKET socket, long timeout) {
	recvRawNetTimeoutReceiver_input___ = socket;
	recvRawNetTimeoutReceiver_output___ = "<error>";
	HANDLE hThread =( HANDLE ) _beginthread( recvRawNetTimeoutReceiver___, 0, NULL );
	DWORD result = WaitForSingleObject( hThread, timeout );

	if( result == WAIT_OBJECT_0 ) {
		if(recvRawNetTimeoutReceiver_output___=="<error>") {
			NET_ERROR = NET_BAD;
			return "";
		} else {
			return recvRawNetTimeoutReceiver_output___;
		}
	} else if( result == WAIT_TIMEOUT ){
		NET_ERROR = NET_TIMEOUT;
		return "";
	}

	if(recvRawNetTimeoutReceiver_output___=="<error>") {
		NET_ERROR = NET_BAD;
		return "";
	}

	return recvRawNetTimeoutReceiver_output___;
}

inline void sendNet(SOCKET socket, string data) {
	NET_ERROR = NET_GOOD;

	DEBUG({
		cout<<"[Connection] to "<<socket<<": sendNet("<<data<<")\n";
		logger+="[Connection] to "+intToStr(socket)+": sendNet("+data+")\n";
		cout.flush();
	});
	
	const char* buffer = (data+"#").c_str();
	const int length = data.size()+1;
	size_t i = 0;
    for (i = 0; i < length; i += send(socket, buffer, length - i, 0));
}

deque <string> recv_stack;
inline string recvNet(SOCKET socket) {
	NET_ERROR = NET_GOOD;

	if(recv_stack.size()>0) {
		string pom = recv_stack.back();
		recv_stack.pop_back();
		DEBUG({
			cout<<"[Connection] from "<<socket<<": recvNet("<<pom<<")\n";
			logger+="[Connection] from "+intToStr(socket)+": recvNet("+pom+")\n";
			cout.flush();
		});
		return pom;
	}

	DEBUG({
		cout<<"[Connection] from "<<socket<<": listening...\n";
		logger+="[Connection] from "+intToStr(socket)+": listening...\n";
		cout.flush();
	});

	string result = "\0";
	bool cont = true;
	int it = 0;
	while(cont) {
		++it;
		if(!isGoodNet()) {
			NET_ERROR = NET_TIMEOUT;
			DEBUG({
				cout<<"[Connection] from "<<socket<<": recvNet(TERMINATED_CONNECTION)\n";
				logger+="[Connection] from "+intToStr(socket)+": recvNet(TERMINATED_CONNECTION)\n";
				cout.flush();
			});
			return "";
		}
		Sleep(1);
		result += recvRawNet(socket);
		result += "##";
		const int len = result.size();
		string buf = "";
		for(int it=0;it<len;++it) {
			if(result[it]=='#') {
				if(buf!="") {
					recv_stack.push_front(buf);
				}
				buf = "";
			} else {
				buf += "0";
				buf[buf.size()-1] = result[it];
			}
		}

		if(recv_stack.size()>0) {
			string pom = recv_stack.back();
			recv_stack.pop_back();
			DEBUG({
				cout<<"[Connection] from "<<socket<<": recvNet("<<pom<<")\n";
				logger+="[Connection] from "+intToStr(socket)+": recvNet("+pom+")\n";
				cout.flush();
			});
			return pom;
		} else {
			DEBUG({
				cout<<"[Connection] from "<<socket<<": recvNet("<<""<<")\n";
				logger+="[Connection] from "+intToStr(socket)+": recvNet("+""+")\n";
				cout.flush();
			});
			return "";
		}

		/*if(result[len-1]=='#') {
		  result.erase(result.begin()+len-1);
			#ifdef NET_DEBUG
				cout<<"[Connection] from "<<socket<<": recvNet("<<result<<")\n";
				logger+="[Connection] from "+intToStr(socket)+": recvNet("+result+")\n";
				cout.flush();
			#endif
			return result;
		}*/
	}
}

namespace server {

	inline string levmap_tostr();

	bool global_chat_changed = false;

	vector<SOCKET> sockets;

	inline void postChat(string mes) {
		//global_chat_changed = true;
		server_group_chat.push_back(mes);
	}

	inline void whenPlayerMoves_server();

	class netenemy_client : public aienemy {
		public:
			SOCKET socket;

			netenemy_client() {
				initClass(this);
			}
			inline bool isNetEnemy() {
				return true;
			}
			inline void nextStep() {

   			}

			inline bool isUserEnemy() {
				return false;
			}

			vector<netenemy_client*> reg;
			inline aienemy* factory_produceEnemy() {
				netenemy_client* pom;
				reg.push_back(pom);
				reg[reg.size()-1] = new netenemy_client();
				return reg[reg.size()-1];
			}
	} netenemy_client_initializer;

	bool runserver = false;

	inline string serverInterpretCommand(string cbuf);

	thread(serverCmdInterpreterThread) {
		/*string cbuf = "";
		while(runserver) {
			cin>>cbuf;
			serverInterpretCommand(cbuf);
			cout.flush();
			if(!runserver) {
				endThread();
			}
		}*/
		endThread();
	}

	inline string serverInterpretCommand( string cbuf ) {

		if(cbuf[0]!='`') {
			postChat("[Host] "+cbuf);
			return "";
		} else {
			cbuf = cbuf.substr(1, string::npos);
		}

		string ret = "";

		vector<string> tokens;
		const int siz = cbuf.size();
		string tbuf = "";
		for(int it=0;it<siz;++it) {
			if(cbuf[it]==' ') {
				tokens.push_back(tbuf);
				tbuf="";
			} else {
				tbuf += "?";
				tbuf[tbuf.size()-1] = cbuf[it];
			}
		}
		if(tbuf!="") {
			tokens.push_back(tbuf);
		}
		for(int it=0;it<10;++it) {
			tokens.push_back("<NULL>");
		}

		if(tokens[0]=="exit") {
			runserver = false;
			is_net_game_server = false;
			return ret;
		} else if (tokens[0]=="say") {
			postChat("[Host] "+tokens[1]);
		} else if(tokens[0]=="log.print") {
			ret+=logger;
		} else if(tokens[0]=="cls"||tokens[0]=="clear") {
			logger = "";
		}
		return ret;
	}

	DWORD WINAPI receive_cmds(LPVOID lpParam) {

		SOCKET current_client = (SOCKET)lpParam;

		char buf[100];
		char sendData[100];
		int res;
		
		int errors = 0;
		bool chat_changed = false;
		int chat_log_pos = 0;

		while(runserver) {
			playersNum = playerAiReg.size();
			string s = recvNet(current_client); //recv(current_client,buf,sizeof(buf),0); // recv cmds

			if(chat_log_pos<server_group_chat.size()) {
				chat_changed = true;
			} else {
				chat_changed = false;
			}

			if(!runserver) return 0x00;
			if(!isGoodNet()) {
				if(NET_ERROR == NET_TIMEOUT) {
					++errors;
				} else {
					errors = 0;
				}
			} else {
				errors = 0;
			}
			if(errors>100) {
				cout<<"Client "<<current_client<<" connection terminated!\n";cout.flush();
				ExitThread(0);
			}

			res = 1;
			const char* buf = s.c_str();
			Sleep(10);
			
			if(res == 0) {
				MessageBox(0,"error","error",MB_OK);
				closesocket(current_client);
				ExitThread(0);
			}

   			if(strstr(buf,"exit")) {
				cout << "\nPlayer \n"; cout.flush();
				closesocket(current_client);
				--netclients;
				ExitThread(0);
			} else if(string(buf) == SEND_CHATDATA) {
				string mes = recvNet(current_client);
				postChat(mes);
			} else if(string(buf) == FORCE_DATA_UPDATE) {
				cout<<"Checking packet received: levmap data sent!\n";cout.flush();
				sendNet(current_client, levmap_tostr());
			} else if(string(buf) == CHECKING_PACKET) {

				if(chat_changed) {
					sendNet(current_client, ORDER_CHATDATA);
					Sleep(10);
					sendNet(current_client, server_group_chat[chat_log_pos]);
					++chat_log_pos;
				} else {
					bool order_failiture = false;
					if(playerAiReg[playerRegMove]->isNetEnemy()) {
						can_client_move = false;
						if(((netenemy_client*)playerAiReg[playerRegMove])->socket == current_client) {
								sendNet(current_client,REQUEST_MOVE);
								int movex = -1, movey = -1;
								string buf = "";
								buf = recvNet(current_client);
								if(buf == ORDER_FAILED_MOVE) {
									order_failiture = false;
								} else {
									movex = strToInt(buf);
									buf = recvNet(current_client);
									movey = strToInt(buf);
									if(movex>=0 && movey>=0) {
										levmap_set(movex, movey, playerAiReg[playerRegMove]->marker);
									}
									moveAllPlayers_server();
								}
						} else {
							sendNet(current_client,ORDER_DATA);
							Sleep(10);
							sendNet(current_client, levmap_tostr());
						}
					} else {
						if(playerAiReg[playerRegMove]->isUserEnemy()) {
							can_client_move = true;
						} else {
							can_client_move = false;
							moveAllPlayers_server();
						}
						sendNet(current_client,ORDER_DATA);
						Sleep(10);
						sendNet(current_client, levmap_tostr());
					}
				}


			} else {
				strcpy(sendData,"Invalid cmd\n");
				Sleep(10);
				send(current_client,sendData,sizeof(sendData),0);
			}
			
		}
	}   

	inline void receiveCurIPAdress__() {
	    char ac[80];
	    if (gethostname(ac, sizeof(ac)) == SOCKET_ERROR) {
	        cerr << "Error " << WSAGetLastError() <<
	                " when getting local host name." << endl;
	        return;
	    }
	    string str(ac);
	    curiphostname=str;
	    //curiphostname
	    
	    struct hostent *phe = gethostbyname(ac);
	    if (phe == 0) {
	        cerr << "Yow! Bad host lookup." << endl;
	        return;
	    }
	
	    for (int i = 0; phe->h_addr_list[i] != 0; ++i) {
	        struct in_addr addr;
	        memcpy(&addr, phe->h_addr_list[i], sizeof(struct in_addr));
	        curip = inet_ntoa(addr);
	    }
	    
	}


	thread(runServer___) {

		 //removeAllPlayers();

		 runserver = true;
		 cout << "Starting up multi-threaded TCP server by KOrUPt\n"; cout.flush();
		 SOCKET sock;
		 DWORD thread;
		 WSADATA wsaData;
		 sockaddr_in server;
	
		 int ret = WSAStartup(0x101,&wsaData);
		  
		 if(ret != 0) {
		    cout<<"[!] Cannot setup server (WSAStartup error).\n";
			return;
		 }
		 receiveCurIPAdress__();
		   
		 server.sin_family=AF_INET;
		 server.sin_addr.s_addr=INADDR_ANY;
		 server.sin_port=htons(123);
		  
		 sock=socket(AF_INET,SOCK_STREAM,0);
		  
		 if(sock == INVALID_SOCKET) {
			cout<<"[!] Cannot setup server (ip host is invliad or not avaliable).\n";
			return;
		 }
		   
		 if( bind(sock,(sockaddr*)&server,sizeof(server)) !=0 ) {
			cout<<"[!] Cannot setup server (no connection).\n";
		    return;
		 }

		 if(listen(sock,5) != 0) {
			cout<<"[!] Cannot setup server (no connection).\n";
		    return;
		 }
		  
		 SOCKET client;
		  
		 sockaddr_in from;
		 int fromlen = sizeof(from);

		 beginThread(serverCmdInterpreterThread);
		 //moveAllPlayers();
	     while(runserver) {
			client = accept(sock,(struct sockaddr*)&from,&fromlen);
			cout<<"Client connected\n"; cout.flush();
			Sleep(250);
			sendNet(client, "connection_status{connected}");
			Sleep(10);
			string buf = str(rndNewEnemyMarker());
			sendNet(client, str(rndNewEnemyMarker()));
			sockets.push_back(client);

			putNewPlayer(netenemy_client_initializer.factory_produceEnemy());
			((netenemy_client*) playerAiReg[playerAiReg.size()-1])->marker = buf[0];
			((netenemy_client*) playerAiReg[playerAiReg.size()-1])->socket = client;
			
			++netclients;
			CreateThread(NULL, 0,receive_cmds,(LPVOID)client, 0, &thread);

		 }
		  
		cout<<"[!] Press any key to back to main menu...\n";
		cout.flush();
		getch();
		system("COLOR 07");

		is_net_game_server = false;
		update_menu_state = true;
		menu_state = 0;
		can_client_move = true;
		is_game_made = false;
		is_net_game_client = false;
		runserver = false;
		closesocket(sock);
		WSACleanup();
		ExitThread(0);
	}

	inline void runServer() {
		menu_state = 99;
		update_menu_state=true;
		is_net_game_server = true;
		can_client_move = false;
		system("cls");
		system("COLOR 0A");
		//moveAllPlayers_server();
		beginThread(runServer___);
	}


	inline string levmap_tostr() {
		string result = "";
		for(int y=0;y<ny*3;++y) {
			for(int x=0;x<nx*3;++x) {
					result+=intToStr(levmap_get(x,y))+";";
			}
		}
		result+=";0;0;0";

		result+=";[";
		result+="0."+intToStr(playerRegMove)+";";
		//result+="0."+intToStr(playerAiReg.size())+";";
		for(int it=0;it<playerAiReg.size();++it) {
			if(playerAiReg[it]->isNetEnemy()||playerAiReg[it]->isUserEnemy()) {
				result+=str(playerAiReg[it]->marker)+".User"+";";
			} else {
				result+=str(playerAiReg[it]->marker)+"."+playerAiReg[it]->enemy_typename+";";
			}
		}
		result+=";]";

		return result;
	}
	
}

using namespace server;
