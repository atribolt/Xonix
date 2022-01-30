#ifndef TEXTPAINTER_H
#define TEXTPAINTER_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

void drawText (
    std::string const& text,
    sf::RenderTarget& target,
    sf::Vector2f const& position = {0, 0},
    sf::Color color = sf::Color::White,
    int fontSize = 10)
{
  static sf::Font font;
  font.loadFromFile("font.ttf");

  static sf::Text textForm(text, font, fontSize);
  textForm.setFillColor(color);
  textForm.setPosition(position);

  target.draw(textForm);
}


#endif // TEXTPAINTER_H
