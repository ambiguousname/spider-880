#pragma once
#include <FL/Fl_Window.H>
#include <string>

void initializeBrowser();
void uninitializeBrowser();

void newWindow(std::string site, std::string filename);

class BrowserWindow : public Fl_Window {

};