#include <stdio.h>
#include <X11/Xlib.h>
#include "window_manager.h"

#define nullptr NULL

static int on_x_error(Display *display, XErrorEvent *e);
static int OnWMDetected(Display* display, XErrorEvent* e);

WM wm_init(){
  WM wm;
  Display *display = XOpenDisplay(nullptr);
  wm.display = display;
  if(display == nullptr){
    printf("Failed to open X Display \n");
  }

  wm.root = DefaultRootWindow(display);

  printf("Window Manager Started!");
  return wm;
}

void wm_close(WM wm){
  XCloseDisplay(wm.display);
}

void wm_run(WM wm){
  XSelectInput(
      wm.display,
      wm.root,
      SubstructureRedirectMask | SubstructureNotifyMask);
  XSync(wm.display, false);

  wm.wm_running = true;
}

int main(){
  WM wm = wm_init();
  wm_close(wm);
}