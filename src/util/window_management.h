#pragma once
#pragma once
#include <FL/Fl_Window.H>

namespace WindowManagement {
	void hide_all_windows(Fl_Widget*);
	void hide_all_windows();

	void essential_hide(Fl_Widget*);

	void set_main(Fl_Window* _main_window);
}