
#include <string>
#include <waccgl.h> //Include WACCGL
using namespace waccgl; //Use deafult WACCGL namespace

//Example WACCGL usage : using internal windows
int main( void ) {

	console cons({ "App title", 600, 600, 0, 0 });
	cons.enableMouse(false); //Enable mouse input
	cons.startAutoKeyReader(); //Enable auto key-reading
	context cont(cons); //Create application context

	scene test_scene; //Create scene

	textframe tf(2, 8, 25, 25, ""); //Textframe
	selbox selectionBox(5, 35, 3, {"Option1", "Option2VeryLongListItemName", "Option3", "Option4", "OptionInfinity"});
	exlistbox selectionList(40, 8, 3, {"Option1", "Option2", "Option3", "Option4", "LOL"});
	checkbox checkBox(40, 2, "Some check box");
	button showWindowBt(2, 3, "Exit"); //A button
	selectionBox.setWidth(25);
	selectionList.setHeight(9);
	selectionList.setWidth(25);
	tf.setText(
		std::string("") +
		"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Praesent non est quam. Praesent fermentum, eros dignissim placerat tempus, augue ex imperdiet massa, in mollis ex leo quis arcu. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Integer ornare fermentum justo, vitae placerat augue semper vel. Fusce hendrerit, purus fringilla cursus porttitor, nisi eros hendrerit urna, vitae placerat tellus nisi eu nisl. Donec ornare rutrum porta. Aliquam eget lacinia arcu. Aliquam tristique aliquet diam, ut sodales justo eleifend eget. Proin neque lacus, finibus et blandit sit amet, mattis tempor lectus. Suspendisse in rutrum erat. Duis tempus eget lacus et porta. Quisque risus lectus, vehicula eget velit vitae, aliquam dictum odio. Mauris ac orci quis diam faucibus finibus. Cras fermentum eleifend purus at pretium. Nullam placerat auctor sem vel accumsan."
	);
	//Create text frame with some lorem ipsum.
	assignAction(showWindowBt, {
		showWindowBt.setText("Clicked"); //Change button text?
		cont.exit(); //Trigger context exit event.
	});
	//Set on click listener for showWindowBt


	test_scene.add(selectionBox); //Add everything to the scene... the selection box
	test_scene.add(checkBox); //..check box...
	test_scene.add(selectionList); //...selection list (similar to the selbox control, but looks like a list)...
	test_scene.add(showWindowBt); //...button...
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
