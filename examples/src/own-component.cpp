
#include <string>
#include <waccgl.h> //Include WACCGL
using namespace waccgl; //Use deafult WACCGL namespace

//Now we will create custom component that will be stationary.
//This component can be focused and clicked.
//When clicked it should move forward forever...
// and ever...
// ...
//
class own_component : public scene_object {
	private:
		bool active = false;

	public:
		own_component() {

		}

		inline bool isFocusable() { //Tells if this component can be focused.
			return true;
		}

		inline void whenClicked(context& arg) { //When the compont is clicked...
			active = true;
		}

		inline void draw(bool state, context& cont) {
				//Performs drawing (state is focus-state of this component)

				cont.get().setCurPos(getPosX(), getPosY());

				for(int i=0; i<7; ++i) {
					if(state) {//If the component is focused
						cont.get() << std::string("*******"); //Perform some drawing
					} else { //If the component isn't focused
						cont.get() << std::string("......."); //Perform some drawing
					}
					cont.get().moveCur(-7, 1); //Move cursor...
				}

				if(active) {
					setPosX(getPosX()+1);
					if(getPosX()>50) setPosX(1), setPosY(getPosY()+1);
					if(getPosY()>50) setPosY(1);
				}
		}
};

//Example WACCGL usage : using internal windows
int main( void ) {

	console cons({ "App title", 600, 600, 0, 0 });
	context cont(cons); //Create application context
	cons.enableMouse(true); //Enable mouse input
	cons.startAutoKeyReader(); //Enable auto key-reading

	scene test_scene; //Create scene

	own_component our_magical_component; //Create an instance of our custom component
	own_component our_magical_component2; //Create another instance...
	own_component our_magical_component3; //And one more...


	our_magical_component.setPosX(2); //Set up all components positions...
	our_magical_component.setPosY(2);
	our_magical_component2.setPosX(15);
	our_magical_component2.setPosY(15);
	our_magical_component3.setPosX(30);
	our_magical_component3.setPosY(30); //Done. Uff...

	test_scene.add(our_magical_component); //Add the "magical component" to the scene
	test_scene.add(our_magical_component2); //And the other one...
	test_scene.add(our_magical_component3); //Finally add the last!

	test_scene.show(true); //Set scene visibility
	cont.add(test_scene); //Add the scene to the context

	bool exitApplication = false; //Some variable
	cont.exitOn(WACCGL_KEY_ESCAPE); //Terminate application when the escape is pressed
	cont.setOnExitAction([&](context& arg, scene_object* src) mutable { //Handler invoked ehn applciation must exit
		exitApplication = true; //Set the UILoop marker to true
	});

	UILoop { //GUI loop in the current thread
		cons.clear(); //This clears console buffer (if not used buffer will will be filled with old graphics)
		char key = cont.readKeyboardInput(); //Read key
		cont.update(key); //Simulate context key event
		cont.draw(); //Draw everything (virtually)
		cons.flush(); //Flush the application (put everything into the screen)
		if(exitApplication) return 0; //If context exit action was invoked this thread should be terminated using return 0;
		cons.rest(); //Console rests (release CPU)
	}

	return 0;
}
