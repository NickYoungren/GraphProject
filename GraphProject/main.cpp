#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Textbox.h"
#include "Button.h"
#include "Graphs.h"
#include <string>
#include <vector>
#include <chrono>

using namespace sf;
using namespace std;
using namespace std::chrono;


int main(){
    bool OnOffButton;
    bool OnOffButton2;
    string currentName1;
    string currentName2;
    string currentName3;
    string currentName4;
    srand(time(NULL));
    RenderWindow window;
    Vector2i centerWindow((VideoMode::getDesktopMode().width / 2)-900, (VideoMode::getDesktopMode().height /2)-650); //window setup
    window.create(VideoMode(1800,1100), "Lego Meta", Style::Titlebar | Style::Close);
    window.setPosition(centerWindow);
    window.setKeyRepeatEnabled(true);

    Textbox textbox1(25, Color::Black,false);           //sets up first search textbox
    Font arial;
    arial.loadFromFile("C:/GraphProject/ArialCE.ttf");
    textbox1.setFont(arial);
    textbox1.setPosition({250,250});
    textbox1.setLimit(true,30);

    Textbox textbox2(25, Color::Black,false);           //sets up second text box
    textbox2.setFont(arial);
    textbox2.setPosition({250,350});
    textbox2.setLimit(true,30);

    Button text1("Search Name 1", {425,50}, 20, Color::Green, Color::Black);            //initialize text and buttons on screen
    text1.setPosition({250,250});
    text1.setFont(arial);

    Button text2("Search Name 2", {425,50}, 20, Color::Green, Color::Black);
    text2.setPosition({250,350});
    text2.setFont(arial);

    Button SearchButton("Search BFS", {200,50}, 20, Color::Green, Color::Black);
    SearchButton.setPosition({250,450});
    SearchButton.setFont(arial);

    Button SearchButton2("Search DFS", {200,50}, 20, Color::Green, Color::Black);
    SearchButton2.setPosition({475,450});
    SearchButton2.setFont(arial);

    Text searchText;
    searchText.setFont(arial);
    searchText.setString("Enter something into both text boxes!");
    searchText.setCharacterSize(35);
    searchText.setFillColor(Color::Yellow);
    searchText.setPosition({170,525});
    Text searchText2;
    searchText2.setFont(arial);
    searchText2.setCharacterSize(35);
    searchText2.setFillColor(Color::Green);

    Button randNameButton("Generate Random Person", {300,50}, 20, Color::Green, Color::Black);
    randNameButton.setPosition({575,700});
    randNameButton.setFont(arial);

    Button printConnection("Show the Connection!", {300,50}, 20, Color::Green, Color::Black);
    printConnection.setPosition({1175,950});
    printConnection.setFont(arial);

    Text person1, person2, person3, person4, person5, person6, person7, person8, person9;    //add all 9 people text
    person1.setFont(arial); person2.setFont(arial); person3.setFont(arial); person4.setFont(arial); person5.setFont(arial); person6.setFont(arial); person7.setFont(arial); person8.setFont(arial); person9.setFont(arial);
    person1.setCharacterSize(20); person2.setCharacterSize(20); person3.setCharacterSize(20); person4.setCharacterSize(20); person5.setCharacterSize(20); person6.setCharacterSize(20); person7.setCharacterSize(20); person8.setCharacterSize(20); person9.setCharacterSize(20);
    person1.setFillColor(Color::White); person2.setFillColor(Color::White); person3.setFillColor(Color::White); person4.setFillColor(Color::White); person5.setFillColor(Color::White); person6.setFillColor(Color::White); person7.setFillColor(Color::White); person8.setFillColor(Color::White); person9.setFillColor(Color::White);
    person1.setPosition({1000,300});
    person2.setPosition({1300,300});
    person3.setPosition({1600,300});        //set positions
    person4.setPosition({1000,600});
    person5.setPosition({1300,600});
    person6.setPosition({1600,600});
    person7.setPosition({1000,900});
    person8.setPosition({1300,900});
    person9.setPosition({1600,900});
    person1.setString("???");person2.setString("???");person3.setString("???");person4.setString("???");person5.setString("???");person6.setString("???");person7.setString("???");person8.setString("???");person9.setString("???");

    Sprite profilePic1, profilePic2, profilePic3, profilePic4, profilePic5, profilePic6, profilePic7, profilePic8, profilePic9;
    profilePic1.setTexture(TextureManager::GetTexture("1"));profilePic2.setTexture(TextureManager::GetTexture("1"));profilePic3.setTexture(TextureManager::GetTexture("1"));profilePic4.setTexture(TextureManager::GetTexture("1"));profilePic5.setTexture(TextureManager::GetTexture("1"));profilePic6.setTexture(TextureManager::GetTexture("1"));profilePic7.setTexture(TextureManager::GetTexture("1"));profilePic8.setTexture(TextureManager::GetTexture("1"));profilePic9.setTexture(TextureManager::GetTexture("1"));
    profilePic1.setPosition({900,50});
    profilePic2.setPosition({1200,50});
    profilePic3.setPosition({1500,50});
    profilePic4.setPosition({900,350});
    profilePic5.setPosition({1200,350});    //add 9 people sprites
    profilePic6.setPosition({1500,350});
    profilePic7.setPosition({900,650});
    profilePic8.setPosition({1200,650});
    profilePic9.setPosition({1500,650});

    Sprite Title;
    Title.setTexture(TextureManager::GetTexture("Title"));      //add extra sprites
    Title.setPosition({30,80});

    Sprite back;
    back.setTexture(TextureManager::GetTexture("back"));
    back.setPosition({0,0});

    Sprite happy;
    happy.setTexture(TextureManager::GetTexture("happy"));
    happy.setPosition({412.5,600});

    Sprite meta;
    meta.setTexture(TextureManager::GetTexture("meta2"));
    meta.setPosition({50,775});

    Sprite RandomPerson;
    RandomPerson.setTexture(TextureManager::GetTexture("102"));
    RandomPerson.setPosition({612.5,775});

    Text randName;
    randName.setFont(arial);
    randName.setCharacterSize(20);
    randName.setFillColor(Color::White);
    randName.setString("No Name Generated Yet");        //setup random generator sprites
    randName.setPosition({625,1025});

    Sprite saber1;
    saber1.setTexture(TextureManager::GetTexture("saber"));
    saber1.setPosition({135,250});

    Sprite saber2;
    saber2.setTexture(TextureManager::GetTexture("saber"));
    saber2.setPosition({135,350});

    Graph randGraph;
    randGraph.mapMaker();

    while (window.isOpen()){
        Event Event{};
        while (window.pollEvent(Event)){
            switch (Event.type) {
                case Event::Closed:
                    window.close();             //if you hit the x button to close window
                case Event::TextEntered:
                    if(textbox1.inTextbox){
                        textbox1.typedOn(Event);        //if typing in the textboxes run textbox class
                    }
                    if(textbox2.inTextbox){
                        textbox2.typedOn(Event);
                    }
                    break;
                case Event::MouseMoved:
                    if(SearchButton.isMouseOver(window)){
                        SearchButton.setBackColor(Color::White);
                    }
                    else{
                        SearchButton.setBackColor(Color::Green);        //change colors of buttons when hovering over them
                    }
                    if(SearchButton2.isMouseOver(window)){
                        SearchButton2.setBackColor(Color::White);
                    }
                    else{
                        SearchButton2.setBackColor(Color::Green);
                    }
                    if(text1.isMouseOver(window) && !textbox1.inTextbox){
                        text1.setBackColor(Color::White);
                    }
                    else{
                        if(!textbox1.inTextbox){
                            text1.setBackColor(Color::Green);
                        }
                    }
                    if(text2.isMouseOver(window) && !textbox2.inTextbox){
                        text2.setBackColor(Color::White);
                    }
                    else{
                        if(!textbox2.inTextbox){
                            text2.setBackColor(Color::Green);
                        }
                    }
                    if(randNameButton.isMouseOver(window)){
                        randNameButton.setBackColor(Color::White);
                    }
                    else{
                        randNameButton.setBackColor(Color::Green);
                    }
                    if(printConnection.isMouseOver(window)){
                        printConnection.setBackColor(Color::White);
                    }
                    else{
                        printConnection.setBackColor(Color::Green);
                    }

                    break;
                case Event::MouseButtonPressed:
                    if (!text1.isMouseOver(window) && !text2.isMouseOver(window)){
                        textbox1.setSelected(false);
                        textbox2.setSelected(false);
                        textbox1.inTextbox = false;                     //sets textbox typing permission if the user clicks anything but the search boxes
                        textbox2.inTextbox = false;
                        if(textbox1.numCharTyped==0){
                            text1.setBackColor(Color::Green);
                            text1.setTextColor(Color::Black);
                        }
                        if(textbox2.numCharTyped==0){
                            text2.setBackColor(Color::Green);
                            text2.setTextColor(Color::Black);
                        }
                    }
                    if(SearchButton.isMouseOver(window)){
                        if(textbox1.numCharTyped!=0 && textbox2.numCharTyped!=0){       //search names if names are typed
                            bool connectionFound;
                            std::string name1 = textbox1.nameTyped;
                            std::string name2 = textbox2.nameTyped;
                            if(OnOffButton && currentName1==textbox1.nameTyped && currentName2==textbox2.nameTyped){
                                searchText2.setFillColor(Color::Transparent);
                                searchText.setFillColor(Color::Red);
                                searchText.setPosition({50,525});
                                happy.setPosition({412.5,600});
                                happy.setTexture(TextureManager::GetTexture("mad"));
                                searchText.setString("You Have Already Searched These Names With BFS!");            //checks if you try to do the same search twice
                                currentName1=textbox1.nameTyped;
                                currentName2=textbox2.nameTyped;
                                break;
                            }
                            if(OnOffButton && currentName1!=textbox1.nameTyped || currentName2!=textbox2.nameTyped){
                                OnOffButton=false;
                            }
                            std::chrono::time_point<std::chrono::system_clock> start, end;
                            happy.setTexture(TextureManager::GetTexture("happy"));
                            searchText.setFillColor(Color::Green);
                            vector<string> names;
                            names.resize(9);
                            unordered_map<string,int>::const_iterator got = randGraph.stringmap.find(name1);        //finds names searched in map
                            unordered_map<string,int>::const_iterator got2 = randGraph.stringmap.find(name2);
                            if(got==randGraph.stringmap.end() || got2==randGraph.stringmap.end()){
                                searchText2.setFillColor(Color::Transparent);
                                searchText.setPosition({300,525});
                                happy.setTexture(TextureManager::GetTexture("mad"));
                                happy.setPosition({412.5,600});
                                searchText.setFillColor(Color::Red);
                                searchText.setString("Entered Names Not Found!");       //if names not found display this
                                OnOffButton=true;
                                break;
                            }
                            start = std::chrono::system_clock::now();
                            connectionFound = randGraph.bfsBool(got->second,got2->second);      //if found begin timing time to find connection using BFS
                            end = std::chrono::system_clock::now();
                            std::chrono::duration<double> elapsed_seconds = end - start;
                            names = randGraph.BFSSearch(got->second,got2->second,connectionFound);
                            double Etime=elapsed_seconds.count();               //return connection in a vector
                            for(auto & name : names){
                                if(name.empty()){
                                    name="????";        //make all empty spaces in vector ???
                                }
                            }
                            //set all names and sprites based on vector
                            person1.setPosition({950,300});person2.setPosition({1250,300});person3.setPosition({1550,300});person4.setPosition({950,600});person5.setPosition({1250,600});person6.setPosition({1550,600});person7.setPosition({950,900});person8.setPosition({1250,900});person9.setPosition({1550,900});
                            profilePic1.setTexture(TextureManager::GetTexture("1"));profilePic2.setTexture(TextureManager::GetTexture("1"));profilePic3.setTexture(TextureManager::GetTexture("1"));profilePic4.setTexture(TextureManager::GetTexture("1"));profilePic5.setTexture(TextureManager::GetTexture("1"));profilePic6.setTexture(TextureManager::GetTexture("1"));profilePic7.setTexture(TextureManager::GetTexture("1"));profilePic8.setTexture(TextureManager::GetTexture("1"));profilePic9.setTexture(TextureManager::GetTexture("1"));
                            if(names.size()==1){person1.setString(names.at(0));}
                            if(names.size()==2){person1.setString(names.at(0)); person2.setString(names.at(1));}
                            if(names.size()==3){person1.setString(names.at(0)); person2.setString(names.at(1));person3.setString(names.at(2));}
                            if(names.size()==4){person1.setString(names.at(0)); person2.setString(names.at(1));person3.setString(names.at(2));person4.setString(names.at(3));}
                            if(names.size()==5){person1.setString(names.at(0)); person2.setString(names.at(1));person3.setString(names.at(2));person4.setString(names.at(3));person5.setString(names.at(4));}
                            if(names.size()==6){person1.setString(names.at(0)); person2.setString(names.at(1));person3.setString(names.at(2));person4.setString(names.at(3));person5.setString(names.at(4));person6.setString(names.at(5));}
                            if(names.size()==7){person1.setString(names.at(0)); person2.setString(names.at(1));person3.setString(names.at(2));person4.setString(names.at(3));person5.setString(names.at(4));person6.setString(names.at(5));person7.setString(names.at(6));}
                            if(names.size()==8){person1.setString(names.at(0)); person2.setString(names.at(1));person3.setString(names.at(2));person4.setString(names.at(3));person5.setString(names.at(4));person6.setString(names.at(5));person7.setString(names.at(6));person8.setString(names.at(7));}
                            if(names.size()==9){person1.setString(names.at(0)); person2.setString(names.at(1));person3.setString(names.at(2));person4.setString(names.at(3));person5.setString(names.at(4));person6.setString(names.at(5));person7.setString(names.at(6));person8.setString(names.at(7));person9.setString(names.at(8));}
                            string randomString1 = to_string(2 + (rand() % 103));string randomString2 = to_string(2 + (rand() % 103));string randomString3 = to_string(2 + (rand() % 103));string randomString4 = to_string(2 + (rand() % 103));string randomString5 = to_string(2 + (rand() % 103));string randomString6 = to_string(2 + (rand() % 103));string randomString7 = to_string(2 + (rand() % 103));string randomString8 = to_string(2 + (rand() % 103));string randomString9 = to_string(2 + (rand() % 103));
                            profilePic1.setTexture(TextureManager::GetTexture(randomString1));profilePic2.setTexture(TextureManager::GetTexture(randomString2));profilePic3.setTexture(TextureManager::GetTexture(randomString3));profilePic4.setTexture(TextureManager::GetTexture(randomString4));profilePic5.setTexture(TextureManager::GetTexture(randomString5));profilePic6.setTexture(TextureManager::GetTexture(randomString6));profilePic7.setTexture(TextureManager::GetTexture(randomString7));profilePic8.setTexture(TextureManager::GetTexture(randomString8));profilePic9.setTexture(TextureManager::GetTexture(randomString9));
                            happy.setPosition({412.5,650});
                            searchText.setPosition({180,525});
                            if(connectionFound){
                                searchText.setString("Connection Found! It took " + to_string(Etime) + "s"); //change text to show if connection was found
                                searchText2.setPosition({175,575});
                                searchText2.setFillColor(Color::Green);
                                searchText2.setString("to compute the connection using BFS");
                            }
                            else{
                                searchText.setPosition({250,525});
                                searchText.setString("No Connection Was Found."); //if no connection found 
                                searchText2.setPosition({180,575});
                                searchText2.setFillColor(Color::Green);
                                searchText2.setString("Now Displaying People You May Know: ");
                            }
                            OnOffButton=true;
                            currentName1=textbox1.nameTyped;
                            currentName2=textbox2.nameTyped;  //set what the current typed in box text is
                        }
                        else if(textbox1.numCharTyped==0 && textbox2.numCharTyped==0){
                            searchText2.setFillColor(Color::Transparent);
                            happy.setPosition({412.5,600});
                            searchText.setPosition({150,525});
                            searchText.setFillColor(Color::Red);
                            searchText.setString("You didn't type anything in either textbox!\n");      //if both textboxes have nothing typed and you click search
                            happy.setTexture(TextureManager::GetTexture("mad"));
                        }
                        else if(textbox2.numCharTyped==0 && textbox1.numCharTyped!=0){
                            searchText2.setFillColor(Color::Transparent);
                            happy.setPosition({412.5,600});
                            searchText.setPosition({175,525});
                            searchText.setFillColor(Color::Red);
                            searchText.setString("You didn't type anything in textbox 2!\n");       //if you type nothing in textboxt 2 and search
                            happy.setTexture(TextureManager::GetTexture("mad"));
                        }
                        else if(textbox1.numCharTyped==0 && textbox2.numCharTyped!=0){
                            searchText2.setFillColor(Color::Transparent);
                            happy.setPosition({412.5,600});
                            searchText.setPosition({175,525});
                            searchText.setFillColor(Color::Red);
                            searchText.setString("You didn't type anything in textbox 1!\n");   //if you type nothing in textbox1 and search
                            happy.setTexture(TextureManager::GetTexture("mad"));
                        }
                    }
                    if(SearchButton2.isMouseOver(window)){
                        if(textbox1.numCharTyped!=0 && textbox2.numCharTyped!=0){   //search names if names are typed
                            bool connectionFound2;
                            std::string name1 = textbox1.nameTyped;
                            std::string name2 = textbox2.nameTyped;
                            if(OnOffButton2 && currentName3==textbox1.nameTyped && currentName4==textbox2.nameTyped){
                                searchText2.setFillColor(Color::Transparent);
                                searchText.setFillColor(Color::Red);
                                searchText.setPosition({50,525});
                                happy.setPosition({412.5,600});
                                happy.setTexture(TextureManager::GetTexture("mad"));
                                searchText.setString("You Have Already Searched These Names With DFS!");   //checks if you try to do the same search twice
                                currentName3=textbox1.nameTyped;
                                currentName4=textbox2.nameTyped;
                                break;
                            }
                            if(OnOffButton2 && currentName3!=textbox1.nameTyped || currentName4!=textbox2.nameTyped){
                                OnOffButton2=false;
                            }
                            std::chrono::time_point<std::chrono::system_clock> start, end;
                            happy.setTexture(TextureManager::GetTexture("happy"));
                            searchText.setFillColor(Color::Green);
                            vector<string> names;
                            names.resize(9);
                            unordered_map<string,int>::const_iterator got = randGraph.stringmap.find(name1); //finds names searched in map
                            unordered_map<string,int>::const_iterator got2 = randGraph.stringmap.find(name2);
                            if(got==randGraph.stringmap.end() || got2==randGraph.stringmap.end()){
                                searchText2.setFillColor(Color::Transparent);
                                searchText.setPosition({300,525});
                                happy.setTexture(TextureManager::GetTexture("mad"));
                                happy.setPosition({412.5,600});
                                searchText.setFillColor(Color::Red);
                                searchText.setString("Entered Names Not Found!");    //if names not found display this
                                OnOffButton2=true;
                                break;
                            }
                            start = std::chrono::system_clock::now();
                            connectionFound2 = randGraph.dfsBool(got->second,got2->second);     //if found begin timing time to find connection using DFS
                            end = std::chrono::system_clock::now();
                            std::chrono::duration<double> elapsed_seconds = end - start;
                            names = randGraph.DFSSearch(got->second,got2->second,connectionFound2);      //return connection in a vector
                            double Etime=elapsed_seconds.count();
                            for(auto & name : names){
                                if(name.empty()){
                                    name="????";                  //make all empty spaces in vector ???
                                }
                            }
                            //set all names and sprites based on vector
                            person1.setPosition({950,300});person2.setPosition({1250,300});person3.setPosition({1550,300});person4.setPosition({950,600});person5.setPosition({1250,600});person6.setPosition({1550,600});person7.setPosition({950,900});person8.setPosition({1250,900});person9.setPosition({1550,900});
                            profilePic1.setTexture(TextureManager::GetTexture("1"));profilePic2.setTexture(TextureManager::GetTexture("1"));profilePic3.setTexture(TextureManager::GetTexture("1"));profilePic4.setTexture(TextureManager::GetTexture("1"));profilePic5.setTexture(TextureManager::GetTexture("1"));profilePic6.setTexture(TextureManager::GetTexture("1"));profilePic7.setTexture(TextureManager::GetTexture("1"));profilePic8.setTexture(TextureManager::GetTexture("1"));profilePic9.setTexture(TextureManager::GetTexture("1"));
                            if(names.size()==1){person1.setString(names.at(0));}
                            if(names.size()==2){person1.setString(names.at(0)); person2.setString(names.at(1));}
                            if(names.size()==3){person1.setString(names.at(0)); person2.setString(names.at(1));person3.setString(names.at(2));}
                            if(names.size()==4){person1.setString(names.at(0)); person2.setString(names.at(1));person3.setString(names.at(2));person4.setString(names.at(3));}
                            if(names.size()==5){person1.setString(names.at(0)); person2.setString(names.at(1));person3.setString(names.at(2));person4.setString(names.at(3));person5.setString(names.at(4));}
                            if(names.size()==6){person1.setString(names.at(0)); person2.setString(names.at(1));person3.setString(names.at(2));person4.setString(names.at(3));person5.setString(names.at(4));person6.setString(names.at(5));}
                            if(names.size()==7){person1.setString(names.at(0)); person2.setString(names.at(1));person3.setString(names.at(2));person4.setString(names.at(3));person5.setString(names.at(4));person6.setString(names.at(5));person7.setString(names.at(6));}
                            if(names.size()==8){person1.setString(names.at(0)); person2.setString(names.at(1));person3.setString(names.at(2));person4.setString(names.at(3));person5.setString(names.at(4));person6.setString(names.at(5));person7.setString(names.at(6));person8.setString(names.at(7));}
                            if(names.size()==9){person1.setString(names.at(0)); person2.setString(names.at(1));person3.setString(names.at(2));person4.setString(names.at(3));person5.setString(names.at(4));person6.setString(names.at(5));person7.setString(names.at(6));person8.setString(names.at(7));person9.setString(names.at(8));}
                            string randomString1 = to_string(2 + (rand() % 103));string randomString2 = to_string(2 + (rand() % 103));string randomString3 = to_string(2 + (rand() % 103));string randomString4 = to_string(2 + (rand() % 103));string randomString5 = to_string(2 + (rand() % 103));string randomString6 = to_string(2 + (rand() % 103));string randomString7 = to_string(2 + (rand() % 103));string randomString8 = to_string(2 + (rand() % 103));string randomString9 = to_string(2 + (rand() % 103));
                            profilePic1.setTexture(TextureManager::GetTexture(randomString1));profilePic2.setTexture(TextureManager::GetTexture(randomString2));profilePic3.setTexture(TextureManager::GetTexture(randomString3));profilePic4.setTexture(TextureManager::GetTexture(randomString4));profilePic5.setTexture(TextureManager::GetTexture(randomString5));profilePic6.setTexture(TextureManager::GetTexture(randomString6));profilePic7.setTexture(TextureManager::GetTexture(randomString7));profilePic8.setTexture(TextureManager::GetTexture(randomString8));profilePic9.setTexture(TextureManager::GetTexture(randomString9));
                            happy.setPosition({412.5,650});
                            searchText.setPosition({180,525});
                            if(connectionFound2){
                                searchText.setString("Connection Found! It took " + to_string(Etime)+"s");
                                searchText2.setPosition({175,575});
                                searchText2.setFillColor(Color::Green);
                                searchText2.setString("to compute the connection using DFS");  //change text to show if connection was found
                            }
                            else{
                                searchText.setPosition({250,525});
                                searchText.setString("No Connection Was Found.");    //change text to show if no connection was found
                                searchText2.setPosition({180,575});
                                searchText2.setFillColor(Color::Green);
                                searchText2.setString("Now Displaying People You May Know: ");
                            }
                            OnOffButton2=true;
                            currentName3=textbox1.nameTyped;
                            currentName4=textbox2.nameTyped;
                        }
                        else if(textbox1.numCharTyped==0 && textbox2.numCharTyped==0){
                            searchText2.setFillColor(Color::Transparent);
                            happy.setPosition({412.5,600});
                            searchText.setPosition({150,525});
                            searchText.setFillColor(Color::Red);
                            searchText.setString("You didn't type anything in either textbox!\n"); //if nothing was typed in either textbox
                            happy.setTexture(TextureManager::GetTexture("mad"));
                        }
                        else if(textbox2.numCharTyped==0 && textbox1.numCharTyped!=0){
                            searchText2.setFillColor(Color::Transparent);
                            happy.setPosition({412.5,600});
                            searchText.setPosition({175,525});
                            searchText.setFillColor(Color::Red);
                            searchText.setString("You didn't type anything in textbox 2!\n"); //nothing typed in textbox 2
                            happy.setTexture(TextureManager::GetTexture("mad"));
                        }
                        else if(textbox1.numCharTyped==0 && textbox2.numCharTyped!=0){
                            searchText2.setFillColor(Color::Transparent);
                            happy.setPosition({412.5,600});
                            searchText.setPosition({175,525});
                            searchText.setFillColor(Color::Red);
                            searchText.setString("You didn't type anything in textbox 1!\n"); //nothing typed in text box 1
                            happy.setTexture(TextureManager::GetTexture("mad"));
                        }
                    }
                    if(text1.isMouseOver(window)){
                        if(textbox2.inTextbox && textbox2.numCharTyped==0){
                            textbox2.inTextbox = false;
                            text2.setBackColor(Color::Green);
                            text2.setTextColor(Color::Black);
                        }
                        if(textbox2.inTextbox){
                            textbox2.inTextbox = false;
                            text2.setBackColor(Color::Green);               //if nothing is typed and clicked off of search boxes set the text back to original
                        }
                        text1.setBackColor(Color::Red);
                        text1.setTextColor(Color::Transparent);
                        textbox2.setSelected(false);
                        textbox1.setSelected(true);
                        textbox1.inTextbox = true;
                        break;
                    }
                    if(text2.isMouseOver(window)){
                        if(textbox1.inTextbox && textbox1.numCharTyped==0){
                            textbox1.inTextbox = false;
                            text1.setBackColor(Color::Green);
                            text1.setTextColor(Color::Black);
                        }
                        if(textbox1.inTextbox){
                            textbox1.inTextbox = false;                   //if nothing is typed and clicked off of search boxes set the text back to original
                            text1.setBackColor(Color::Green);
                        }
                        text2.setBackColor(Color::Red);
                        text2.setTextColor(Color::Transparent);
                        textbox1.setSelected(false);
                        textbox2.setSelected(true);
                        textbox2.inTextbox = true;
                        break;
                    }
                    if(randNameButton.isMouseOver(window)){
                        string randomRand = to_string(2 + (rand() % 103));
                        int random = 1 + (rand() % 25000);
                        auto got = randGraph.intmap.find(random);
                        RandomPerson.setTexture(TextureManager::GetTexture(randomRand));            //find a random name in map and display sprite/name to search
                        randName.setPosition({600,1025});
                        randName.setString("Random Name: " + got->second);
                    }
                    if(printConnection.isMouseOver(window)){
                        string name1 = textbox1.nameTyped;
                        string name2 = textbox2.nameTyped;                   //takes names and finds them in map
                        auto print = randGraph.stringmap.find(name1);
                        auto print2 = randGraph.stringmap.find(name2);
                        if((textbox1.numCharTyped!=0 || textbox2.numCharTyped!=0) && print!=randGraph.stringmap.end() && print2!=randGraph.stringmap.end()) {
                            vector<int> path;
                            vector<bool> visited;
                            if(!randGraph.dfsBool(print->second,print2->second)){           
                                searchText.setPosition({300,525});
                                searchText.setString("No Connection To Print!");
                                break;
                            }
                            randGraph.DFSPathfinder(print->second,print2->second,visited,path);    //if they exit in the map and valid print the entire connection
                            randGraph.printCompletePath(path);
                        }
                        else{
                            searchText.setPosition({360,525});
                            searchText.setString("Invalid Inputs");   //if nothing is typed in textboxs and tries to print connection
                        }
                    }
            }
        }
        window.clear();
        window.draw(back);
        window.draw(Title);
        window.draw(happy);
        window.draw(meta);
        window.draw(saber1);
        window.draw(saber2);
        window.draw(RandomPerson);
        SearchButton.drawTo(window);
        SearchButton2.drawTo(window);
        randNameButton.drawTo(window);
        printConnection.drawTo(window);
        window.draw(randName);
        window.draw(searchText);
        window.draw(searchText2);
        window.draw(profilePic1);
        window.draw(profilePic2);
        window.draw(profilePic3);
        window.draw(profilePic4);
        window.draw(profilePic5);
        window.draw(profilePic6); //draw all sprites and text to window
        window.draw(profilePic7);
        window.draw(profilePic8);
        window.draw(profilePic9);
        window.draw(person1);
        window.draw(person2);
        window.draw(person3);
        window.draw(person4);
        window.draw(person5);
        window.draw(person6);
        window.draw(person7);
        window.draw(person8);
        window.draw(person9);
        text1.drawTo(window);
        text2.drawTo(window);
        textbox1.drawTo(window);
        textbox2.drawTo(window);
        window.display();
    }
    return 0;
}
