
#define UILoop while(runapp)
#define KEYEVENT_DEFAULT 1

static bool consoleEventReader_ready__ = true;

void GetDesktopResolution(int& horizontal, int& vertical) {
   RECT desktop;
   const HWND hDesktop = GetDesktopWindow();
   GetWindowRect(hDesktop, &desktop);
   horizontal = desktop.right;
   vertical = desktop.bottom;
}

class key {
	private:
		char code = 0x00;
		char speccode = KEYEVENT_DEFAULT;

	public:

		key() {
			code = 0x00;
			speccode = KEYEVENT_DEFAULT;
		}

		key(char c1) {
			code = c1;
			speccode = KEYEVENT_DEFAULT;
		}

		key(char c1, char c2) {
			if(c2==0x00) {
				code = c1;
				speccode = KEYEVENT_DEFAULT;
			} else {
				code = c1;
				speccode = c2;
			}
		}

    inline bool operator==(key c) {
      return code == c.code && speccode == c.speccode;
    }

		inline void override(char c1, char c2) {
			if(c2==0x00) {
				code = c1;
				speccode = KEYEVENT_DEFAULT;
			} else {
				code = c1;
				speccode = c2;
			}
		}

		inline bool isNullKey() {
			return code == 0x00;
		}

		inline bool isSpecialKey() {
			return speccode != KEYEVENT_DEFAULT;
		}

		inline char getKeyCode() {
			//if(speccode != KEYEVENT_DEFAULT) return KEYEVENT_DEFAULT;
			return code;
		}

		inline char getKeySpecialCode() {
			return speccode;
		}

};
const static key null_key = key();
#define NULL_KEY null_key

struct console_props {
	std::string window_name;
	int bufferw;
	int bufferh;
	int w;
	int h;
};

struct mouse_info {
	int x;
	int y;
	int x_delta;
	int y_delta;
	int wheel_pos;
	int wheel_pos_delta;
	bool lbutton;
	bool rbutton;
	bool mbutton;
	bool lbutton_changed;
	bool rbutton_changed;
	bool mbutton_changed;
} EMPTY_MOUSE_DATA = {-1, -1, 0, 0, 0, 0, false, false, false, false, false, false};

struct keyboard_info {
	char key;
	bool key_present;
} EMPTY_KEYBOARD_DATA = {0, false};

inline keyboard_info new_keyboard_info(char k) {
	keyboard_info ret;
	ret.key = k;
	ret.key_present = true;
	return ret;
}

DWORD WINAPI consoleEventReader___(LPVOID lpParam);
//DWORD WINAPI consoleInputReader___(LPVOID lpParam);


class console {
	private:
		//friend DWORD WINAPI consoleInputReader___(LPVOID lpParam);
		friend DWORD WINAPI consoleEventReader___(LPVOID lpParam);
		friend class context;

		HANDLE hOut;
		HWND hWndCon;
		CHAR_INFO* buffer;
		int screen_buffer_w = 0;
		int screen_buffer_h = 0;
		const static int w = 400;
		const static int h = 200;
		mouse_info mouse_data;
		std::vector<keyboard_info> keyboard_data;
		bool use_mouse__ = true;
		bool enable_mouse__ = true;
		bool block_mouse__ = false;
		int MAX_FONT_SIZE;
		uint curx;
		uint cury;
		WORD curattrib;
		console_props props;
		std::vector<UINT> availableFontSizes;
		bool reversed_video_mode = false;
		double mouseSensivityX = 1.0;
		double mouseSensivityY = 1.0;

		inline void applyVideoSettings() {
			if(!reversed_video_mode) {
				return;
			}
			for(int y=0;y<h;++y) {
				for(int x=0;x<w;++x) {
					if((buffer[y*w+x].Attributes | 0x4000) != buffer[y*w+x].Attributes) {
						buffer[y*w+x].Attributes *= 0x10;
						buffer[y*w+x].Attributes += (buffer[y*w+x].Attributes-(buffer[y*w+x].Attributes%0x100))/0x100;
						buffer[y*w+x].Attributes -= (buffer[y*w+x].Attributes-(buffer[y*w+x].Attributes%0x1000));
						buffer[y*w+x].Attributes |= 0x4000;
						//|= COMMON_LVB_REVERSE_VIDEO | COMMON_LVB_GRID_RVERTICAL; //BACKGROUND_GREEN;//COMMON_LVB_REVERSE_VIDEO;

					}
				}
			}
		}

	public:

		console(console_props aprops) {
			props = aprops;
			init();
		}

		console() {
			props.window_name = "";
			props.w = -1;
			props.h = -1;
			props.bufferw = -1;
			props.bufferh = -1;
			init();
		}

		inline std::vector<UINT> getAvailableFontSizes() {
			return availableFontSizes;
		}

		inline void clearInputData() {
			mouse_data = EMPTY_MOUSE_DATA;
			keyboard_data.clear();
		}

		inline void enableReversedVideoMode(bool state = true) {
			reversed_video_mode = state;
		}

		inline bool isMouseBlocked() {
			return block_mouse__;
		}

		inline void blockMouse(bool state=true) {
			block_mouse__ = state;
		}

		inline int getMouseX() {
			return mouse_data.x;
		}

		inline int getMouseY() {
			return mouse_data.y;
		}

		inline int getMouseDeltaX() {
			return mouse_data.x_delta;
		}

		inline int getMouseDeltaY() {
			return mouse_data.y_delta;
		}

		inline int getScreenBufferW() {
			return screen_buffer_w;
		}

		inline int getScreenBufferH() {
			return screen_buffer_h;
		}

		inline mouse_info& getMouseInfo() {
			return mouse_data;
		}

		inline std::vector<keyboard_info>& getKeyboardInfoStack() {
			return keyboard_data;
		}

		inline keyboard_info getKeyboardInfo() {
			if(keyboard_data.size()==0) return EMPTY_KEYBOARD_DATA;
			return keyboard_data.back();
		}

		inline char getKeyboardInput() {
			if(keyboard_data.size()==0) return EMPTY_KEYBOARD_DATA.key;
			return keyboard_data.back().key;
		}

		inline char readKeyboardInput() {
			if(keyboard_data.size()==0) return EMPTY_KEYBOARD_DATA.key;

			char buf = keyboard_data.back().key;
			keyboard_data.pop_back();
			return buf;
		}

		inline void waitForKeyInput() {
			while(readKeyboardInput()==EMPTY_KEYBOARD_DATA.key) Sleep(0);
		}

		inline void waitForUserInput() {
			mouse_data.x_delta = 0;
			mouse_data.y_delta = 0;
			while(readKeyboardInput()==EMPTY_KEYBOARD_DATA.key && mouse_data.x_delta==0 && mouse_data.y_delta==0) {
				Sleep(0);
				updateMousePosition();
			}
		}

		inline bool isMouseEnabled() {
			return enable_mouse__;
		}

		inline void enableMouse(bool state=true) {
			enable_mouse__ = state;
		}

		inline bool isMouseAvailable() {
			return ((enable_mouse__)&&(use_mouse__)&&(!block_mouse__));
		}

		inline double getMouseSensivityX() {
			return mouseSensivityX;
		}

		inline void setMouseSensivityX(double arg0) {
			mouseSensivityX = arg0;
		}

		inline double getMouseSensivityY() {
			return mouseSensivityY;
		}

		inline void setMouseSensivityY(double arg0) {
			mouseSensivityY = arg0;
		}

		inline bool updateMousePosition() {
			if(!enable_mouse__) return false;

			POINT pt;
			RECT rect;
			CONSOLE_FONT_INFO cfi;
			GetCursorPos(&pt);
			ScreenToClient(getHwnd(),&pt);
			GetWindowRect(getHwnd(), &rect);
			int width = rect.right - rect.left;
			int height = rect.bottom - rect.top;
			GetCurrentConsoleFont(getHandle(), TRUE, &cfi);
			int fontw = cfi.dwFontSize.X;
			int fonth = cfi.dwFontSize.Y;
			const int nx = (pt.x)/(fontw/15)*mouseSensivityX;
			const int ny = (pt.y)/(fonth/15)*mouseSensivityY;

			mouse_data.x_delta = nx - mouse_data.x;
			mouse_data.y_delta = ny - mouse_data.y;

			if(nx>=0 && ny>=0 && nx<getScreenBufferW() && ny<getScreenBufferH()) {
				if(mouse_data.x!=nx && mouse_data.y!=ny) {
					use_mouse__ = true;
				}
				mouse_data.x = nx;
				mouse_data.y = ny;
			}

			mouse_data.lbutton_changed = (((GetAsyncKeyState(VK_LBUTTON)!=0)?1:0) != ((mouse_data.lbutton)?1:0));
			if(GetAsyncKeyState(VK_LBUTTON)!=0) {
				mouse_data.lbutton = true;
			} else {
				mouse_data.lbutton = false;
			}

			mouse_data.rbutton_changed = (((GetAsyncKeyState(VK_RBUTTON)!=0)?1:0) != ((mouse_data.rbutton)?1:0));
			if(GetAsyncKeyState(VK_RBUTTON)!=0) {
				mouse_data.rbutton = true;
			} else {
				mouse_data.rbutton = false;
			}

			mouse_data.mbutton_changed = (((GetAsyncKeyState(VK_MBUTTON)!=0)?1:0) != ((mouse_data.mbutton)?1:0));
			if(GetAsyncKeyState(VK_MBUTTON)!=0) {
				mouse_data.mbutton = true;
			} else {
				mouse_data.mbutton = false;
			}

			return true;
		}

		inline HANDLE getHandle() {
			return hOut;
		}

		inline HWND getHwnd() {
			return hWndCon;
		}

		inline int getMaxFontSize() {
			return MAX_FONT_SIZE;
		}

		inline void setMaxFontSize(int size) {
			MAX_FONT_SIZE = size;
		}

		inline void updateFonts() {
			GetConsoleAvailableFontSizes__();
		}

		inline void WINAPI GetConsoleAvailableFontSizes__() {
			availableFontSizes.clear();
			for(int it=0;it<MAX_FONT_SIZE;++it) {
				if(SetConsoleFontSizeEx(it)!=0) {
					availableFontSizes.push_back((UINT)it);
				}
			}
			sort(availableFontSizes.begin(), availableFontSizes.end());

		}

		BOOL WINAPI SetConsoleFont(DWORD fontIndex) {
			HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

			typedef BOOL (WINAPI *PSetConsoleFont)(HANDLE, DWORD);
			static PSetConsoleFont pSetConsoleFont = NULL;

			if(pSetConsoleFont == NULL)
				pSetConsoleFont = (PSetConsoleFont)::GetProcAddress(::GetModuleHandle(_T("kernel32")), "SetConsoleFont");
			if(pSetConsoleFont == NULL) return FALSE;

			return pSetConsoleFont(hOutput, fontIndex);
		}


		BOOL WINAPI SetConsoleFontSizeEx(UINT sizey) {
			HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

			PCONSOLE_FONT_INFOEX font = new CONSOLE_FONT_INFOEX();
		    font->cbSize = sizeof(CONSOLE_FONT_INFOEX);

		    PCONSOLE_FONT_INFOEX font2 = new CONSOLE_FONT_INFOEX();
		    font2->cbSize = sizeof(CONSOLE_FONT_INFOEX);

			GetCurrentConsoleFontEx( hOutput, FALSE, font );
			font->dwFontSize.X = -1;
			font->dwFontSize.Y = sizey;
			SetCurrentConsoleFontEx( hOutput, FALSE, font );

			if(GetCurrentConsoleFontEx( hOutput, FALSE, font2 )==0) {
				return FALSE;
			} else {
				return (font2->dwFontSize.Y==sizey);
			}
			return FALSE;
		}

		UINT WINAPI GetConsoleNearestFontSize(UINT sizey) {
			std::vector<UINT>::iterator it = (std::lower_bound (availableFontSizes.begin(), availableFontSizes.end(), sizey));

			const int pos = it-availableFontSizes.begin();
			const int siz = availableFontSizes.size();

			if(siz<=0||pos>=siz) {
				return 0;
			}

			return availableFontSizes[it-availableFontSizes.begin()];
		}

		BOOL WINAPI SetConsoleFontSize(UINT sizey) {
			return SetConsoleFontSizeEx( GetConsoleNearestFontSize(sizey) );
		}

		BOOL WINAPI SetConsoleCodePage(UINT codePageID) {
			/*typedef BOOL (WINAPI *PSetConsoleCP)(UINT);
			static PSetConsoleCP pSetConsoleCP = NULL;
			static PSetConsoleCP pSetConsoleOutputCP = NULL;

			if(pSetConsoleCP == NULL)
				pSetConsoleCP = (PSetConsoleCP)::GetProcAddress(::GetModuleHandle(_T("kernel32")), "SetConsoleCP");
			if(pSetConsoleCP == NULL) return FALSE;


			if(pSetConsoleOutputCP == NULL)
				pSetConsoleOutputCP = (PSetConsoleCP)::GetProcAddress(::GetModuleHandle(_T("kernel32")), "SetConsoleOutputCP");
			if(pSetConsoleOutputCP == NULL) return FALSE;
			*/

			SetConsoleOutputCP( codePageID );
			SetConsoleCP( codePageID );

			//return pSetConsoleCP(codePageID);
			//pSetConsoleOutputCP(codePageID);
			//return TRUE;
		}

		inline void startAutoKeyReader() {
			DWORD thread;
			CreateThread(NULL, 0,consoleEventReader___,(LPVOID)this, 0, &thread);
		}

		inline void rest() {
			Sleep(0);
		}

		inline void init() {
			std::ios_base::sync_with_stdio(0);
			MAX_FONT_SIZE = 40;
			GetConsoleAvailableFontSizes__();
			SetConsoleFontSize(16);

			hOut = GetStdHandle( STD_OUTPUT_HANDLE );
			hWndCon = GetConsoleWindow();
			mouse_data = EMPTY_MOUSE_DATA;
			keyboard_data.clear();

			//DWORD thread;
			//CreateThread(NULL, 0,consoleEventReader___,(LPVOID)this, 0, &thread);
			//CreateThread(NULL, 0,consoleInputReader___,(LPVOID)this, 0, &thread);

			SMALL_RECT windowSize = {0, 0, 100, 100};

			//props.w = props.h = 0;
			//props.bufferh = props.bufferw = 0;//2000;

			if(props.window_name!="") {
				if(!SetConsoleTitle(props.window_name.c_str())) {
					std::cout << "SetConsoleTitle failed with error " << GetLastError() << std::endl;
					runapp=false;
					return;
				}
			}

			if(props.bufferw>=0&&props.bufferh>=0) {
			    _COORD coord;
   				coord.X = props.bufferw;
    			coord.Y = props.bufferh;

			    if(!SetConsoleScreenBufferSize(hOut, coord)) {
			        std::cout<<"Failure in setting buffer size\n"<<GetLastError();
			        runapp=false;
					return;
		        }

			}

			if(props.h==0||props.w==0) {
				CONSOLE_SCREEN_BUFFER_INFO info;
				GetConsoleScreenBufferInfo(hOut, &info);
				SMALL_RECT rc;
				rc.Left = rc.Top = 0;
				rc.Right = (short)(std::min(info.dwMaximumWindowSize.X, info.dwSize.X) - 1);
				rc.Bottom = (short)(std::min(info.dwMaximumWindowSize.Y, info.dwSize.Y) - 1);

				HWND hConsole = GetConsoleWindow();
				MoveWindow(hConsole, rc.Left, rc.Top, rc.Right, rc.Bottom, TRUE);
				SetConsoleWindowInfo(hOut, true, &rc);
			}

			if(props.w>0&&props.h>0) {
				HWND hConsole = GetConsoleWindow();
				RECT ConsoleRect;
			    GetWindowRect(hConsole, &ConsoleRect);

			    if(!MoveWindow(hConsole, ConsoleRect.left, ConsoleRect.top, props.w, props.h, TRUE)) {
			        std::cout<<"Failure in setting window size\n"<<GetLastError();
			        runapp=false;
					return;
		        }

			}

			buffer = new CHAR_INFO[w*h];
			screen_buffer_w = w;
			screen_buffer_h = h;
			CHAR_INFO none;
			none.Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
			none.Char.AsciiChar = ' ';
			for(int y=0;y<h;++y) {
				for(int x=0;x<w;++x) {
					set(x, y, none);
				}
			}
			curattrib = none.Attributes;
			curx = 0;
			cury = 0;
		}

		inline void wait(int miliseconds) {
		    Sleep(miliseconds);
		}


		inline CHAR_INFO& get(int x, int y) {
			return buffer[y*w+x];
		}

		inline void set(int x, int y, CHAR_INFO val) {
			buffer[y*w+x] = val;
		}

		inline void clearScreen() {
			COORD Position;
		    Position.X = 0;
		    Position.Y = 0;
		    SetConsoleCursorPosition(hOut, Position);
		}

		inline void clear() {
			CHAR_INFO none;
			none.Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
			none.Char.AsciiChar = ' ';
			for(int y=0;y<h;++y) {
				for(int x=0;x<w;++x) {
					set(x, y, none);
				}
			}
		}

		inline void flush() {
			//clear();
			clearScreen();
			applyVideoSettings();
			SMALL_RECT writerect = {0, 0, w-1, h-1};
			HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
			COORD topleft = {0, 0};
			WriteConsoleOutput(hOut, buffer, {w,h}, topleft, &writerect);
		}

		inline void put(int x, int y, char dat) {
			if(dat!=0x00) get(x,y).Char.AsciiChar = dat;
		}

		inline void put(int x, int y, char dat, WORD attrib) {
			get(x,y).Attributes = attrib;
			if(dat!=0x00) get(x,y).Char.AsciiChar = dat;
		}

		inline void setColor(int x, int y, WORD attrib=0x00) {
			get(x,y).Attributes = attrib;
		}

		inline void clearColor(int x, int y) {
			setColor(x, y);
		}

		inline void clearColorRegion(region reg) {
			reg.paint( buffer, w, h, newRegionPainter(CHAR_INFO, {
				element->Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
			}));
		}

		inline void print(int x, int y, char ch) {
			if(ch!=0x00) buffer[y*w+x].Char.AsciiChar = ch;
		}

		inline void print(int x, int y, std::string text) {
			const uint siz = text.size();
			uint dy = 0;
			uint dx = -1;
			for(uint it=0;it<siz;++it) {
				++dx;
				if(text[it]=='\n') {
					++dy;
					dx = -1;
				} else {
					put(x+dx, y+dy, text[it]);
				}
			}
			setCurPos(x+dx+1, y+dy);
		}

		inline void print(int x, int y, std::string text, WORD attrib) {
			const uint siz = text.size();
			uint dy = 0;
			uint dx = -1;
			for(uint it=0;it<siz;++it) {
				++dx;
				if(text[it]=='\n') {
					++dy;
					dx = -1;
				} else {
					put(x+dx, y+dy, text[it], attrib);
				}
			}
			setCurPos(x+dx+1, y+dy);
		}

		inline void print(std::string text) {
			print(curx, cury, text, curattrib);
		}

		inline CHAR_INFO& get() {
			return get(curx, cury);
		}

		inline void setCurPos(int x, int y) {
			curx = x;
			cury = y;
		}

		inline void setCurX(int x) {
			curx = x;
		}

		inline void setCurY(int y) {
			cury = y;
		}

		inline uint getCurX() {
			return curx;
		}

		inline uint getCurY() {
			return cury;
		}

		inline void moveCur(int x, int y) {
			curx += x;
			cury += y;
		}

		inline void setCurAtt(WORD attrib) {
			curattrib = attrib;
		}

		inline WORD& getCurAtt() {
			return curattrib;
		}

		inline void exec( int x, int y, void(*arg)(console&, int,int) ) {
			setCurPos(x,y);
			arg((*this), x,y);
		}

};

/*DWORD WINAPI consoleInputReader___(LPVOID lpParam) {
	while(true) Sleep(1);
	console* cons = (console*)lpParam;
	while(runapp) {
		//char key = _getch();
		char key = _getch();
		cons->use_mouse__ = false;
		cons->getKeyboardInfo().key_present = true;
		cons->getKeyboardInfo().key = key;
		Sleep(15);
	}
	ExitThread(0);
}*/

DWORD WINAPI consoleEventReader___(LPVOID lpParam) {
	#ifndef MOUSE_HWHEELED
	#define MOUSE_HWHEELED 0x0008
	#endif

	DWORD cNumRead, fdwMode, i;
    INPUT_RECORD irInBuf[128];
    int counter=0;

	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD fdwSaveOldMode;
	console* cons = (console*) lpParam;

	if (! GetConsoleMode(hStdin, &fdwSaveOldMode) ) {
        ExitThread(0);
	}

    fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
    if (! SetConsoleMode(hStdin, fdwMode) ) {
        ExitThread(0);
	}

	//cons->getKeyboardInfo().clear();

	while (runapp) {
        if (!ReadConsoleInput(hStdin, irInBuf, 128, &cNumRead)) {

		} else {
	        for (i = 0; i < cNumRead; i++) {
				if(irInBuf[i].EventType == FOCUS_EVENT) {
					cons->clearInputData();
				}
				if(irInBuf[i].EventType == MOUSE_EVENT && irInBuf[i].Event.MouseEvent.dwEventFlags == MOUSE_WHEELED) {
					if(HIWORD(irInBuf[i].Event.MouseEvent.dwButtonState)>120) {
						cons->getMouseInfo().wheel_pos++;
						cons->getMouseInfo().wheel_pos_delta++;
					} else {
						cons->getMouseInfo().wheel_pos--;
						cons->getMouseInfo().wheel_pos_delta--;
					}
				}
				if(irInBuf[i].EventType == KEY_EVENT) {
					if(cons->use_mouse__ && cons->enable_mouse__) {
						cons->use_mouse__ = false;
					} else {
						cons->use_mouse__ = false;
						if(irInBuf[i].Event.KeyEvent.bKeyDown == TRUE) {

							//LEFT_CTRL_PRESSED
							if(irInBuf[i].Event.KeyEvent.dwControlKeyState == ENHANCED_KEY ||
								irInBuf[i].Event.KeyEvent.dwControlKeyState == LEFT_CTRL_PRESSED
							) {
								if(irInBuf[i].Event.KeyEvent.dwControlKeyState == LEFT_CTRL_PRESSED) {
									cons->getKeyboardInfoStack().push_back( new_keyboard_info( irInBuf[i].Event.KeyEvent.wVirtualScanCode + 30 ) );
								} else {
									cons->getKeyboardInfoStack().push_back( new_keyboard_info( irInBuf[i].Event.KeyEvent.wVirtualScanCode ) );
								}

								cons->getKeyboardInfoStack().push_back( new_keyboard_info( -32 ) );
							} else {
								cons->getKeyboardInfoStack().push_back( new_keyboard_info( irInBuf[i].Event.KeyEvent.uChar.UnicodeChar ) );
							}

							/*if(irInBuf[i].Event.KeyEvent.uChar.wVirtualScanCode == ) {

							} else if(irInBuf[i].Event.KeyEvent.uChar.UnicodeChar>0) {
								cons->getKeyboardInfoStack().push_back( new_keyboard_info( irInBuf[i].Event.KeyEvent.uChar.UnicodeChar ) );
							} else if(irInBuf[i].Event.KeyEvent.wVirtualScanCode>0) {
								cons->getKeyboardInfoStack().push_back( new_keyboard_info( irInBuf[i].Event.KeyEvent.wVirtualScanCode ) );
							} else /*if(irInBuf[i].Event.KeyEvent.wVirtualKeyCode>0) {
								cons->getKeyboardInfo().key = irInBuf[i].Event.KeyEvent.wVirtualKeyCode;
								cons->getKeyboardInfo().key_present = true;
							} else*/ {
								//cons->getKeyboardInfo().key = 0;
								//cons->getKeyboardInfo().key_present = false;
							}
						}
					}
				}
	        }
		}
		Sleep(0);
    }
	ExitThread(0);
}

console& operator<<(console& src, std::string text);
console& operator<<(console& src, int data);
console& operator<<(console& src, char ch);

inline console& operator<<(console& src, std::string text) {
	src.print(text);
	return src;
}

inline console& operator<<(console& src, int data) {
	src.print(intToStr(data));
	return src;
}

inline console& operator<<(console& src, char ch) {
	//if(ch!=0x00) src.print(ch);
	std::string text = "x";
	text[0] = ch;
	src.print(text);
	return src;
}
