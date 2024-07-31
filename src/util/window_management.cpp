#include "window_management.hpp"
#include <FL/Fl.H>
#include <vector>

namespace WindowManagement {
	void hide_all_windows(Fl_Widget*) {
		hide_all_windows();
	}
	void hide_all_windows() {
		while(Fl::first_window()) {
			Fl::first_window()->hide();
		}
	}
	void hide_all_windows(void*) {
		hide_all_windows();
	}

	Fl_Window* main_window;

	void set_main(Fl_Window* _main_window) {
		main_window = _main_window;
	}

	void essential_hide(Fl_Widget*) {
		main_window->show();
		return;
	}
}