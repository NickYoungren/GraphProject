#pragma once
#include <SFML/Graphics.hpp>

class Button{
public:
    Button(){}
    int textLength=0;
    Button(std::string t, sf::Vector2f size, int charSize, sf::Color bgColor, sf::Color textColor){
        textLength = t.length()/2;
        text.setString(t);
        text.setFillColor(textColor);     //set properties of button
        text.setCharacterSize(charSize);
        button.setSize(size);
        button.setFillColor(bgColor);
    }

    void setFont(sf::Font &font){
        text.setFont(font);       //set font
    }

    void setBackColor(sf::Color color){  //set color
        button.setFillColor(color);
    }

    void setTextColor(sf::Color color){ //set text color
        text.setFillColor(color);
    }

    void setPosition(sf::Vector2f pos){
        button.setPosition(pos);

        float xPos = (pos.x + button.getLocalBounds().width / 2) - textLength*10.56;  //set position of text based on pixel size of font
        float yPos = (pos.y + button.getLocalBounds().height / 2)-12;
        text.setPosition({xPos,yPos});
    }

    void drawTo(sf::RenderWindow &window){
        window.draw(button);
        window.draw(text);
    }

    bool isMouseOver(sf::RenderWindow &window){
        float mouseX = sf::Mouse::getPosition(window).x;
        float mouseY = sf::Mouse::getPosition(window).y;
        float btnPosX = button.getPosition().x;
        float btnPosY = button.getPosition().y;
        float btnXPosWidth = button.getPosition().x + button.getLocalBounds().width;  //if mouse is over/not over then select is set true/false
        float btnYPosHeight = button.getPosition().y + button.getLocalBounds().height;

        if(mouseX < btnXPosWidth && mouseX > btnPosX && mouseY < btnYPosHeight && mouseY > btnPosY){
            return true;
        }
        return false;
    }
private:
    sf::RectangleShape button;  //set shape and text
    sf::Text text;
};
