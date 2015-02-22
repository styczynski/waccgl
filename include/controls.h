


class frame : public scene_object {
	private:
		char defbg;
		frame_style fs;

	public:

		frame(int ax, int ay, int aw, int ah) {
			fs = default_frame_style;
			defbg = ' ';
			objx = ax;
			objy = ay;
			objw = aw;
			objh = ah;
		}

		inline void setFrameStyle(frame_style afs=null_frame_style) {
			fs = afs;
		}

		inline void setBackground(char ch) {
			defbg = ch;
		}

		inline void draw(context& arg) {
			int x, y;
			for(int ity=0;ity<objh;++ity) {
				for(int itx=0;itx<objw;++itx) {
					x = itx+objx+parentX;
					y = ity+objy+parentY;
					if(defbg!=0x00) {
						arg.get().put(x, y, defbg);
					}
					if(ity==0) {
						if(itx==0) {
							arg.get().put(x, y, fs.top_left);
						} else if(itx==objw-1) {
							arg.get().put(x, y, fs.top_right);
						} else {
							arg.get().put(x, y, fs.horizontal);
						}
					} else if(ity==objh-1) {
						if(itx==0) {
							arg.get().put(x, y, fs.bottom_left);
						} else if(itx==objw-1) {
							arg.get().put(x, y, fs.bottom_right);
						} else {
							arg.get().put(x, y, fs.horizontal);
						}
					} else {
						if(itx==0||itx==objw-1) {
							arg.get().put(x, y, fs.vertical);
						}
					}

				}
			}
		}

		inline bool isFocusable(context& arg) {
			return false;
		}
};



class textframe : public scene_object {
	private:
		char defbg;
		std::string text;
		frame_style fs;

	public:
		textframe(int ax, int ay, int aw, int ah, std::string atext) {
			fs = default_frame_style;
			defbg = ' ';
			objx = ax;
			objy = ay;
			objw = aw;
			objh = ah;
			text = atext;
		}

		inline void setText(std::string s) {
			text = s;
		}

		inline void addText(std::string s) {
			text += s;
		}

		inline void clearText(std::string s) {
			text = "";
		}

		inline std::string getText(std::string s) {
			return text;
		}

		inline void setFrameStyle(frame_style afs=null_frame_style) {
			fs = afs;
		}

		inline void setBackground(char ch) {
			defbg = ch;
		}

		inline void draw(context& arg) {
			int x, y, tit, siz = text.size();
			bool lockLine = false;
			tit = 0;
			for(int ity=0;ity<objh;++ity) {

				for(int itx=0;itx<objw;++itx) {
					x = itx+objx+parentX;
					y = ity+objy+parentY;
					if(defbg!=0x00) {
						arg.get().put(x, y, defbg);
					}
					if(!lockLine) {
						if(ity!=0&&ity!=objh-1&&itx!=0&&itx!=objw-1&&tit<siz) {
							if(text[tit] == '\n') {
								lockLine = true;
								++tit;
							} else {
								arg.get().put(x, y, text[tit]);
								++tit;
							}
						}
					}

					if(ity==0) {
						if(itx==0) {
							arg.get().put(x, y, fs.top_left);
						} else if(itx==objw-1) {
							arg.get().put(x, y, fs.top_right);
						} else {
							arg.get().put(x, y, fs.horizontal);
						}
					} else if(ity==objh-1) {
						if(itx==0) {
							arg.get().put(x, y, fs.bottom_left);
						} else if(itx==objw-1) {
							arg.get().put(x, y, fs.bottom_right);
						} else {
							arg.get().put(x, y, fs.horizontal);
						}
					} else {
						if(itx==0||itx==objw-1) {
							arg.get().put(x, y, fs.vertical);
						}
					}

				}
				lockLine = false;
				arg.get().moveCur(0, 1);
			}
		}

		inline bool isFocusable(context& arg) {
			return false;
		}
};



class imgframe : public scene_object {
	private:
		char defbg;
		ascimg *img;
		frame_style fs;

	public:
		imgframe(int ax, int ay, int aw, int ah, ascimg *aimg) {
			fs = default_frame_style;
			defbg = ' ';
			objx = ax;
			objy = ay;
			objw = aw;
			objh = ah;
			img = aimg;
		}

		imgframe(int ax, int ay, ascimg *aimg) {
			fs = default_frame_style;
			defbg = ' ';
			objx = ax;
			objy = ay;
			objw = aimg->w;
			objh = aimg->h+2;
			img = aimg;
		}

		inline void setFrameStyle(frame_style afs=null_frame_style) {
			fs = afs;
		}

		inline void setImage(ascimg *aimg) {
			objw = aimg->w;
			objh = aimg->h+2;
			img = aimg;
		}

		inline void setBackground(char ch) {
			defbg = ch;
		}

		inline void draw(context& arg) {
			int x, y, tit, titx, tity, siz = img->size();

			titx = 0;
			tity = 0;
			tit = 0;
			for(int ity=0;ity<objh;++ity) {

				for(int itx=0;itx<objw;++itx) {
					x = itx+objx+parentX;
					y = ity+objy+parentY;
					if(defbg!=0x00) {
						arg.get().put(x, y, defbg);
					}
					if(ity!=0&&ity!=objh-1&&itx!=0&&itx!=objw-1&&tit<siz) {
						arg.get().put(x, y, *img->get(itx-1, ity-1));
					}
					if(ity==0) {
						if(itx==0) {
							arg.get().put(x, y, fs.top_left);
						} else if(itx==objw-1) {
							arg.get().put(x, y, fs.top_right);
						} else {
							arg.get().put(x, y, fs.horizontal);
						}
					} else if(ity==objh-1) {
						if(itx==0) {
							arg.get().put(x, y, fs.bottom_left);
						} else if(itx==objw-1) {
							arg.get().put(x, y, fs.bottom_right);
						} else {
							arg.get().put(x, y, fs.horizontal);
						}
					} else {
						if(itx==0||itx==objw-1) {
							arg.get().put(x, y, fs.vertical);
						}
					}

				}
				tit+=img->w-objw-2;
				arg.get().moveCur(0, 1);
			}
		}

		inline bool isFocusable(context& arg) {
			return false;
		}
};



class button : public scene_object {
	private:
		char defbg;
		std::string text;
		frame_style fs;
		frame_style mfs;
		action act;

	public:
		button() {

		}

		button(int ax, int ay, int aw, int ah, std::string atext) {
			act = null_action;
			fs = default_frame_style;
			mfs = default_dbframe_style;
			defbg = ' ';
			text = atext;
			objx = ax;
			objy = ay;
			objw = aw;
			objh = ah;
		}

		button(int ax, int ay, std::string atext) {
			act = null_action;
			fs = default_frame_style;
			mfs = default_dbframe_style;
			defbg = ' ';
			text = atext;
			objx = ax;
			objy = ay;
			objw = atext.size()+4;
			objh = 3;
		}

		inline void setAction(action aact) {
			act = aact;
		}

		inline void setText(std::string atext) {
			text = atext;
		}

		inline void setFrameStyle(frame_style afs=null_frame_style) {
			fs = afs;
		}

		inline void setMarkedFrameStyle(frame_style afs=null_frame_style) {
			mfs = afs;
		}

		inline void setBackground(char ch) {
			defbg = ch;
		}

		inline ME_STATE onMouseEvent(context& arg, mouse_info& mouse_data) {
			if(mouse_data.x>=objx+parentX && mouse_data.x<=objx+parentX+objw) {
				if(mouse_data.y>=objy+parentY && mouse_data.y<=objy+parentY+objh) {
					return ME_FOCUSED;
				}
			}
			return ME_NOT_FOCUSED;
		}

		inline void draw(bool state, context& arg) {
			int x, y;
			for(int ity=0;ity<objh;++ity) {
				for(int itx=0;itx<objw;++itx) {
					x = itx+objx+parentX;
					y = ity+objy+parentY;
					arg.get().put(x, y, defbg);
					if(state) {
						if(ity==0) {
							if(itx==0) {
								arg.get().put(x, y, mfs.top_left);
							} else if(itx==objw-1) {
								arg.get().put(x, y, mfs.top_right);
							} else {
								arg.get().put(x, y, mfs.horizontal);
							}
						} else if(ity==objh-1) {
							if(itx==0) {
								arg.get().put(x, y, mfs.bottom_left);
							} else if(itx==objw-1) {
								arg.get().put(x, y, mfs.bottom_right);
							} else {
								arg.get().put(x, y, mfs.horizontal);
							}
						} else {
							if(itx==0||itx==objw-1) {
								arg.get().put(x, y, mfs.vertical);
							}
						}
					} else {
						if(ity==0) {
							if(itx==0) {
								arg.get().put(x, y, fs.top_left);
							} else if(itx==objw-1) {
								arg.get().put(x, y, fs.top_right);
							} else {
								arg.get().put(x, y, fs.horizontal);
							}
						} else if(ity==objh-1) {
							if(itx==0) {
								arg.get().put(x, y, fs.bottom_left);
							} else if(itx==objw-1) {
								arg.get().put(x, y, fs.bottom_right);
							} else {
								arg.get().put(x, y, fs.horizontal);
							}
						} else {
							if(itx==0||itx==objw-1) {
								arg.get().put(x, y, fs.vertical);
							}
						}
					}
				}

				arg.get().setCurPos(objx+parentX+(objw-2-text.size())/2+1, objy+parentY+((objh-objh%2)/2));
				arg.get() << text;
				arg.get().moveCur(0, 1);
			}
		}

		inline void whenClicked(context& arg) {
			act(arg, this);
		}
};



class selbox : public scene_object {
	private:
		char defbg;
		std::string text;
		frame_style fs;
		frame_style mfs;
		std::string * options_names;
		int options_num;
		int sel_option;
		action act;

	public:

		selbox(int ax, int ay, int aw, int ah, int argnum, std::string atext[]) {
			act = null_action;
			sel_option=0;
			options_num = argnum;
			options_names = new std::string[options_num+1];
			for(int it=0;it<options_num;++it) {
				options_names[it] = atext[it];
			}
			fs = default_frame_style;
			mfs = default_dbframe_style;
			defbg = ' ';
			text = atext[0];
			objx = ax;
			objy = ay;
			objw = aw;
			objh = ah;
		}

		selbox(int ax, int ay, int argnum, std::initializer_list<std::string> atext) {
			act = null_action;
			sel_option = 0;
			options_num = atext.size();
			options_names = new std::string[options_num+1];
			int it=0;
			std::string ftext = "";
			for(std::string str : atext) {
				options_names[it] = str;
				if(it==0) ftext = str;
				++it;
			}
			fs = default_frame_style;
			mfs = default_dbframe_style;
			defbg = ' ';
			text = ftext;
			objx = ax;
			objy = ay;
			objw = text.size()+4;
			objh = 3;
		}

		selbox(int ax, int ay, int argnum, std::string atext[]) {
			act = null_action;
			sel_option = 0;
			options_num = argnum;
			options_names = new std::string[options_num+1];
			for(int it=0;it<options_num;++it) {
				options_names[it] = atext[it];
			}
			fs = default_frame_style;
			mfs = default_dbframe_style;
			defbg = ' ';
			text = atext[0];
			objx = ax;
			objy = ay;
			objw = text.size()+4;
			objh = 3;
		}

		inline void moveOptions(context& arg, int delta) {
			if(delta>0) {
				for(int it=0;it<delta;++it) {
					nextOption();
					act(arg, this);
				}
			} else {
				for(int it=0;it<-delta;++it) {
					prevOption();
					act(arg, this);
				}
			}
		}

		inline void onMouseEventFocused(context& arg, mouse_info& mouse_data) {
			moveOptions(arg, mouse_data.wheel_pos_delta);
			mouse_data.wheel_pos_delta = 0;
		}

		inline ME_STATE onMouseEvent(context& arg, mouse_info& mouse_data) {
			if(mouse_data.x>=objx+parentX && mouse_data.x<=objx+parentX+objw) {
				if(mouse_data.y>=objy+parentY && mouse_data.y<=objy+parentY+objh) {
					return ME_FOCUSED;
				}
			}
			return ME_NULL;
		}

		inline std::string* getOptions() {
			return options_names;
		}

		inline int getSelectionNumber() {
			return sel_option;
		}

		inline std::string getSelectedOption() {
			return options_names[sel_option];
		}

		inline int optionsNumber() {
			return options_num;
		}

		inline void setAction(action aact) {
			act = aact;
		}

		inline void nextOption() {
			++sel_option;
			if(sel_option>=options_num) {
				sel_option=0;
			}
		}

		inline void prevOption() {
			--sel_option;
			if(sel_option<0) {
				sel_option=options_num-1;
			}
		}

		inline void setFrameStyle(frame_style afs=null_frame_style) {
			fs = afs;
		}

		inline void setMarkedFrameStyle(frame_style afs=null_frame_style) {
			mfs = afs;
		}

		inline void setBackground(char ch) {
			defbg = ch;
		}

		inline void draw(bool state, context& arg) {
			int x, y;
			for(int ity=0;ity<objh;++ity) {
				for(int itx=0;itx<objw;++itx) {
					x = itx+objx+parentX;
					y = ity+objy+parentY;
					arg.get().put(x, y, defbg);
					if(state) {
						if(ity==0) {
							if(itx==0) {
								arg.get().put(x, y, mfs.top_left);
							} else if(itx==objw-1) {
								arg.get().put(x, y, mfs.top_right);
							} else {
								arg.get().put(x, y, mfs.horizontal);
							}
						} else if(ity==objh-1) {
							if(itx==0) {
								arg.get().put(x, y, mfs.bottom_left);
							} else if(itx==objw-1) {
								arg.get().put(x, y, mfs.bottom_right);
							} else {
								arg.get().put(x, y, mfs.horizontal);
							}
						} else {
							if(itx==0||itx==objw-1) {
								arg.get().put(x, y, mfs.vertical);
							}
						}
					} else {
						if(ity==0) {
							if(itx==0) {
								arg.get().put(x, y, fs.top_left);
							} else if(itx==objw-1) {
								arg.get().put(x, y, fs.top_right);
							} else {
								arg.get().put(x, y, fs.horizontal);
							}
						} else if(ity==objh-1) {
							if(itx==0) {
								arg.get().put(x, y, fs.bottom_left);
							} else if(itx==objw-1) {
								arg.get().put(x, y, fs.bottom_right);
							} else {
								arg.get().put(x, y, fs.horizontal);
							}
						} else {
							if(itx==0||itx==objw-1) {
								arg.get().put(x, y, fs.vertical);
							}
						}
					}
				}
				/*
				string options_names;
				int options_num;
				int sel_option;
				*/
				text = options_names[sel_option];

				arg.get().setCurPos(objx+parentX+(objw-2-text.size())/2+1, objy+parentY+((objh-objh%2)/2));
				arg.get() << text;
				arg.get().moveCur(0, 1);

				if(state) {
					arg.get().setCurPos(objx+parentX+(objw-2-text.size())/2, objy+parentY+((objh-objh%2)/2)+1);
					arg.get() << "/|\\";
					arg.get().setCurPos(objx+parentX+(objw-2-text.size())/2, objy+parentY+((objh-objh%2)/2)-1);
					arg.get() << "\\|/";
				} else {
					arg.get().setCurPos(objx+parentX+(objw-2-text.size())/2+1, objy+parentY+((objh-objh%2)/2)+1);
					arg.get() << "|";
					arg.get().setCurPos(objx+parentX+(objw-2-text.size())/2+1, objy+parentY+((objh-objh%2)/2)-1);
					arg.get() << "|";
				}



			}
		}

		inline void onKeyEvent(context& arg, key& keycode) {

			if(keycode == WACCGL_KEY_SELECT_NEXT) {
				nextOption();
				act(arg, this);
			} else if(keycode == WACCGL_KEY_SELECT_PREV) {
				prevOption();
				act(arg, this);
			}

		}

		inline void whenClicked(context& arg) {

		}
};



class checkbox : public scene_object {
	private:
		char defbg;
		std::string text;
		frame_style fs;
		frame_style mfs;
		bool cstate;
		action act;

	public:
		checkbox(int ax, int ay, int aw, int ah, std::string atext) {
			cstate=false;
			fs = default_frame_style;
			mfs = default_dbframe_style;
			defbg = ' ';
			text = atext;
			objx = ax;
			objy = ay;
			objw = aw;
			objh = ah;
			act = null_action;
		}

		checkbox(int ax, int ay, std::string atext) {
			cstate=false;
			fs = default_frame_style;
			mfs = default_dbframe_style;
			defbg = ' ';
			text = atext;
			objx = ax;
			objy = ay;
			objw = atext.size()+4;
			objh = 3;
			act = null_action;
		}

		inline void onMouseEventFocused(context& arg, mouse_info& mouse_data) {
			if(mouse_data.wheel_pos_delta!=0) {
				whenClicked(arg);
			}
			mouse_data.wheel_pos_delta = 0;
		}

		inline ME_STATE onMouseEvent(context& arg, mouse_info& mouse_data) {
			if(mouse_data.x>=objx+parentX && mouse_data.x<=objx+parentX+objw) {
				if(mouse_data.y>=objy+parentY && mouse_data.y<=objy+parentY+objh) {
					return ME_FOCUSED;
				}
			}
			return ME_NULL;
		}

		inline void setState(bool state) {
			cstate = state;
		}

		inline void setFrameStyle(frame_style afs=null_frame_style) {
			fs = afs;
		}

		inline void setMarkedFrameStyle(frame_style afs=null_frame_style) {
			mfs = afs;
		}

		inline void setBackground(char ch) {
			defbg = ch;
		}

		inline void setAction(action aact) {
			act = aact;
		}

		inline void draw(bool state, context& arg) {
			int x, y;
			for(int ity=0;ity<objh;++ity) {
				for(int itx=0;itx<objw;++itx) {
					x = itx+objx+parentX;
					y = ity+objy+parentY;
					arg.get().put(x, y, defbg);
					if(state) {
						if(ity==0) {
							if(itx==0) {
								arg.get().put(x, y, mfs.top_left);
							} else if(itx==objw-1) {
								arg.get().put(x, y, mfs.top_right);
							} else {
								arg.get().put(x, y, mfs.horizontal);
							}
						} else if(ity==objh-1) {
							if(itx==0) {
								arg.get().put(x, y, mfs.bottom_left);
							} else if(itx==objw-1) {
								arg.get().put(x, y, mfs.bottom_right);
							} else {
								arg.get().put(x, y, mfs.horizontal);
							}
						} else {
							if(itx==0||itx==objw-1) {
								arg.get().put(x, y, mfs.vertical);
							}
						}
					} else {
						if(ity==0) {
							if(itx==0) {
								arg.get().put(x, y, fs.top_left);
							} else if(itx==objw-1) {
								arg.get().put(x, y, fs.top_right);
							} else {
								arg.get().put(x, y, fs.horizontal);
							}
						} else if(ity==objh-1) {
							if(itx==0) {
								arg.get().put(x, y, fs.bottom_left);
							} else if(itx==objw-1) {
								arg.get().put(x, y, fs.bottom_right);
							} else {
								arg.get().put(x, y, fs.horizontal);
							}
						} else {
							if(itx==0||itx==objw-1) {
								arg.get().put(x, y, fs.vertical);
							}
						}
					}
				}

				arg.get().setCurPos(2,2);
				std::string pom;
				for(int it=128;it<255;++it) {

					pom+=intToStr(it)+"="+"?";
					pom[pom.size()-1] = (char)it;
				}
				//arg.get() << pom;

				arg.get().setCurPos(objx+parentX+(objw-2-text.size())/2+1, objy+parentY+((objh-objh%2)/2));
				arg.get() << text;
				//arg.get().moveCur(0, 1);

				arg.get().setCurPos(objx+parentX, objy+((objh-objh%2)/2)+parentY);
				std::string p = " ";
				if(cstate) {
					p[0] = (char)220;
				} else {
					p[0] = (char)'O';
				}
				arg.get() << p;

				/*if(cstate) {
					arg.get() << (char)93;
				} else {
					arg.get() << (char)93;
				}*/
			}
		}

		void whenClicked(context& arg) {
			cstate = !cstate;
			act(arg, this);
		}

		inline bool isChecked() {
			return cstate;
		}

};






class slistbox : public scene_object {
	private:
		char defbg;
		std::string text;
		frame_style fs;
		frame_style mfs;
		std::string * options_names;
		int options_num;
		int sel_option;
		action act;
		bool sprop_roundedList;

	public:

		slistbox(int ax, int ay, int aw, int ah, int argnum, std::string atext[]) {
			setDefaultSideProperties();
			act = null_action;
			sel_option=0;
			options_num = argnum;
			options_names = new std::string[options_num+1];
			for(int it=0;it<options_num;++it) {
				options_names[it] = atext[it];
			}
			fs = default_frame_style;
			mfs = default_dbframe_style;
			defbg = ' ';
			text = atext[0];
			objx = ax;
			objy = ay;
			objw = aw;
			objh = ah;
		}

		slistbox(int ax, int ay, int argnum, std::string atext[]) {
			setDefaultSideProperties();
			act = null_action;
			sel_option = 0;
			options_num = argnum;
			options_names = new std::string[options_num+1];
			for(int it=0;it<options_num;++it) {
				options_names[it] = atext[it];
			}
			fs = default_frame_style;
			mfs = default_dbframe_style;
			defbg = ' ';
			text = atext[0];
			objx = ax;
			objy = ay;
			objw = text.size()+4;
			objh = 3;
		}

		slistbox(int ax, int ay, int argnum, std::initializer_list<std::string> atext) {
			setDefaultSideProperties();
			act = null_action;
			sel_option = 0;
			options_num = atext.size();
			options_names = new std::string[options_num+1];
			int it=0;
			std::string ftext = "";
			for(std::string str : atext) {
				options_names[it] = str;
				if(it==0) ftext = str;
				++it;
			}
			fs = default_frame_style;
			mfs = default_dbframe_style;
			defbg = ' ';
			text = ftext;
			objx = ax;
			objy = ay;
			objw = text.size()+4;
			objh = 3;
		}


		inline void moveOptions(context& arg, int delta) {
			if(delta>0) {
				for(int it=0;it<delta;++it) {
					nextOption();
					act(arg, this);
				}
			} else {
				for(int it=0;it<-delta;++it) {
					prevOption();
					act(arg, this);
				}
			}
		}

		inline void onMouseEventFocused(context& arg, mouse_info& mouse_data) {
			moveOptions(arg, mouse_data.wheel_pos_delta);
			mouse_data.wheel_pos_delta = 0;
		}

		inline ME_STATE onMouseEvent(context& arg, mouse_info& mouse_data) {
			if(mouse_data.x>=objx+parentX && mouse_data.x<=objx+parentX+objw) {
				if(mouse_data.y>=objy+parentY && mouse_data.y<=objy+parentY+objh) {
					return ME_FOCUSED;
				}
			}
			return ME_NULL;
		}

		inline void setDefaultSideProperties() {
			sprop_roundedList = false;
		}

		inline void setRoundedList(bool state) {
			sprop_roundedList = state;
		}

		inline std::string* getOptions() {
			return options_names;
		}

		inline int getSelectionNumber() {
			return sel_option;
		}

		inline std::string getSelectedOption() {
			return options_names[sel_option];
		}

		inline int optionsNumber() {
			return options_num;
		}

		inline void setAction(action aact) {
			act = aact;
		}

		inline void nextOption() {
			++sel_option;
			if(sel_option>=options_num) {
				if(sprop_roundedList) {
					sel_option= 0;
				} else {
					sel_option= options_num-1;
				}
			}
		}

		inline void prevOption() {
			--sel_option;
			if(sel_option<0) {
				if(sprop_roundedList) {
					sel_option = options_num-1;
				} else {
					sel_option = 0;
				}
			}
		}

		inline void setFrameStyle(frame_style afs=null_frame_style) {
			fs = afs;
		}

		inline void setMarkedFrameStyle(frame_style afs=null_frame_style) {
			mfs = afs;
		}

		inline void setBackground(char ch) {
			defbg = ch;
		}

		inline void draw(bool state, context& arg) {
			int x, y;
			for(int ity=0;ity<objh;++ity) {
				for(int itx=0;itx<objw;++itx) {
					x = itx+objx+parentX;
					y = ity+objy+parentY;
					arg.get().put(x, y, defbg);
					if(state) {
						if(ity==0) {
							if(itx==0) {
								arg.get().put(x, y, mfs.top_left);
							} else if(itx==objw-1) {
								arg.get().put(x, y, mfs.top_right);
							} else {
								arg.get().put(x, y, mfs.horizontal);
							}
						} else if(ity==objh-1) {
							if(itx==0) {
								arg.get().put(x, y, mfs.bottom_left);
							} else if(itx==objw-1) {
								arg.get().put(x, y, mfs.bottom_right);
							} else {
								arg.get().put(x, y, mfs.horizontal);
							}
						} else {
							if(itx==0||itx==objw-1) {
								arg.get().put(x, y, mfs.vertical);
							}
						}
					} else {
						if(ity==0) {
							if(itx==0) {
								arg.get().put(x, y, fs.top_left);
							} else if(itx==objw-1) {
								arg.get().put(x, y, fs.top_right);
							} else {
								arg.get().put(x, y, fs.horizontal);
							}
						} else if(ity==objh-1) {
							if(itx==0) {
								arg.get().put(x, y, fs.bottom_left);
							} else if(itx==objw-1) {
								arg.get().put(x, y, fs.bottom_right);
							} else {
								arg.get().put(x, y, fs.horizontal);
							}
						} else {
							if(itx==0||itx==objw-1) {
								arg.get().put(x, y, fs.vertical);
							}
						}
					}
				}

				text = options_names[sel_option];
				int textidbeg = sel_option-((objh-2)/2);

				if(textidbeg>options_num-1) {
					textidbeg=options_num-1;
				}
				if(textidbeg<0) {
					textidbeg=0;
				}

				for(int ity=1;ity<objh-1;++ity) {
					if(ity-1+textidbeg>=0 && ity-1+textidbeg<options_num) {
						arg.get().setCurPos(objx+(objw-5-text.size())/2+1+parentX, objy+ity+parentY);
						if(sel_option == ity-1+textidbeg) {
							if(state) {
								arg.get() << "-> ";
								arg.get() << options_names[ity-1+textidbeg];
								arg.get() << " <-";
							} else {
								arg.get() << " [ ";
								arg.get() << options_names[ity-1+textidbeg];
								arg.get() << " ] ";
							}
						} else {
							arg.get() << "   ";
							arg.get() << options_names[ity-1+textidbeg];
							arg.get() << "   ";
						}
					}
				}

				/*arg.get().setCurPos(objx+(objw-2-text.size())/2+1, objy+((objh-objh%2)/2));
				arg.get() << text;
				arg.get().moveCur(0, 1);*/

				/*if(state) {
					arg.get().setCurPos(objx+(objw-2-text.size())/2, objy+((objh-objh%2)/2)+1);
					arg.get() << "/|\\";
					arg.get().setCurPos(objx+(objw-2-text.size())/2, objy+((objh-objh%2)/2)-1);
					arg.get() << "\\|/";
				} else {
					arg.get().setCurPos(objx+(objw-2-text.size())/2+1, objy+((objh-objh%2)/2)+1);
					arg.get() << "|";
					arg.get().setCurPos(objx+(objw-2-text.size())/2+1, objy+((objh-objh%2)/2)-1);
					arg.get() << "|";
				}*/



			}
		}

		inline void onKeyEvent(context& arg, key& keycode) {
			if(keycode == WACCGL_KEY_SELECT_NEXT) {
				nextOption();
				act(arg, this);
			} else if(keycode == WACCGL_KEY_SELECT_PREV) {
				prevOption();
				act(arg, this);
			}
		}

		inline void whenClicked(context& arg) {

		}
};






class listbox : public scene_object {
	private:
		char defbg;
		std::string text;
		frame_style fs;
		frame_style mfs;
		std::vector<std::string> options_names;
		int options_num;
		int sel_option;
		action act;
		bool sprop_roundedList;

	public:

		listbox(int ax, int ay, int aw, int ah, std::vector<std::string> atext) {
			setDefaultSideProperties();
			act = null_action;
			sel_option=0;
			options_num = atext.size();
			options_names = atext;
			fs = default_frame_style;
			mfs = default_dbframe_style;
			defbg = ' ';
			text = atext[0];
			objx = ax;
			objy = ay;
			objw = aw;
			objh = ah;
		}

		listbox(int ax, int ay, int aw, int ah) {
			setDefaultSideProperties();
			act = null_action;
			sel_option=0;
			options_num = 0;
			fs = default_frame_style;
			mfs = default_dbframe_style;
			defbg = ' ';
			text = "";
			objx = ax;
			objy = ay;
			objw = aw;
			objh = ah;
		}

		listbox(int ax, int ay, int aw, int ah, int len, std::string atext[]) {
			setDefaultSideProperties();
			act = null_action;
			sel_option=0;
			setOptions(len, atext);
			fs = default_frame_style;
			mfs = default_dbframe_style;
			defbg = ' ';
			text = atext[0];
			objx = ax;
			objy = ay;
			objw = aw;
			objh = ah;
		}

		listbox(int ax, int ay, int len, std::string atext[]) {
			setDefaultSideProperties();
			act = null_action;
			sel_option = 0;
			setOptions(len, atext);
			fs = default_frame_style;
			mfs = default_dbframe_style;
			defbg = ' ';
			text = atext[0];
			objx = ax;
			objy = ay;
			objw = text.size()+4;
			objh = 3;
		}

		listbox(int ax, int ay, int argnum, std::initializer_list<std::string> atext) {
			setDefaultSideProperties();
			act = null_action;
			sel_option = 0;
			options_num = atext.size();
			int it = 0;
			std::string ftext = "";
			for(std::string str : atext) {
				options_names.push_back(str);
				if(it==0) ftext = str;
				++it;
			}
			fs = default_frame_style;
			mfs = default_dbframe_style;
			defbg = ' ';
			text = ftext;
			objx = ax;
			objy = ay;
			objw = text.size()+4;
			objh = 3;
		}


		listbox(int ax, int ay, std::vector<std::string> atext) {
			setDefaultSideProperties();
			act = null_action;
			sel_option = 0;
			options_num = atext.size();
			options_names = atext;
			fs = default_frame_style;
			mfs = default_dbframe_style;
			defbg = ' ';
			text = atext[0];
			objx = ax;
			objy = ay;
			objw = text.size()+4;
			objh = 3;
		}

		listbox(int ax, int ay) {
			setDefaultSideProperties();
			act = null_action;
			sel_option = 0;
			options_num = 0;
			fs = default_frame_style;
			mfs = default_dbframe_style;
			defbg = ' ';
			text = "";
			objx = ax;
			objy = ay;
			objw = text.size()+4;
			objh = 3;
		}


		inline void moveOptions(context& arg, int delta) {
			if(delta>0) {
				for(int it=0;it<delta;++it) {
					nextOption();
					act(arg, this);
				}
			} else {
				for(int it=0;it<-delta;++it) {
					prevOption();
					act(arg, this);
				}
			}
		}

		inline void onMouseEventFocused(context& arg, mouse_info& mouse_data) {
			moveOptions(arg, mouse_data.wheel_pos_delta);
			mouse_data.wheel_pos_delta = 0;
		}

		inline ME_STATE onMouseEvent(context& arg, mouse_info& mouse_data) {
			if(mouse_data.x>=objx+parentX && mouse_data.x<=objx+parentX+objw) {
				if(mouse_data.y>=objy+parentY && mouse_data.y<=objy+parentY+objh) {
					return ME_FOCUSED;
				}
			}
			return ME_NULL;
		}


		inline void emptyOptions() {
			options_num = 0;
			options_names.clear();
		}

		inline void addOptions(int len, std::string atext[]) {
			for(int it=0;it<len;++it) {
				options_names.push_back(atext[it]);
			}
			options_num += len;
		}

		inline void setOptions(int len, std::string atext[]) {
			emptyOptions();
			addOptions(len, atext);
		}

		inline void overrideOption(int pos, std::string atext) {
			options_names[pos] = atext;
		}

		inline void addOption(std::string atext) {
			++options_num;
			options_names.push_back(atext);
		}

		inline void removeOption(std::string atext) {
			for(int it=0;it<options_num;++it) {
				if(options_names[it] == atext) {
					options_names.erase(options_names.begin()+it, options_names.begin()+it+1);
					--options_num;
					return;
				}
			}
		}

		inline void addOptions(std::vector<std::string> atext) {
			const int len = atext.size();
			for(int it=0;it<len;++it) {
				options_names.push_back(atext[it]);
			}
			options_num += atext.size();
		}

		inline void removeOption(int index) {
			options_names.erase(options_names.begin()+index, options_names.begin()+index+1);
			--options_num;
		}

		inline void setOptions(std::vector<std::string> atext) {
			options_names = atext;
			options_num = atext.size();
		}

		inline void setDefaultSideProperties() {
			sprop_roundedList = false;
		}

		inline void setRoundedList(bool state) {
			sprop_roundedList = state;
		}

		inline std::vector<std::string> getOptions() {
			return options_names;
		}

		inline bool isAnyOptionContains(std::string val) {
			for(int it=0;it<options_num;++it) {
				if(options_names[it].find(val)!=std::string::npos) {
					return true;
				}
			}
			return false;
		}

		inline int getSelectionNumber() {
			return sel_option;
		}

		inline std::string getSelectedOption() {
			return options_names[sel_option];
		}

		inline int optionsNumber() {
			return options_num;
		}

		inline void setAction(action aact) {
			act = aact;
		}

		inline void nextOption() {
			++sel_option;
			if(sel_option>=options_num) {
				if(sprop_roundedList) {
					sel_option= 0;
				} else {
					sel_option= options_num-1;
				}
			}
		}

		inline void prevOption() {
			--sel_option;
			if(sel_option<0) {
				if(sprop_roundedList) {
					sel_option = options_num-1;
				} else {
					sel_option = 0;
				}
			}
		}

		inline void setFrameStyle(frame_style afs=null_frame_style) {
			fs = afs;
		}

		inline void setMarkedFrameStyle(frame_style afs=null_frame_style) {
			mfs = afs;
		}

		inline void setBackground(char ch) {
			defbg = ch;
		}

		inline void draw(bool state, context& arg) {
			int x, y;
			for(int ity=0;ity<objh;++ity) {
				for(int itx=0;itx<objw;++itx) {
					x = itx+objx+parentX;
					y = ity+objy+parentY;
					arg.get().put(x, y, defbg);
					if(state) {
						if(ity==0) {
							if(itx==0) {
								arg.get().put(x, y, mfs.top_left);
							} else if(itx==objw-1) {
								arg.get().put(x, y, mfs.top_right);
							} else {
								arg.get().put(x, y, mfs.horizontal);
							}
						} else if(ity==objh-1) {
							if(itx==0) {
								arg.get().put(x, y, mfs.bottom_left);
							} else if(itx==objw-1) {
								arg.get().put(x, y, mfs.bottom_right);
							} else {
								arg.get().put(x, y, mfs.horizontal);
							}
						} else {
							if(itx==0||itx==objw-1) {
								arg.get().put(x, y, mfs.vertical);
							}
						}
					} else {
						if(ity==0) {
							if(itx==0) {
								arg.get().put(x, y, fs.top_left);
							} else if(itx==objw-1) {
								arg.get().put(x, y, fs.top_right);
							} else {
								arg.get().put(x, y, fs.horizontal);
							}
						} else if(ity==objh-1) {
							if(itx==0) {
								arg.get().put(x, y, fs.bottom_left);
							} else if(itx==objw-1) {
								arg.get().put(x, y, fs.bottom_right);
							} else {
								arg.get().put(x, y, fs.horizontal);
							}
						} else {
							if(itx==0||itx==objw-1) {
								arg.get().put(x, y, fs.vertical);
							}
						}
					}
				}

				if(options_num<=0) {
					text = "";
				} else {
					text = options_names[sel_option];
					int textidbeg = sel_option-((objh-2)/2);

					if(textidbeg>options_num-1) {
						textidbeg=options_num-1;
					}
					if(textidbeg<0) {
						textidbeg=0;
					}

					for(int ity=1;ity<objh-1;++ity) {
						if(ity-1+textidbeg>=0 && ity-1+textidbeg<options_num) {
							arg.get().setCurPos(objx+(objw-5-text.size())/2+1+parentX, objy+ity+parentY);
							if(sel_option == ity-1+textidbeg) {
								if(state) {
									arg.get() << "-> ";
									arg.get() << options_names[ity-1+textidbeg];
									arg.get() << " <-";
								} else {
									arg.get() << " [ ";
									arg.get() << options_names[ity-1+textidbeg];
									arg.get() << " ] ";
								}
							} else {
								arg.get() << "   ";
								arg.get() << options_names[ity-1+textidbeg];
								arg.get() << "   ";
							}
						}
					}

				}
				/*arg.get().setCurPos(objx+(objw-2-text.size())/2+1, objy+((objh-objh%2)/2));
				arg.get() << text;
				arg.get().moveCur(0, 1);*/

				/*if(state) {
					arg.get().setCurPos(objx+(objw-2-text.size())/2, objy+((objh-objh%2)/2)+1);
					arg.get() << "/|\\";
					arg.get().setCurPos(objx+(objw-2-text.size())/2, objy+((objh-objh%2)/2)-1);
					arg.get() << "\\|/";
				} else {
					arg.get().setCurPos(objx+(objw-2-text.size())/2+1, objy+((objh-objh%2)/2)+1);
					arg.get() << "|";
					arg.get().setCurPos(objx+(objw-2-text.size())/2+1, objy+((objh-objh%2)/2)-1);
					arg.get() << "|";
				}*/



			}
		}

		inline void onKeyEvent(context& arg, key& keycode) {
			if(keycode == WACCGL_KEY_SELECT_NEXT) {
				nextOption();
				act(arg, this);
			} else if(keycode == WACCGL_KEY_SELECT_PREV) {
				prevOption();
				act(arg, this);
			}
		}

		inline void whenClicked(context& arg) {

		}
};



class exlistbox : public scene_object {
	private:
		char defbg;
		std::string text;
		frame_style fs;
		frame_style mfs;
		std::vector<std::string> options_names;
		int options_num;
		int sel_option;
		action act;
		bool sprop_roundedList;
		std::string main_text;
		int main_text_sel;

	public:

		exlistbox(int ax, int ay, int aw, int ah, std::vector<std::string> atext) {
			setDefaultSideProperties();
			act = null_action;
			sel_option=0;
			options_num = atext.size();
			options_names = atext;
			fs = default_frame_style;
			mfs = default_dbframe_style;
			defbg = ' ';
			text = atext[0];
			objx = ax;
			objy = ay;
			objw = aw;
			objh = ah;
			main_text = "...";
			main_text_sel = -1;
		}

		exlistbox(int ax, int ay, int aw, int ah) {
			setDefaultSideProperties();
			act = null_action;
			sel_option=0;
			options_num = 0;
			fs = default_frame_style;
			mfs = default_dbframe_style;
			defbg = ' ';
			text = "";
			objx = ax;
			objy = ay;
			objw = aw;
			objh = ah;
			main_text = "...";
			main_text_sel = -1;
		}

		exlistbox(int ax, int ay, int aw, int ah, int len, std::string atext[]) {
			setDefaultSideProperties();
			act = null_action;
			sel_option=0;
			setOptions(len, atext);
			fs = default_frame_style;
			mfs = default_dbframe_style;
			defbg = ' ';
			text = atext[0];
			objx = ax;
			objy = ay;
			objw = aw;
			objh = ah;
			main_text = "...";
			main_text_sel = -1;
		}

		exlistbox(int ax, int ay, int argnum, std::initializer_list<std::string> atext) {
			setDefaultSideProperties();
			act = null_action;
			sel_option = 0;
			setOptions(atext);
			fs = default_frame_style;
			mfs = default_dbframe_style;
			defbg = ' ';
			text = options_names[0];
			objx = ax;
			objy = ay;
			objw = text.size()+4;
			objh = 3;
			main_text = "...";
			main_text_sel = -1;
		}

		exlistbox(int ax, int ay, int len, std::string atext[]) {
			setDefaultSideProperties();
			act = null_action;
			sel_option = 0;
			setOptions(len, atext);
			fs = default_frame_style;
			mfs = default_dbframe_style;
			defbg = ' ';
			text = atext[0];
			objx = ax;
			objy = ay;
			objw = text.size()+4;
			objh = 3;
			main_text = "...";
			main_text_sel = -1;
		}

		exlistbox(int ax, int ay, std::vector<std::string> atext) {
			setDefaultSideProperties();
			act = null_action;
			sel_option = 0;
			options_num = atext.size();
			options_names = atext;
			fs = default_frame_style;
			mfs = default_dbframe_style;
			defbg = ' ';
			text = atext[0];
			objx = ax;
			objy = ay;
			objw = text.size()+4;
			objh = 3;
			main_text = "...";
			main_text_sel = -1;
		}

		exlistbox(int ax, int ay) {
			setDefaultSideProperties();
			act = null_action;
			sel_option = 0;
			options_num = 0;
			fs = default_frame_style;
			mfs = default_dbframe_style;
			defbg = ' ';
			text = "";
			objx = ax;
			objy = ay;
			objw = text.size()+4;
			objh = 3;
			main_text = "...";
			main_text_sel = -1;
		}

		inline void moveOptions(context& arg, int delta) {
			if(delta>0) {
				for(int it=0;it<delta;++it) {
					nextOption();
					act(arg, this);
				}
			} else {
				for(int it=0;it<-delta;++it) {
					prevOption();
					act(arg, this);
				}
			}
		}

		inline void onMouseEventFocused(context& arg, mouse_info& mouse_data) {
			moveOptions(arg, mouse_data.wheel_pos_delta);
			mouse_data.wheel_pos_delta = 0;
		}

		inline ME_STATE onMouseEvent(context& arg, mouse_info& mouse_data) {
			if(mouse_data.x>=objx+parentX && mouse_data.x<=objx+parentX+objw) {
				if(mouse_data.y>=objy+parentY && mouse_data.y<=objy+parentY+objh) {
					return ME_FOCUSED;
				}
			}
			return ME_NULL;
		}

		inline void emptyOptions() {
			options_num = 0;
			options_names.clear();
		}

		inline void addOptions(int len, std::string atext[]) {
			for(int it=0;it<len;++it) {
				options_names.push_back(atext[it]);
			}
			options_num += len;
		}

		inline void setOptions(int len, std::initializer_list<std::string> atext) {
			emptyOptions();
			addOptions(atext);
		}

		inline void setOptions(int len, std::string atext[]) {
			emptyOptions();
			addOptions(len, atext);
		}

		inline void overrideOption(int pos, std::string atext) {
			options_names[pos] = atext;
		}

		inline void addOption(std::string atext) {
			++options_num;
			options_names.push_back(atext);
		}

		inline void removeOption(std::string atext) {
			for(int it=0;it<options_num;++it) {
				if(options_names[it] == atext) {
					options_names.erase(options_names.begin()+it, options_names.begin()+it+1);
					--options_num;
					return;
				}
			}
		}

		inline void addOptions(std::initializer_list<std::string> atext) {
				int it = 0;
				for(std::string str : atext) {
					options_names.push_back(str);
					++it;
				}
				options_num += it;
		}

		inline void addOptions(std::vector<std::string> atext) {
			const int len = atext.size();
			for(int it=0;it<len;++it) {
				options_names.push_back(atext[it]);
			}
			options_num += atext.size();
		}

		inline void removeOption(int index) {
			options_names.erase(options_names.begin()+index, options_names.begin()+index+1);
			--options_num;
		}

		inline void setOptions(std::vector<std::string> atext) {
			options_names = atext;
			options_num = atext.size();
		}

		inline void setDefaultSideProperties() {
			sprop_roundedList = false;
		}

		inline void setRoundedList(bool state) {
			sprop_roundedList = state;
		}

		inline std::vector<std::string> getOptions() {
			return options_names;
		}

		inline bool isAnyOptionContains(std::string val) {
			for(int it=0;it<options_num;++it) {
				if(options_names[it].find(val)!=std::string::npos) {
					return true;
				}
			}
			return false;
		}

		inline void setDefaultOption(int index) {
			main_text = options_names[index];
			main_text_sel = index;
		}

		inline int getTempSelectionNumber() {
			return sel_option;
		}

		inline std::string getTempSelectedOption() {
			return options_names[sel_option];
		}

		inline int getSelectionNumber() {
			return main_text_sel;
		}

		inline std::string getSelectedOption() {
			if(main_text_sel<0) {
				return "";
			}
			return main_text;
		}

		inline int optionsNumber() {
			return options_num;
		}

		inline void setAction(action aact) {
			act = aact;
		}

		inline void nextOption() {
			++sel_option;
			if(sel_option>=options_num) {
				if(sprop_roundedList) {
					sel_option= 0;
				} else {
					sel_option= options_num-1;
				}
			}
		}

		inline void prevOption() {
			--sel_option;
			if(sel_option<0) {
				if(sprop_roundedList) {
					sel_option = options_num-1;
				} else {
					sel_option = 0;
				}
			}
		}

		inline void setFrameStyle(frame_style afs=null_frame_style) {
			fs = afs;
		}

		inline void setMarkedFrameStyle(frame_style afs=null_frame_style) {
			mfs = afs;
		}

		inline void setBackground(char ch) {
			defbg = ch;
		}

		inline void draw(bool state, context& arg) {
			int x, y;
			int tobjh = objh+2;
			for(int ity=0;ity<tobjh;++ity) {
				for(int itx=0;itx<objw;++itx) {
					x = itx+objx+parentX;
					y = ity+objy+parentY;
					arg.get().put(x, y, defbg);
					if(state) {
						if(ity==0) {
							if(itx==0) {
								arg.get().put(x, y, mfs.top_left);
							} else if(itx==objw-1) {
								arg.get().put(x, y, mfs.top_right);
							} else {
								arg.get().put(x, y, mfs.horizontal);
							}
						} else if(ity==tobjh-1) {
							if(itx==0) {
								arg.get().put(x, y, mfs.bottom_left);
							} else if(itx==objw-1) {
								arg.get().put(x, y, mfs.bottom_right);
							} else {
								arg.get().put(x, y, mfs.horizontal);
							}
						} else {
							if(itx==0||itx==objw-1) {
								arg.get().put(x, y, mfs.vertical);
							}
						}
					} else {
						if(ity==0) {
							if(itx==0) {
								arg.get().put(x, y, fs.top_left);
							} else if(itx==objw-1) {
								arg.get().put(x, y, fs.top_right);
							} else {
								arg.get().put(x, y, fs.horizontal);
							}
						} else if(ity==tobjh-1) {
							if(itx==0) {
								arg.get().put(x, y, fs.bottom_left);
							} else if(itx==objw-1) {
								arg.get().put(x, y, fs.bottom_right);
							} else {
								arg.get().put(x, y, fs.horizontal);
							}
						} else {
							if(itx==0||itx==objw-1) {
								arg.get().put(x, y, fs.vertical);
							}
						}
					}
				}

				arg.get().setCurPos(objx+(objw-5-text.size())/2+1+parentX, objy+1+parentY);
				arg.get() << "* "+main_text+" *";

				if(!state) {
					tobjh = 3;
					arg.get().setCurPos(objx+objw-5+parentX, objy+1+parentY);
					arg.get() << "\\/";
				} else {
					if(options_num<=0) {
						text = "";
					} else {
						text = options_names[sel_option];
						int textidbeg = sel_option-((tobjh-2)/2);

						if(textidbeg>options_num-1) {
							textidbeg=options_num-1;
						}
						if(textidbeg<0) {
							textidbeg=0;
						}

						for(int ity=1;ity<tobjh-2;++ity) {
							if(ity-1+textidbeg>=0 && ity-1+textidbeg<options_num) {
								arg.get().setCurPos(objx+(objw-5-text.size())/2+1+parentX, objy+ity+parentY+1);
								if(sel_option == ity-1+textidbeg) {
									if(state) {
										arg.get() << "-> ";
										arg.get() << options_names[ity-1+textidbeg];
										arg.get() << " <-";
									} else {
										arg.get() << " [ ";
										arg.get() << options_names[ity-1+textidbeg];
										arg.get() << " ] ";
									}
								} else {
									arg.get() << "   ";
									arg.get() << options_names[ity-1+textidbeg];
									arg.get() << "   ";
								}
							}
						}

					}
				}
				/*arg.get().setCurPos(objx+(objw-2-text.size())/2+1, objy+((tobjh-tobjh%2)/2));
				arg.get() << text;
				arg.get().moveCur(0, 1);*/

				/*if(state) {
					arg.get().setCurPos(objx+(objw-2-text.size())/2, objy+((tobjh-tobjh%2)/2)+1);
					arg.get() << "/|\\";
					arg.get().setCurPos(objx+(objw-2-text.size())/2, objy+((tobjh-tobjh%2)/2)-1);
					arg.get() << "\\|/";
				} else {
					arg.get().setCurPos(objx+(objw-2-text.size())/2+1, objy+((tobjh-tobjh%2)/2)+1);
					arg.get() << "|";
					arg.get().setCurPos(objx+(objw-2-text.size())/2+1, objy+((tobjh-tobjh%2)/2)-1);
					arg.get() << "|";
				}*/



			}
		}

		inline void onKeyEvent(context& arg, key& keycode) {
			if(keycode == WACCGL_KEY_SELECT_NEXT) {
				nextOption();
				act(arg, this);
			} else if(keycode == WACCGL_KEY_SELECT_PREV) {
				prevOption();
				act(arg, this);
			}
		}

		inline void whenClicked(context& arg) {
			main_text = getTempSelectedOption();
			main_text_sel = getTempSelectionNumber();
			act(arg, this);
		}
};


class vscrollbar : public scene_object {
	private:
		char defbg = 0x00;
		frame_style fs;
		frame_style mfs;
		int max = 0;
		int scroll = 0;
		char markerMain = '#';
		char markerScrolled = '.';
		char markerNotScrolled = '.';
		char markerMainFocused = '#';
		char markerScrolledFocused = '.';
		char markerNotScrolledFocused = '.';
		action actionOnScroll = null_action;

	public:

		vscrollbar(int ax, int ay, int ah, int vscroll=-1, int maxscroll=-1) {
			if(maxscroll<0) {
				maxscroll = ah;
			}
			if(vscroll<0) {
				vscroll = maxscroll - vscroll%maxscroll;
			}
			fs = null_frame_style;
			mfs = null_frame_style;
			objx = ax;
			objy = ay;
			objw = 3;
			objh = ah;
			max = maxscroll;
			scroll = vscroll;
			setMarker();
			setMarkerScrolled();
			setMarkerNotScrolled();
			setFocusedMarker();
			setFocusedMarkerScrolled();
			setFocusedMarkerNotScrolled();

			normalizeScroll();
		}

		inline void setOnScrollAction(action act) {
			actionOnScroll = act;
		}

		/*vscrollbar(int ax, int ay, int aw, int ah) {
			fs = default_frame_style;
			mfs = default_dbframe_style;
			objx = ax;
			objy = ay;
			objw = aw;
			objh = ah;
			max = 100;
			scroll = 50;
			setMarkerScrolled();
			setMarkerNotScrolled();
		}*/

		inline void onMouseEventFocused(context& arg, mouse_info& mouse_data) {
			pushScroll(mouse_data.wheel_pos_delta);
			mouse_data.wheel_pos_delta = 0;
		}

		inline ME_STATE onMouseEvent(context& arg, mouse_info& mouse_data) {
			if(mouse_data.x>=objx+parentX && mouse_data.x<=objx+parentX+objw) {
				if(mouse_data.y>=objy+parentY && mouse_data.y<=objy+parentY+objh) {
					return ME_FOCUSED;
				}
			}
			return ME_NULL;
		}

		inline void setFrameStyle(frame_style afs=null_frame_style) {
			fs = afs;
		}

		inline void setMarkedFrameStyle(frame_style afs=null_frame_style) {
			mfs = afs;
		}

		inline void setBackground(char ch) {
			defbg = ch;
		}

		inline void setMarker(char marker='*') {
			markerMain = marker;
		}

		inline void setMarkerScrolled(char marker='|') {
			markerScrolled = marker;
		}

		inline void setMarkerNotScrolled(char marker='|') {
			markerNotScrolled = marker;
		}

		inline void setFocusedMarker(char marker=178) {
			markerMainFocused = marker;
		}

		inline void setFocusedMarkerScrolled(char marker=176) {
			markerScrolledFocused = marker;
		}

		inline void setFocusedMarkerNotScrolled(char marker=176) {
			markerNotScrolledFocused = marker;
		}

		inline void setMaxScroll(int amax) {
			max = amax;
			normalizeScroll();
		}

		inline int getMaxScroll() {
			return max;
		}

		inline void setMax(int amax) {
			max = amax;
			normalizeScroll();
		}

		inline int getMax() {
			return max;
		}

		inline void setScroll(int ascroll) {
			scroll = ascroll;
			normalizeScroll();
		}

		inline int getScroll() {
			return scroll;
		}

		inline void setValue(int ascroll) {
			scroll = ascroll;
			normalizeScroll();
		}

		inline int getValue() {
			return scroll;
		}

		inline void normalizeScroll() {
			if(max<1) {
				scroll = 1;
				max = 1;
			}
			if(scroll<1) scroll=1;
			scroll = std::min(scroll, max-2);
		}

		inline void pushScroll(int val=1) {
			if(scroll<max && val>=0) {
				scroll += val;
			} else if(scroll>0 && val<0) {
				scroll += val;
			}
			normalizeScroll();
		}

		inline void onKeyEvent(context& arg, key& keycode) {
			if(keycode == WACCGL_KEY_SCROLL_DOWN) {
				pushScroll(1);
				actionOnScroll(arg, this);
			} else if(keycode == WACCGL_KEY_SCROLL_UP) {
				pushScroll(-1);
				actionOnScroll(arg, this);
			}
		}

		inline void draw(bool state, context& arg) {

			double percone = ((double)(max)) / ((double)(objh-2));

			int x = 0;
			int y = 0;

			for(int ity=0;ity<objh;++ity) {
				for(int itx=0;itx<objw;++itx) {
					x = itx+objx+parentX;
					y = ity+objy+parentY;
					arg.get().put(x, y, defbg);

					if(state) {
						if(ity==0) {
							if(itx==0) {
								arg.get().put(x, y, mfs.top_left);
							} else if(itx==objw-1) {
								arg.get().put(x, y, mfs.top_right);
							} else {
								arg.get().put(x, y, mfs.horizontal);
							}
						} else if(ity==objh-1) {
							if(itx==0) {
								arg.get().put(x, y, mfs.bottom_left);
							} else if(itx==objw-1) {
								arg.get().put(x, y, mfs.bottom_right);
							} else {
								arg.get().put(x, y, mfs.horizontal);
							}
						} else {
							if(itx==0||itx==objw-1) {
								arg.get().put(x, y, mfs.vertical);
							} else {
								if( ((double)ity)*percone <= scroll ) {
									arg.get().put(x, y, markerScrolledFocused);

								} else if( abs( ((double)ity)*percone - scroll) <= percone ) {
									arg.get().put(x, y, markerMainFocused);
								} else {
									arg.get().put(x, y, markerNotScrolledFocused);
								}
							}
						}
					} else {
						if(ity==0) {
							if(itx==0) {
								arg.get().put(x, y, fs.top_left);
							} else if(itx==objw-1) {
								arg.get().put(x, y, fs.top_right);
							} else {
								arg.get().put(x, y, fs.horizontal);
							}
						} else if(ity==objh-1) {
							if(itx==0) {
								arg.get().put(x, y, fs.bottom_left);
							} else if(itx==objw-1) {
								arg.get().put(x, y, fs.bottom_right);
							} else {
								arg.get().put(x, y, fs.horizontal);
							}
						} else {
							if(itx==0||itx==objw-1) {
								arg.get().put(x, y, fs.vertical);
							} else {
								if( ((double)ity)*percone <= scroll ) {
									arg.get().put(x, y, markerScrolled);

								} else if( abs( ((double)ity)*percone - scroll) <= percone ) {
									arg.get().put(x, y, markerMain);
								} else {
									arg.get().put(x, y, markerNotScrolled);
								}
							}
						}
					}
				}
			}
		}

		inline bool isFocusable(context& arg) {
			return true;
		}

};




class progressbar : public scene_object {
	private:
		char defbg = ' ';
		char progressbg = '#';
		char progressnbg = 0x00;
		frame_style fs;
		int value = 0;
		int max = 100;
		bool stateActionExecuted = false;
		action act = null_action;

	public:

		progressbar(int ax, int ay, int aw, int ah=1, int avalue=0, int amax=100) {
			fs = null_frame_style;
			objx = ax;
			objy = ay;
			objw = aw;
			objh = ah;
			value = avalue;
			max = amax;
			defbg = ' ';
			setDoneProgressMarker();
			setNotDoneProgressMarker();
		}

		inline void setDoneProgressMarker(char ch=178) {
			progressbg = ch;
		}

		inline void setNotDoneProgressMarker(char ch=176) {
			progressnbg = ch;
		}

		inline void setFrameStyle(frame_style afs=null_frame_style) {
			fs = afs;
		}

		inline void setBackground(char ch) {
			defbg = ch;
		}

		inline void setProgress(int val=0) {
			value = val;
			normalizeProgress();
		}

		inline int getProgress() {
			return value;
		}

		inline void setMax(int amax) {
			max = amax;
			normalizeProgress();
		}

		inline int getMax() {
			return max;
		}

		inline void pushProgress(int val=1) {
			if(value<max && val>=0) {
				value += val;
			} else if(value>0 && val<0) {
				value += val;
			}
			normalizeProgress();
		}

		inline void normalizeProgress() {
			if(max<0) {
				value = 0;
				max = 0;
			}
			value = std::min(value, max + 1);
		}

		inline void setAction(action aact) {
			act = aact;
		}

		inline void draw(context& arg) {

			if(max!=0 && max==value) {
				if(!stateActionExecuted) {
					stateActionExecuted = true;
					act(arg, this);
				}
			} else {
				if(stateActionExecuted) {
					stateActionExecuted = false;
				}
			}

			int x, y;
			int tobjh = objh+2;
			for(int ity=0;ity<tobjh;++ity) {
				for(int itx=0;itx<objw;++itx) {
					x = itx+objx+parentX;
					y = ity+objy+parentY;
					arg.get().put(x, y, defbg);

					if(ity==0) {
						if(itx==0) {
							arg.get().put(x, y, fs.top_left);
						} else if(itx==objw-1) {
							arg.get().put(x, y, fs.top_right);
						} else {
							arg.get().put(x, y, fs.horizontal);
						}
					} else if(ity==tobjh-1) {
						if(itx==0) {
							arg.get().put(x, y, fs.bottom_left);
						} else if(itx==objw-1) {
							arg.get().put(x, y, fs.bottom_right);
						} else {
							arg.get().put(x, y, fs.horizontal);
						}
					} else {
						if(itx==0||itx==objw-1) {
							arg.get().put(x, y, fs.vertical);
						} else {
							if(itx<=(value*objw)/max) {
								arg.get().put(x, y, progressbg);
							} else {
								arg.get().put(x, y, progressnbg);
							}
						}
					}
				}
			}
		}

		inline bool isFocusable(context& arg) {
			return false;
		}

};





class edittextframe : public scene_object {
	private:
		char defbg;
		std::string text;
		frame_style fs;
		frame_style ffs;
		action act = null_action;
		int line = 0;
		int column = 0;
		int maxline = 0;
		int maxcollumn = 0;
		int texteditbegin = 0;
		int texteditend = 0;
		char cursor = 4;
		int linedelta = 0;
		int text_source_padding_left = 0;
		int max_visiblecollumn = 0;

		action actionOnTextType = null_action;

		bool hideOverflowText = true;
		bool autoAddSpaces = true;
		bool autoAddSpacesWithTrimming = true;

		inline std::string stringify(char c) {
			std::string ret = "0";
			ret[0]=c;
			return ret;
		}

		inline std::string stringify_array(char c, int len) {
			std::string ret = "";
			std::string s = stringify(c);
			for(int it=0;it<len;++it) {
				ret += s;
			}
			return ret;
		}


		inline int getStringTrimLeftSize(std::string src) {
			int it = 0;
			const int len = src.size();
			while(it<len && src[it]==' ') {
				++it;
			}
			return it;
		}

		inline int getStringTrimRightSize(std::string src) {
			const int len = src.size();
			int it = len-1;
			while(it>=0 && src[it]==' ') {
				--it;
			}
			return len-1-it;
		}

		inline std::string trimLeft(std::string src) {
			const int len = getStringTrimLeftSize(src);
			src.erase(src.size()-len-1, len);
			return src;
		}

		inline std::string trimRight(std::string src) {
			const int len = getStringTrimRightSize(src);
			src.erase(0, len);
			return src;
		}

		inline std::string trim(std::string src) {
			return trimLeft(trimRight(src));
		}

	public:

		edittextframe(int ax, int ay, int aw, int ah, std::string atext) {
			fs = default_frame_style;
			ffs = default_dbframe_style;
			defbg = ' ';
			objx = ax;
			objy = ay;
			objw = aw;
			objh = ah;
			text = atext;
		}

		inline void setAction(action act) {
			actionOnTextType = act;
		}

		inline void setOnTypeTextAction(action act) {
			actionOnTextType = act;
		}

		inline void setText(std::string atext) {
			text = atext;
		}

		inline std::string getText() {
			return text;
		}

		inline void setFrameStyle(frame_style afs=null_frame_style) {
			fs = afs;
		}

		inline void setFocusedFrameStyle(frame_style afs=null_frame_style) {
			ffs = afs;
		}

		inline void setBackground(char ch) {
			defbg = ch;
		}


		inline void draw(bool state, context& arg) {
			drawBasic(state, arg, text, true);
		}

		inline void moveToLine(int lin) {
			if(maxline>objh) {
				if(lin>objh) {
					linedelta = lin-objh+1;
				} else {
					linedelta = 0;
					line = lin;
				}
			} else {
				linedelta = 0;
				line = lin;
			}
		}

		inline void drawBasic(bool state, context& arg, std::string ftext, bool doNormalization) {

			max_visiblecollumn = objw - 4;

			arg.clearColorRegion(region(objx, objy, objw, objh));

			texteditend = -1;
			texteditbegin = -1;

			int x, y, tit, siz = ftext.size();
			bool lockLine = false;
			bool glacon = false;
			WORD glac = 0x00;

			tit = 0;

			if(linedelta>0) {
				int lns = 0;
				while(lns<linedelta && tit<siz) {
					++tit;
					if(ftext[tit]=='\n') {
						++lns;
					}
				}
			}

			for(int ity=0;ity<objh;++ity) {

				for(int itx=0;itx<objw;++itx) {
					x = itx+objx+parentX;
					y = ity+objy+parentY;
					if(defbg!=0x00) {
						arg.get().put(x, y, defbg);
					}
					if(!lockLine) {
						if(ity!=0&&ity!=objh-1&&itx!=0&&itx!=objw-1&&tit<siz) {
							if(ftext[tit]=='~') {
								WORD acc = 0;
								int ftit = tit;
								bool isglac = false;
								while(ftext[tit]!='&') {
									++tit;
									if(ftext[tit]=='b') {
										acc |= BACKGROUND_BLUE;
									} else if(ftext[tit]=='B') {
										acc |= FOREGROUND_BLUE;
									} else if(ftext[tit]=='g') {
										acc |= BACKGROUND_GREEN;
									} else if(ftext[tit]=='G') {
										acc |= FOREGROUND_GREEN;
									} else if(ftext[tit]=='r') {
										acc |= BACKGROUND_RED;
									} else if(ftext[tit]=='R') {
										acc |= FOREGROUND_RED;
									} else if(ftext[tit]=='[') {
										isglac = true;
										glacon = true;
									} else if(ftext[tit]==']') {
										glacon = false;
									}
								}
								++tit;
								--itx;
								if(isglac) {
									glac = acc;
								}
								arg.get().setColor(x, y, acc);
								//x-=tit-ftit+2;
							} else if(ftext[tit] == '\n') {
								if(ity==line+1 && tit>0) {
									if(ftext[tit-1]=='\n'){
										texteditbegin = texteditend = tit;
									}
								}
								lockLine = true;
								++tit;
								tit += text_source_padding_left;

								if(hideOverflowText) {
									if(itx == objw-2) {
										while(ftext[tit]!='\n' && tit<siz-1) {
											++tit;
										}
										++tit;
										lockLine = true;
										//--tit;
										//++y;
										//++ity;
									}
								}

							} else {

								if(hideOverflowText) {
									if(itx == objw-2) {
										while(ftext[tit]!='\n' && tit<siz-1) {
											++tit;
										}
										++tit;
										lockLine = true;
										//--tit;
										//++y;
										//++ity;
									}
								}

								if(!(hideOverflowText && itx == objw-2)) {
									arg.get().put(x, y, ftext[tit]);
									if(tit==siz-1) {
										maxline = ity;
									}
									if(itx==1 && ity==line+1) {
										texteditbegin = tit;
									} else if(x==1 && ity==line+1) {
										texteditend = tit-1;
									}

									if(ity==line+1) {

										if(itx==column+1) {
											arg.get().put(std::min(objx+objw+2, x), y, cursor);
											++x;
											--tit;
										}

										arg.get().setColor(x, y, BACKGROUND_BLUE | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
									} else if(glacon) {
										arg.get().setColor(x, y, glac);
									}
									++tit;
								}
							}
						}
					}

					if(ity==0) {
						if(state) {
							if(itx==0) {
								arg.get().put(x, y, ffs.top_left);
							} else if(itx==objw-1) {
								arg.get().put(x, y, ffs.top_right);
							} else {
								arg.get().put(x, y, ffs.horizontal);
							}
						} else {
							if(itx==0) {
								arg.get().put(x, y, fs.top_left);
							} else if(itx==objw-1) {
								arg.get().put(x, y, fs.top_right);
							} else {
								arg.get().put(x, y, fs.horizontal);
							}
						}
					} else if(ity==objh-1) {
						if(state) {
							if(itx==0) {
								arg.get().put(x, y, ffs.bottom_left);
							} else if(itx==objw-1) {
								arg.get().put(x, y, ffs.bottom_right);
							} else {
								arg.get().put(x, y, ffs.horizontal);
							}
						} else {
							if(itx==0) {
								arg.get().put(x, y, fs.bottom_left);
							} else if(itx==objw-1) {
								arg.get().put(x, y, fs.bottom_right);
							} else {
								arg.get().put(x, y, fs.horizontal);
							}
						}
					} else {
						if(state) {
							if(itx==0||itx==objw-1) {
								arg.get().put(x, y, ffs.vertical);
							}
						} else {
							if(itx==0||itx==objw-1) {
								arg.get().put(x, y, fs.vertical);
							}
						}
					}

				}
				tit += text_source_padding_left;
				lockLine = false;
				arg.get().moveCur(0, 1);
			}
			if(texteditend==-1) {
				texteditend = siz;
			}
			if(texteditbegin==-1) {
				texteditbegin = texteditend;
			}

			maxcollumn = texteditend - texteditbegin;

			if(column == maxcollumn) {
				arg.get().put(column+objx+1+parentX, line+objy+1+parentY, cursor);
			}


			arg.get().print(0, 0, "curx = "+intToStr(column) + "; cury = "+intToStr(line)+"; maxcollumn = "+intToStr(maxcollumn));
			arg.get().print(0, 1, "texteditend = "+intToStr(texteditend));
			arg.get().print(0, 2, "texteditbegin = "+intToStr(texteditbegin));
			arg.get().print(0, 3, "max_visiblecollumn = "+intToStr(max_visiblecollumn));
			arg.get().print(0, 4, "before=["+intToStr( getLinePaddingLeft() )+"] and after=["+intToStr( getLinePaddingRight() )+"]");


			if(doNormalization) {
				normalize();
				drawBasic(state, arg, ftext, false);
			}
		}

		inline bool isFocusable(context& arg) {
			return true;
		}

		inline void moveCollumn(int dist=0) {
			if(dist==0) return;
			if(dist<0) {
				prevCollumn(-dist);
			} else {
				nextCollumn(dist);
			}
		}

		inline void nextCollumn(int dist=1) {
			column+=dist;
			if(column>=max_visiblecollumn-1 && column<=maxcollumn) {
				column = max_visiblecollumn-1;
				text_source_padding_left += dist;
			} else if(column>maxcollumn && line<maxline-1) {
				column = 900000000;
				//++text_source_padding_left;
				nextLine();
			}
		}

		inline void prevCollumn(int dist=1) {
			column-=dist;
			if(column<0 && text_source_padding_left>0) {
				text_source_padding_left -= dist;
				column += dist;
			}
			if(column<0 && line!=0) {
				column = 900000000;
				prevLine();
			}
		}

		inline void normalize() {
			normalizeCollumn();
			normalizeLine();
		}

		inline void normalizeCollumn() {
			if(column>maxcollumn) column=( (max_visiblecollumn>maxcollumn)? maxcollumn : max_visiblecollumn );
			if(column<0) column=0;
		}

		inline void normalizeLine() {
			if(line>maxline) line=maxline;
			if(line<0) line=0;
		}

		inline void textRemove(int position, int length) {
			if(position>text.size()) return;
			text.erase(position, length);
		}

		inline std::string getLineText() {
			return text.substr(texteditbegin, texteditend+1);
		}

		inline int getLinePaddingLeft() {
			std::string bef = getLineText();
			int it = 0;
			const int len = bef.size();
			while(it<len && bef[it]==' ') {
				++it;
			}
			return it;
		}

		inline int getLinePaddingRight() {
			std::string bef = getLineText();
			const int len = bef.size();
			int it = len-1;
			while(it>=0 && bef[it]==' ') {
				--it;
			}
			return len-1-it;
		}

		inline std::string getLineTextBeforeCursor() {
			return text.substr(texteditbegin, column);
		}

		inline std::string getLineTextAfterCursor() {
			return text.substr(column, texteditend);
		}

		inline void textInsert(int position, std::string what) {
			if(position>text.size()) return;
			text.insert(position, what);
		}

		inline void cursorBackspace() {
			textRemove(texteditbegin + column - 1, 1);
			prevCollumn();
		}

		inline void cursorDelete() {
			textRemove(texteditbegin + column, 1);
		}

		inline void notifyNewLine(int dist=1) {
			maxline += dist;
		}

		inline void notifyNewCollumn(int dist=1) {
			texteditend += dist;
			maxcollumn += dist;
		}

		inline void cursorInsertEndl() {
			if(autoAddSpaces) {
				if(autoAddSpacesWithTrimming) {
					textInsert(texteditbegin + column, "\n"+stringify_array(' ', getLinePaddingLeft()-getStringTrimLeftSize(getLineTextAfterCursor())));
				} else {
					textInsert(texteditbegin + column, "\n"+stringify_array(' ', getLinePaddingLeft()));
				}
			} else {
				textInsert(texteditbegin + column, "\n");
			}
			notifyNewLine();
			nextLine(1);
		}

		inline void cursorInsertText(std::string text) {
			textInsert(texteditbegin + column, text);
			notifyNewCollumn(text.size()+1);
			nextCollumn(text.size());
		}

		inline int getTextCursorPosition() {
			return texteditbegin + column;
		}

		inline int getTextSelectedLineBegin() {
			return texteditbegin;
		}

		inline int getTextSelectedLineEnd() {
			return texteditend;
		}

		inline int getTextLines() {
			return maxline;
		}

		inline int getSelectedLineNumber() {
			return line+linedelta;
		}

		inline int getSelectedCollumnNumber() {
			return column;
		}


		inline void nextLine(int dist=1) {
			if(line>=maxline-1) { line = maxline-1; return; }
			text_source_padding_left = 0;//(maxcollumn<max_visiblecollumn) ? 0 : maxcollumn - max_visiblecollumn;
			if(line>=objh-5) {
				if(dist>0) {
					linedelta += dist;
					return;
				}
			}
			line+=dist;
			//column = 0;
			if(line>maxline-1) line=maxline-1;
		}

		inline void prevLine(int dist=1) {
			if(line<=0) { line = 0; return; }
			text_source_padding_left = 0;//(maxcollumn<max_visiblecollumn) ? 0 : maxcollumn - max_visiblecollumn;
			if(line<=0) {
				if(dist>0) {
					linedelta -= dist;
					return;
				}
			}
			line-=dist;
			//column = 0;
			if(line<0) line=0;
		}

		inline void moveLine(int dist=0) {
			if(dist==0) return;
			if(dist<0) {
				prevLine(-dist);
			} else {
				nextLine(dist);
			}
		}

		inline bool probeKey(context& arg, key& keycode) {
			arg.get().setCurPos(45, 20);
			arg.get() << ("edittf.probe ");
			arg.get().setCurPos(50, 21);
			arg.get() << ((int)keycode.getKeySpecialCode());

			if(keycode.isSpecialKey()) {
				arg.get().setCurPos(55, 22);
				arg.get() << "special key";
				switch(keycode.getKeySpecialCode()) {
					case 46: case 47: {
						arg.get().setCurPos(55, 23);
						arg.get() << "key-46/47";
						return false;
						break;
					}
				}
			}
			return false;
		}

		inline void onKeyEvent(context& arg, key& keycode) {

			if(keycode == WACCGL_KEY_TEXT_NEXT_LINE) {
				nextLine(); act(arg, this);
			} else if(keycode == WACCGL_KEY_TEXT_PREV_LINE) {
				prevLine(); act(arg, this);
			} else if(keycode == WACCGL_KEY_TEXT_NEXT_COLUMN) {
				nextCollumn(); act(arg, this);
			} else if(keycode == WACCGL_KEY_TEXT_PREV_COLUMN) {
				prevCollumn(); act(arg, this);
			} if(keycode == WACCGL_KEY_TEXT_DELETE) {
				cursorDelete();
			}

			if(keycode.isSpecialKey()) return;

			if(keycode == WACCGL_KEY_TEXT_BACKSPACE) {
				cursorBackspace();
			} else if(keycode == WACCGL_KEY_TEXT_NEW_LINE) {
				cursorInsertEndl();
			} else if(keycode == WACCGL_KEY_TEXT_TABULATION) {
				cursorInsertText("    ");
			} else {
				cursorInsertText(stringify(keycode.getKeyCode()));
			}

			actionOnTextType(arg, this);
			//putCursor();
		}
};




/*

class vscrollbar : public scene_object {
	private:
		frame_style fs;
		frame_style mfs;

	public:

		vscrollbar(int ax, int ay, int aw, int ah) {
			fs = default_frame_style;
			mfs = default_dbframe_style;
			objx = ax;
			objy = ay;
			objw = aw;
			objh = ah;
		}

		inline void onMouseEventFocused(context& arg, mouse_info& mouse_data) {
			moveScroll(arg, mouse_data.wheel_pos_delta);
			mouse_data.wheel_pos_delta = 0;
		}

		inline ME_STATE onMouseEvent(context& arg, mouse_info& mouse_data) {
			if(mouse_data.x>=objx+parentX && mouse_data.x<=objx+parentX+objw) {
				if(mouse_data.y>=objy+parentY && mouse_data.y<=objy+parentY+objh) {
					return ME_FOCUSED;
				}
			}
			return ME_NULL;
		}

		inline void setFrameStyle(frame_style afs) {
			fs = afs;
		}

		inline void setMarkedFrameStyle(frame_style afs) {
			mfs = afs;
		}

		inline void setBackground(char ch) {
			defbg = ch;
		}

		inline void draw(bool state, context& arg) {

			for(int ity=0;ity<tobjh;++ity) {
				for(int itx=0;itx<objw;++itx) {
					x = itx+objx+parentX;
					y = ity+objy+parentY;
					arg.get().put(x, y, defbg);

					if(ity==0) {
						if(itx==0) {
							arg.get().put(x, y, fs.top_left);
						} else if(itx==objw-1) {
							arg.get().put(x, y, fs.top_right);
						} else {
							arg.get().put(x, y, fs.horizontal);
						}
					} else if(ity==tobjh-1) {
						if(itx==0) {
							arg.get().put(x, y, fs.bottom_left);
						} else if(itx==objw-1) {
							arg.get().put(x, y, fs.bottom_right);
						} else {
							arg.get().put(x, y, fs.horizontal);
						}
					} else {
						if(itx==0||itx==objw-1) {
							arg.get().put(x, y, fs.vertical);
						}
					}
				}
			}
		}

		inline bool isFocusable(context& arg) {
			return true;
		}

};


*/
