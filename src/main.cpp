#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

int main(int argc, char** argv) {
  RenderWindow window({100, 100}, "Xonix");

  while(window.isOpen()) {
    Event ev;
    while(window.pollEvent(ev)) {
      switch(ev.type) {
        case Event::Closed:
          window.close();
          break;
        default: break;
      }
    }

    window.clear();
    window.draw(CircleShape(50, 32));
    window.display();
  }
}
