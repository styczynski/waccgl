
#include <string>
#include <waccgl.h> //Include WACCGL
using namespace waccgl; //Use deafult WACCGL namespace

//Example WACCGL usage : using internal windows
int main( void ) {

	console cons({ "App title", 600, 600, 0, 0 });
	cons.enableMouse(true); //Enable mouse input
	cons.startAutoKeyReader(); //Enable auto key-reading
	cons.enableReversedVideoMode(true); //Set inverted wideo mode
	cons.setMouseSensivityX(0.6);//Set the mouse sensivity on X axis
	cons.setMouseSensivityY(0.6);//Set the mouse sensivity on Y axis
	context cont(cons); //Create application context

	scene test_scene; //Create scene

	textframe tf(2, 8, 25, 25, "Example applciation showing basic WACCGL functionality."); //Textframe
	test_scene.add(tf); //...text frame.

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
