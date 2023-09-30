#include "database_window.h"
#include "util/hide_all_windows.h"

DatabaseWindow::DatabaseWindow(int x, int y, int w, int h) : Fl_Window(x, y, w, h, "Citizen Database"), citizen_db(), area(0, 0, 100, 20, "Area"), income(0, 20, 100, 20, "Income"), family(0, 40, 100, 20, "Family") {
	resizable(this);
	end();
}

void DatabaseWindow::hide() {
	Fl_Window::hide();
	hide_all_windows();
}