#include <iostream>
#include <FL/Fl_Group.h>
#include <FL/Fl_Output.h>
#include <FL/Fl_Window.h>

void onStart() {
	std::cout << "Hello world!";
}
	
void draw() {
	Fl_Window *window = new Fl_Window(340, 480, "Test");
	Fl_Group *p_test = new Fl_Group(0, 0, 100, 100);
	Fl_Output *p_test_text_0 = new Fl_Output(0, 0, 100, 100, "This is a .CPPHTML webpage!");
	Fl_Output *p_test_text_1 = new Fl_Output(0, 0, 100, 100, "You can write multiple lines!");
	p_test->end();
	window->end();
	window->show();
	onStart();
}
