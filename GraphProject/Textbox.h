#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27   //defines values for key inputs

class Textbox{
public:
    bool inTextbox = false;
    int numCharTyped = 0;
    string nameTyped;
    Textbox(){}

    Textbox(int size, sf::Color color, bool sel){
        textbox.setCharacterSize(size);
        textbox.setFillColor(color);
        isSelected=sel;
        if (sel){
            textbox.setString("_");     //allows user to know where they are typing by showing a "_"
        }
        else{
            textbox.setString("");   //if not selected it goes away
        }
    }

    void setFont(sf::Font &font){
        textbox.setFont(font);
    }

    void setPosition(sf::Vector2f pos){     //set font position and text limit of textbox
        textbox.setPosition(pos);
    }

    void setLimit(bool ToF){
        hasLimit = ToF;
    }

    void setLimit(bool ToF, int lim){
        hasLimit = ToF;
        limit = lim-1;
    }

    void setSelected(bool sel){
        isSelected = sel;
        if(!sel){
            std::string t = text.str();
            std::string newT = "";              //if selected set the string based on input
            for(int i=0; i<t.length();i++){
                newT += t[i];
            }
            textbox.setString(newT);
        }
    }

    std::string getText(){
        return text.str();
    }

    void drawTo(sf::RenderWindow &window){    //draws the textbox to screen
        window.draw(textbox);
    }

    void typedOn(sf::Event input){
        if(isSelected){
            int charTyped = input.text.unicode;
            if(charTyped < 128){
                if(hasLimit){
                    if(text.str().length() <= limit){       //if selected check limit and run input logic if typing
                        inputLogic(charTyped);
                    }
                    else if(text.str().length() > limit && charTyped==DELETE_KEY){ //if delete key pushed then delete the last character
                        deleteLastChar();
                    }
                }
                else{
                    inputLogic(charTyped);
                }
            }
        }
    }
private:
    sf::Text textbox;
    std::ostringstream text;
    bool isSelected = false;
    bool hasLimit = false;
    int limit;

    void inputLogic(int charTyped){
        if(charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped !=ESCAPE_KEY){  //based on input determine what to do with text
            text << static_cast<char>(charTyped); //if not specified keys then add typed text to string
        }
        else if(charTyped == DELETE_KEY){  //if we are pushing delete then delete last character
            if(text.str().length() > 0){
                deleteLastChar();
            }
        }
        numCharTyped=text.str().length();
        nameTyped=text.str();
        textbox.setString(text.str()+"_");  //add string to textbox and then add "_"
    }

    void deleteLastChar(){
        std::string t = text.str();
        std::string newT = "";
        for(int i=0; i < t.length() - 1;i++){  //function to delete last character of string when hitting delete key
            newT += t[i];
        }
        text.str("");
        text << newT;
        textbox.setString(text.str());
    }
};
