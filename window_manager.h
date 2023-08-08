#include "X11/Xlib.h"
#include "stdbool.h"

typedef struct 
{
  Display *display;
  Window root;
  bool wm_running;
}WM;

