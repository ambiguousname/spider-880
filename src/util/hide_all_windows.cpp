#include <FL/Fl.H>
#include <FL/Fl_Window.H>

void hide_all_windows() {
	while(Fl::first_window()) {
		Fl::first_window()->hide();
	}
}