
#include <string>
#include <waccgl.h> //Include WACCGL
using namespace waccgl; //Use deafult WACCGL namespace

//Example WACCGL usage : using internal windows
int main( void ) {

	console cons({ "App title", 200, 400, 0, 0 });
	cons.enableMouse(false); //Enable mouse input
	cons.startAutoKeyReader(); //Enable auto key-reading
	context cont(cons); //Create application context

	scene test_scene; //Create scene
	window wnd(7, 7, 50, 50); //Create an internal window
	vscrollbar sb(0, 0, 18); //Create the vertical scrollbar
	button bt(20, 20, "Close"); //Create a button
	bt.setFrameStyle(create_frame_style('X')); //Set button frame
	assignAction(bt, {
		//At the event handling loop there are two variables - context& arg (cuurent context) and
		//scene_object* src - pointer to the event target GUI object
		//Event-handler are just C++ lambdas. ('action' type)
		//assignAction(...) is just a syntax-sugar macro for default actions.
		//Each cotrol's got few setOn...Action and only one setAction method
		//If you use assignAction macro you're setting up action using setAction(...) method.
		//SetAction(...) behaviour depends on the element type (on button it's click event handler, on vscrollbar it listens for srcoll change)

		wnd.close();
		wnd.show(false);
	});


	wnd
	  .add(sb)
	  .add(bt)
	  .pack();
	  //Add everything to the internal window

	textframe tf(2, 8, 75, 25, ""); //Textframe
	button showWindowBt(2, 3, "Show internal window!"); //A button
	tf.setText(
		std::string("") +
		"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Praesent non est quam. Praesent fermentum, eros dignissim placerat tempus, augue ex imperdiet massa, in mollis ex leo quis arcu. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Integer ornare fermentum justo, vitae placerat augue semper vel. Fusce hendrerit, purus fringilla cursus porttitor, nisi eros hendrerit urna, vitae placerat tellus nisi eu nisl. Donec ornare rutrum porta. Aliquam eget lacinia arcu. Aliquam tristique aliquet diam, ut sodales justo eleifend eget. Proin neque lacus, finibus et blandit sit amet, mattis tempor lectus. Suspendisse in rutrum erat. Duis tempus eget lacus et porta. Quisque risus lectus, vehicula eget velit vitae, aliquam dictum odio. Mauris ac orci quis diam faucibus finibus. Cras fermentum eleifend purus at pretium. Nullam placerat auctor sem vel accumsan." +
		"Nullam lectus tortor, cursus et ex non, fermentum vehicula erat. Mauris et est nisi. Maecenas pulvinar et eros eu posuere. Donec sit amet arcu lectus. Vestibulum ut mi ac lectus facilisis congue id sit amet felis. Maecenas mattis dolor ut lorem consectetur iaculis. Suspendisse in condimentum quam, feugiat laoreet ex. Proin mollis a elit in tincidunt." +
		"Donec et malesuada leo. Proin at pretium mauris. Praesent volutpat magna ultricies laoreet rutrum. In vitae lacus volutpat, porta magna et, consectetur elit. Praesent non neque eu est convallis sagittis. Aliquam ultricies urna ante, id sodales lacus facilisis quis. Sed tincidunt erat molestie tellus consectetur rutrum. Maecenas aliquet, dolor eget cursus sollicitudin, ipsum magna viverra nunc, eu facilisis risus est porttitor leo. Duis ut mauris tellus. Proin suscipit consectetur nisl, in tincidunt ligula volutpat vel." +
		"Ut est massa, ultrices vel ipsum ut, maximus volutpat nunc. Proin dictum velit vel accumsan feugiat. Etiam ut consectetur nulla. Suspendisse at quam auctor, lacinia urna a, fringilla lacus. Nullam ullamcorper eros lacus, eu hendrerit mi tempus id. Nunc vel metus blandit, bibendum lectus a, egestas est. Nulla cursus sapien id turpis varius, volutpat ullamcorper neque venenatis." +
		"Quisque vel porta libero. Nullam in tempus ligula, vitae tincidunt odio. Praesent et arcu eget sapien blandit ultrices. Donec massa urna, ornare eu consequat nec, sagittis at ex. Curabitur convallis in erat et fringilla. Proin sed iaculis tortor. Curabitur nibh turpis, fringilla quis consectetur ac, condimentum eget sem. Cras maximus quis turpis ut fringilla."
	);
	//Create text frame with some lorem ipsum.
	assignAction(showWindowBt, {
		wnd.open(); //Open a window
		showWindowBt.setText("Clicked"); //Change button text?
	});
	//Set on click listener for showWindowBt


	test_scene.add(showWindowBt); //Add everything to the scene... the button
	test_scene.add(tf); //Text frame
	test_scene.add(wnd); //Now add the internal window to the scene
	test_scene.show(true); //Set scene visibility

	wnd.setTopmost(true); //Make the internal window topmost

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
