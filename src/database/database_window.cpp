#include "database_window.h"

DatabaseWindow::DatabaseWindow(int x, int y, int w, int h) : Fl_Window(x, y, w, h, "Citizen Database"), citizen_db(), area(0, 0, 20, 20, "Area"), income(0, 40, 20, 20, "Income"), family(0, 60, 20, 20, "Family") {
	
	end();
}