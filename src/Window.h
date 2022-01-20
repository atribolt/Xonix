#ifndef WINDOW_H
#define WINDOW_H

#include "Classes.h"

class Window {
public:
  ~Window();
  static Window& instance();

  void init();
  void open();
  void close();

  bool isOpen() const;

  WindowPtr getWindow();
  RenderTargetPtr getCanvas();

private:
  Window();

  RenderWindowPtr _window;
};

#endif // WINDOW_H
