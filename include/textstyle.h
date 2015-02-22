

class styled_text {
	private:
		struct styled_text_char {
			char ch = 0x00;
			bool foreground_r = true,
				 foreground_g = true,
			 	 foreground_b = true,
				 background_r = false,
				 background_g = false,
				 background_b = false;
		};
		typedef std::vector< styled_text_char > styled_string;
		
		styled_string text;
		
		inline styled_string stringToStyledString(std::string str) {
			styled_text_char ch;
			styled_string ret;
			
			const int len = str.size();
			for(int it=0;it<len;++it) {
				ch.ch = str[it];
				ret.push_back(ch);
			}
			return ret;
		} 
		
		inline std::string styledStringToString(styled_string str) {
			std::string ret = "";
			
			const int len = str.size();
			for(int it=0;it<len;++it) {
				ret += stringify(str[it].ch);
			}
			return ret;
		}
		
		inline std::string generateStyledStringRepresentation(styled_string str) {
			std::string ret = "", ch = "", stylech = "";
			
			const int len = str.size();
			for(int it=0;it<len;++it) {
				ch = stringify(str[it].ch);
				stylech = "";
				if(str[it].foreground_r) {
					stylech += "R";
				}
				if(str[it].foreground_g) {
					stylech += "G";
				}
				if(str[it].foreground_b) {
					stylech += "B";
				}
				if(str[it].background_r) {
					stylech += "r";
				}
				if(str[it].background_g) {
					stylech += "g";
				}
				if(str[it].background_b) {
					stylech += "b";
				}
				
				ret += "~" + stylech + "&" + ch;
			}
			return ret;
		}
		
	public:
		
		styled_text() {
			text.clear();
		}
		
		styled_text(std::string rawtext) {
			text = stringToStyledString(rawtext);
		}
		
		/*inline void colourRegexp(regex reg, bool fr=true, bool fg=true, bool fb=true, bool br=true, bool bg=true, bool bb=true) {
			string str = getRawText();
			smatch sm;
			regex_search(str, sm, reg);
			
			cout<<"finding matches in \""<<str<<"\".\n";
			const int siz = sm.size();
			cout<<siz<<" matches found.\n";
			for (int i=0; i<siz; ++i) {
				cout<<"Colour from "<<sm.position(i)<<" to "<<(sm.position(i)+sm[i].length())<<"\n";
				paintChar(sm.position(i), sm.position(i)+sm[i].length(), fr, fg, fb, br, bg, bb);
			}
		}*/
		
		inline void setRawText(std::string rawtext) {
			text = stringToStyledString(rawtext);
		}
		
		inline std::string getRawText() {
			return styledStringToString(text);
		}
		
		inline std::string getText() {
			return generateStyledStringRepresentation(text);
		}
		
		inline void erase(int pos, int len) {
			text.erase(pos+text.begin(), text.begin()+pos+len);
		}
		
		inline void eraseTo(int pos, int endpos) {
			text.erase(pos+text.begin(), text.begin()+endpos);
		}
		
		inline char getChar(int index) {
			return text[index].ch;
		}
		
		inline bool& isCharPaintedForegroundR(int index) {
			return text[index].foreground_r;
		}
		
		inline bool& isCharPaintedForegroundG(int index) {
			return text[index].foreground_g;
		}
		
		inline bool& isCharPaintedForegroundB(int index) {
			return text[index].foreground_b;
		}
		
		inline bool& isCharPaintedBackgroundR(int index) {
			return text[index].background_r;
		}
		
		inline bool& isCharPaintedBackgroundG(int index) {
			return text[index].background_g;
		}
		
		inline bool& isCharPaintedBackgroundB(int index) {
			return text[index].background_b;
		}
		
		inline void paintCharForegroundR(int index, int to, bool state=true) {
			for(int it=index;it<to;++it) text[it].foreground_r = state;
		}                                   
		
		inline void paintCharForegroundR(int index, bool state=true) {
			paintCharForegroundR(index, index+1, state);
		}
		
		inline void paintCharForegroundG(int index, int to, bool state=true) {
			for(int it=index;it<to;++it) text[it].foreground_g = state;
		}
		
		inline void paintCharForegroundG(int index, bool state=true) {
			paintCharForegroundG(index, index+1, state);
		}
		
		inline void paintCharForegroundB(int index, int to, bool state=true) {
			for(int it=index;it<to;++it) text[it].foreground_b = state;
		}
		
		inline void paintCharForegroundB(int index, bool state=true) {
			paintCharForegroundB(index, index+1, state);
		}
		
		inline void paintCharBackgroundR(int index, int to, bool state=true) {
			for(int it=index;it<to;++it) text[it].background_r = state;
		}
		
		inline void paintCharBackgroundR(int index, bool state=true) {
			paintCharBackgroundR(index, index+1, state);
		}
		
		inline void paintCharBackgroundG(int index, int to, bool state=true) {
			for(int it=index;it<to;++it) text[it].background_g = state;
		}                                   
		
		inline void paintCharBackgroundG(int index, bool state=true) {
			paintCharBackgroundG(index, index+1, state);
		}
		
		inline void paintCharBackgroundB(int index, int to, bool state=true) {
			for(int it=index;it<to;++it) text[it].background_b = state;
		}
		
		inline void paintCharBackgroundB(int index, bool state=true) {
			paintCharBackgroundB(index, index+1, state);
		}
		
		inline void paintCharBackground(int index, int to, bool r=true, bool g=true, bool b=true) {
			paintCharBackgroundR(index, to, r);
			paintCharBackgroundG(index, to, g);
			paintCharBackgroundB(index, to, b);
		}
		
		inline void paintCharBackground(int index, bool r=true, bool g=true, bool b=true) {
			paintCharBackground(index, index+1, r, g, b);	
		}
		
		inline void paintCharForeground(int index, int to, bool r=true, bool g=true, bool b=true) {
			paintCharForegroundR(index, to, r);
			paintCharForegroundG(index, to, g);
			paintCharForegroundB(index, to, b);
		}
		
		inline void paintCharForeground(int index, bool r=true, bool g=true, bool b=true) {
			paintCharForeground(index, index+1, r, g, b);	
		}
		
		
		inline void paintChar(int index, int to, bool fr=true, bool fg=true, bool fb=true, bool br=true, bool bg=true, bool bb=true) {
			paintCharForeground(index, to, fr, fg, fb);
			paintCharBackground(index, to, br, bg, bb);
		}
		
		inline void paintChar(int index, bool fr=true, bool fg=true, bool fb=true, bool br=true, bool bg=true, bool bb=true) {
			paintChar(index, index+1, fr, fg, fb, br, bg, bb);
		}
		
	
};
