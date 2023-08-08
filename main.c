#include <stdio.h>
#include <X11/Xlib.h>
#include "window_manager.h"

#define nullptr NULL


Wm wm_init(){
  Wm wm;
  Display *display = XOpenDisplay(nullptr);
  wm.display = display;
  if(display == nullptr){
    printf("Failed to open X Display \n");
  }

  wm.root = DefaultRootWindow(display);

  printf("Window Manager Started!");
  return wm;
}

void wm_close(Wm wm){
  XCloseDisplay(wm.display);
}

int main(){
  Wm wm = wm_init();
  wm_close(wm);
}