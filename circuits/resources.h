#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/System.hpp>
#include<SFML/Network.hpp>
using namespace std;
float reci(float n);
class resources
{
public:
    int no;
    float temp;
    resources();
    vector<float> resinpar;
    float calcnetres(int count);
};
class Data2
{
public:
    vector<float> resinpar2;
};
class Data3
{
public:
    vector<float> current23;
};
class Data4
{
public:
    vector<float> pds12;
};
class Data5
{
public:
    vector<float> power1234;
};
class Nodes
{
private:
    //variables
    int columnnum;
    float nres, ncurr, nvol, npow;
    std::vector<int>recnum;
    int max_row_num;
    std::vector<string>rlis;
    std::vector<string>clis;
    std::vector<string>vlis;
    std::vector<string>plis;
    std::vector<string>srlis;
    std::vector<string>sclis;
    std::vector<string>svlis;
    std::vector<string>splis;
    sf::RectangleShape node;
    std::vector<sf::RectangleShape>balls;
    std::vector<sf::RectangleShape>columns;
    sf::RectangleShape thread;
    sf::RectangleShape thread1;
    sf::RectangleShape thread2;
    std::vector<sf::RectangleShape>threads;
    std::vector<sf::RectangleShape>finthreads;
    sf::RectangleShape line;
    std::vector<sf::RectangleShape> lines;
    bool mouseHeld;
    //resources
    sf::Font font;
    //Text
    sf::Text uiText;
    //Mouse position
    sf::Vector2i MousePosWindow;
    sf::Vector2f mousePosView;
    //window
    sf::RenderWindow* window;
    sf::Event eevee;
    sf::VideoMode videoMode;
    //Private functions
    void initWindow();
    void initText();
    void initNodes(int n,int m);
    void initColumns(int n);
    void initVariables();
    void initThreads(int n);
    void initFinalthreads();
    void initFonts();
    void initVect(vector<string>vect1, vector<string>vect2, vector<string>vect3, vector<string>vect4,
        vector<string>vect5, vector<string>vect6, vector<string>vect7, vector<string>vect8);
public:
    Nodes(vector<string> vect1, vector<string> vect2, vector<string> vect3, vector<string> vect4
        , float netres, float netcurr, float netvol, float netpow,
        vector<string>vect5, vector<string>vect6, vector<string>vect7, vector<string>vect8);//Constructor
    virtual ~Nodes();//Destructor
    //Accessors
    const bool running() const;
    //Functions
    void pollEvents();
    void update();
    void updateText(int n,bool b,bool c);
    void updatenodes();
    void updateMousePositions();
    void rendernodes(sf::RenderTarget& target);
    void renderText(sf::RenderTarget& target);
    void render();
    void drawballs();


};
class columns {
public:
    vector<sf::CircleShape>balls;
};