
#include <iostream>
#include <FL/Fl_Window.h>
#include <FL/Fl_Box.h>
#include <FL/Fl_Group.h>

void draw() {
	Fl_Window *window = new Fl_Window(340, 480, "Test");
	Fl_Group *p_test = new Fl_Group(0, 0, 100, 100);
	p_test->end();
	window->end();
	window->show();
	onStart();
}

void onStart() {
	std::cout << "Hello world!";
}
	
