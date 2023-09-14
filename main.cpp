#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_PNG_Image.H>
 
int main(int argc, char **argv) {
  Fl_Window *window = new Fl_Window(340,180, "Test");
  Fl_Box *box = new Fl_Box(20,40,300,100);

  Fl_PNG_Image *img = new Fl_PNG_Image("./test.png");

  Fl_Image* temp = img->copy(box->w(), box->h() * img->h()/img->w());

  box->image(temp);
  
  window->end();
  window->show(argc, argv);
  return Fl::run();
}