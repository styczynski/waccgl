
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
	scene second_scene; //Second scene

	textframe tf(2, 8, 25, 25, "Example applciation showing basic WACCGL functionality."); //Textframe
	button bt(2, 2, "Press me!");

	assignAction(bt, {
			cont.showOnly(&second_scene); //Now the button shows the second scene!
	});

	test_scene.add(tf); //Add the text frame to the scene.
	test_scene.add(bt); //And the button now.

	textframe tf2(2, 8, 25, 25, "Second text frame"); //Another textframe
	button bt2(2, 2, "Me too!"); //Another button

	assignAction(bt2, {
			cont.showOnly(&test_scene);
	});

	second_scene.add(tf2);
	second_scene.add(bt2);

	cont.add(test_scene); //Add the scene to the context
	cont.add(second_scene); //Add the second scene

	cont.showOnly(&test_scene); //Show only the first scene
	cont.setChangeAnimation(&chanim_slide); //Set scene change animation to the slide animation.


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
