#include <stdio.h>
#include <X11/Xlib.h>
#include "window_manager.h"

#define nullptr NULL

void on_create_notify(XCreateWindowEvent e){};
void on_destroy_notify(XDestroyWindowEvent e){};
void on_reparent_notify(XReparentEvent e){};


void on_configure_request(WM wm,XConfigureRequestEvent e);


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

  for(;;){
    XEvent e;
    XNextEvent(wm.display, &e);

    switch(e.type){
      case CreateNotify:
        on_create_notify(e.xcreatewindow);
        break;
      case DestroyNotify:
        on_destroy_notify(e.xdestroywindow);
        break;
      case ReparentNotify:
        on_reparent_notify(e.xreparent);
        break;
      case ConfigureRequest:
        on_configure_request(wm, e.xconfigurerequest);
        break;

      default: 
        printf("Ignored Event");
    }
  }
}

void on_configure_request(WM wm, XConfigureRequestEvent e){
  XWindowChanges changes;

  changes.x = e.x;
  changes.y = e.y;
  changes.width = e.width;
  changes.height = e.height;
  changes.border_width = e.border_width;
  changes.sibling = e.above;
  changes.stack_mode = e.detail;

  XConfigureWindow(wm.display, e.window, e.value_mask, &changes);
}

int main(){
  WM wm = wm_init();
  wm_run(wm);
  wm_close(wm);
}