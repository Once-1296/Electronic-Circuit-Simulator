#include "resources.h"

resources::resources()
{

    fstream file("temp.txt", ios::app);
    cout << "Enter no of resistors (positive) in parallel:\t";
    do
    {
        cin >> no;
    } while (no <= 0);
    for (int i = 0; i < no; i++)
    {
        if (i < no - 1)
        {
            cout << "Enter resistance for resistor(p) " << i + 1 << "\t";
            cin >> temp;
            file << temp << ",";
            resinpar.push_back(temp);
        }
        if (i == no - 1)
        {
            cout << "Enter resistance for resistor(p) " << i + 1 << "\t";
            cin >> temp;
            file << temp << endl;
            resinpar.push_back(temp);
            file.close();
        }
    }
    cout << "Net resistance of given resistors in parallel is:" << endl;
    cout << calcnetres(no) << endl;
}

float resources::calcnetres(int count)
{
    float sum = 0;
    for (int i = 0; i < count; i++)
    {
        sum += reci(resinpar[i]);
    }
    return (reci(sum));
}

float reci(float n)
{
    return (1 / n);
}

void Nodes::initWindow()
{
    this->videoMode.height = 600;
    this->videoMode.width = 800;
    this->window = new sf::RenderWindow(this->videoMode, "circuits project", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

void Nodes::initText()
{
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(15);
    this->uiText.setFillColor(sf::Color::Blue);
    this->uiText.setString("NONE");
}

void Nodes::initNodes(int n,int m)
{
    int tmp = 2 * n + 1;
    int tmp1 = 2 * m + 1;
    this->node.setSize(sf::Vector2f(this->videoMode.width / (4.0f * static_cast<float> (this->columnnum)), this->videoMode.height / (4.0f * static_cast<float> (this->recnum[n-1]+2))));
    this->node.setPosition((this->videoMode.width*static_cast<float>(tmp) )/ (2.0f*static_cast<float> (this->columnnum))-(this->node.getSize().x*0.5f),
                            ((this->videoMode.height * static_cast<float>(tmp1)) / (2.0f * static_cast<float> (this->recnum[n-1]+2)) )- (this->node.getSize().y*0.5f));
    this->node.setFillColor(sf::Color::Cyan);
    if (m == 1&&m!=recnum[n-1])
    {
        this->thread.setSize(sf::Vector2f((this->videoMode.width * 3.0f) / (4.0f * static_cast<float> (this->columnnum)),
            3));
        this->thread.setPosition(sf::Vector2f(this->node.getPosition().x - this->node.getSize().x,
            this->node.getPosition().y + (this->node.getSize().y * 0.5f)));
        this->threads.push_back(this->thread);
        this->thread1.setSize(sf::Vector2f(3,(this->videoMode.height) / ( static_cast<float> (this->recnum[n-1]+2))));
        this->thread1.setPosition(sf::Vector2f(this->node.getPosition().x - this->node.getSize().x,
            this->node.getPosition().y + (this->node.getSize().y * 0.5f)));
        this->threads.push_back(this->thread1);
        this->thread2.setSize(sf::Vector2f(3, (this->videoMode.height) / (static_cast<float> (this->recnum[n - 1] + 2))));
        this->thread2.setPosition(sf::Vector2f(this->node.getPosition().x +(this->node.getSize().x*2.0f),
            this->node.getPosition().y + (this->node.getSize().y * 0.5f)));
        this->threads.push_back(this->thread2);

    }
    else if (m == recnum[n - 1])
    {
        this->thread.setSize(sf::Vector2f((this->videoMode.width * 3.0f) / (4.0f * static_cast<float> (this->columnnum)),
            3));
        this->thread.setPosition(sf::Vector2f(this->node.getPosition().x - this->node.getSize().x,
            this->node.getPosition().y + (this->node.getSize().y * 0.5f)));
        this->threads.push_back(this->thread);
    }
    else
    {
        this->thread.setSize(sf::Vector2f((this->videoMode.width * 3.0f) / (4.0f * static_cast<float> (this->columnnum)),
            3));
        this->thread.setPosition(sf::Vector2f(this->node.getPosition().x - this->node.getSize().x,
            this->node.getPosition().y + (this->node.getSize().y * 0.5f)));
        this->threads.push_back(this->thread);
        this->thread1.setSize(sf::Vector2f(3, (this->videoMode.height) / (static_cast<float> (this->recnum[n - 1] + 2))));
        this->thread1.setPosition(sf::Vector2f(this->node.getPosition().x - this->node.getSize().x,
            this->node.getPosition().y + (this->node.getSize().y * 0.5f)));
        this->threads.push_back(this->thread1);
        this->thread2.setSize(sf::Vector2f(3, (this->videoMode.height) / (static_cast<float> (this->recnum[n - 1] + 2))));
        this->thread2.setPosition(sf::Vector2f(this->node.getPosition().x + (this->node.getSize().x * 2.0f),
            this->node.getPosition().y + (this->node.getSize().y * 0.5f)));
        this->threads.push_back(this->thread2);
    }
   this->balls.push_back(this->node);

}

void Nodes::initColumns(int n)
{
    this->node.setSize(sf::Vector2f((this->videoMode.width * 1.0f) / static_cast<float>(this->columnnum),static_cast<float> (this->videoMode.height)*(1.0f - ((2.0f)/(this->max_row_num * 1.0f)))));
    this->node.setPosition(sf::Vector2f((this->videoMode.width * 1.0f * static_cast<float>(n)) / static_cast<float> (this->columnnum),( this->videoMode.height*1.0f)/static_cast <float>(this->max_row_num)));
    this->node.setFillColor(sf::Color::Black);
    this->node.setOutlineColor(sf::Color::Green);
    this->node.setOutlineThickness(2.0f);
    this->columns.push_back(node);
}

void Nodes::initVariables()
{
    this->max_row_num = 0;
    ifstream file("temp.txt");
    string word, line;
    getline(file, line);
    this->columnnum = stoi(line);
    int con2;
    for (int i = 0; i < this->columnnum; i++)
    {
        con2 = 0;
        getline(file, line);
        stringstream obj2(line);
        while (getline(obj2, word, ','))
        {
            con2++;
        }
        this->recnum.push_back(con2);
    }
    this->columnnum+=2;
    for (int i = 0; i < this->recnum.size(); i++)
    {
        if (this->max_row_num < this->recnum[i]) 
        {
            this->max_row_num = this->recnum[i];
        }
    }
    this->max_row_num += 2;
}

void Nodes::initThreads(int n)
{
    this->thread.setSize(sf::Vector2f(this->videoMode.width / static_cast<float>((this->columnnum) * 8.0f), 3));
    this->thread.setPosition(sf::Vector2f(((this->videoMode.width)*4.0f*n) / static_cast<float>((this->columnnum) * 4.0f), this->videoMode.height / 2.0f));
    this->threads.push_back(this->thread);
    this->thread1.setSize(sf::Vector2f(this->videoMode.width / static_cast<float>((this->columnnum) * 8.0f), 3));
    this->thread1.setPosition(sf::Vector2f((((this->videoMode.width) * 4.0f * (n+1)) / static_cast<float>((this->columnnum) * 4.0f))-this->thread1.getSize().x, this->videoMode.height / 2.0f));
    this->threads.push_back(this->thread1);
}

void Nodes::initFinalthreads()
{
    this->thread.setSize(sf::Vector2f((this->videoMode.width * 1.0f) / (2.0f*static_cast<float>(this->columnnum)), 3.0f));
    this->thread.setPosition(sf::Vector2f((this->videoMode.width * 1.0f) / (2.0f * static_cast<float>(this->columnnum)),(this->videoMode.height * 1.0f) / 2.0f));
    this->finthreads.push_back(this->thread);
    this->thread.setPosition(sf::Vector2f((this->videoMode.width * 1.0f) * (1.0f-((1.0f)/static_cast<float>(this->columnnum)))
        ,(this->videoMode.height * 1.0f) / 2.0f));
    this->finthreads.push_back(this->thread);
    this->thread.setPosition(sf::Vector2f((this->videoMode.width * 1.0f) * (1.0f - ((1.0f) /(2.0f * static_cast<float>(this->columnnum)))), (this->videoMode.height * 1.0f) / 2.0f));
    this->thread.setSize(sf::Vector2f(3.0f,((this->videoMode.height * 1.0f)*((1.0f/2.0f)-(1.0f/(2.0f * static_cast<float>(this->max_row_num)))))));
    this->finthreads.push_back(this->thread);
    this->thread.setPosition(sf::Vector2f((this->videoMode.width * 1.0f) / (2.0f * static_cast<float>(this->columnnum)), (this->videoMode.height * 1.0f) / 2.0f));
    this->finthreads.push_back(this->thread);
    this->thread.setPosition(sf::Vector2f((1.0f * this->videoMode.width)/(2.0f * static_cast<float>(this->columnnum)),(this->videoMode.height * 1.0f)*(1.0f-(1.0f/(2.0f*static_cast<float>(this->max_row_num))))));
    this->thread.setSize(sf::Vector2f((this->videoMode.width * 1.0f) * ((1.0f/2.0f)-(1.0f / static_cast<float>(this->columnnum))), 3.0f));
    this->finthreads.push_back(this->thread);
    this->thread.setPosition(sf::Vector2f((1.0f * this->videoMode.width/2.0f) * (1.0f + (1.0f / static_cast<float>(this->columnnum))), (this->videoMode.height * 1.0f) * (1.0f - (1.0f / (2.0f * static_cast<float>(this->max_row_num))))));
    this->finthreads.push_back(this->thread);
}

void Nodes::initFonts()
{
        if (!this->font.loadFromFile("fonts/Raleway-Bold.ttf"))
        {
            std::cout << "ERROR:GAME::::INITFONTS::Failed to load font" << "\n";
        }
}
void Nodes::initVect(vector<string> vect1, vector<string> vect2, vector<string> vect3, vector<string> vect4,
    vector<string>vect5, vector<string>vect6, vector<string>vect7, vector<string>vect8)
{
    for (auto& e : vect1)
    {
        this->rlis.push_back(e);
    }    
    for (auto& e : vect2)
    {
        this->clis.push_back(e);
    }    
    for (auto& e : vect3)
    {
        this->vlis.push_back(e);
    }    
    for (auto& e : vect4)
    {
        this->plis.push_back(e);
    }   
    for (auto& e : vect5)
    {
        this->srlis.push_back(e);
    }
    for (auto& e : vect6)
    {
        this->sclis.push_back(e);
    }
    for (auto& e : vect7)
    {
        this->svlis.push_back(e);
    }
    for (auto& e : vect8)
    {
        this->splis.push_back(e);
    }
}

Nodes::Nodes(vector<string> vect1, vector<string> vect2, vector<string> vect3, vector<string> vect4
    , float netres, float netcurr, float netvol, float netpow,
    vector<string>vect5, vector<string>vect6, vector<string>vect7, vector<string>vect8)
{
    this->nres = netres;
    this->ncurr = netcurr;
    this->nvol = netvol;
    this->npow = netpow;
    this->initWindow();
    this->initVariables();
    this->initVect(vect1, vect2, vect3, vect4,vect5,vect6,vect7,vect8);
    this->initFonts();
    this->initText();
    this->drawballs();

}

Nodes::~Nodes()
{
    delete this->window;
}
//Accessors
const bool Nodes::running() const
{
    return this->window->isOpen();
}

void Nodes::pollEvents()
{
    //Event polling
    while (this->window->pollEvent(this->eevee))
    {
        switch (this->eevee.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->eevee.key.code == sf::Keyboard::Escape)
            {
                this->window->close();
                break;
            }
        }
    }
}

void Nodes::update()
{
    this->pollEvents();
    this->updateMousePositions();
    this->updatenodes();
}

void Nodes::updateText(int n,bool b,bool c)
{
    std::stringstream ss;
    if (b&&c) 
    {
        ss  << "Resistor "<<n+1<<" details: "<<"\n"
            <<"Resistance: " << this->rlis[n] << "\n"
            << "Current through resistance: " << this->clis[n] << "\n"
            << "Potential drop at resistance: " << this->vlis[n] << "\n"
            << "Power consumed by resistance: " << this->plis[n] << "\n";
        this->uiText.setString(ss.str());
    }
    else if(!(b||c))
    {
        ss << "Net Resistance: " << this->nres<< "\n"
            << "Net current: " << this->ncurr << "\n"
            << "Net Potential difference: " << this->nvol << "\n"
            << "Net Power consumed: " << this->npow << "\n";
        this->uiText.setString(ss.str());
    }
    else
    {
        ss << "Series group " << n + 1 << " details: " << "\n"
            << "Resistance: " << this->srlis[n] << "\n"
            << "Current through resistance: " << this->sclis[n] << "\n"
            << "Potential drop at resistance: " << this->svlis[n] << "\n"
            << "Power consumed by resistance: " << this->splis[n] << "\n";
        this->uiText.setString(ss.str());
    }

}

void Nodes::updatenodes()
{
    bool bb= false,cc=false;
    //Check if clicked on
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (this->mouseHeld == false)
        {
            this->mouseHeld = true;
            for (int i = 0; i < this->balls.size(); i++)
            {
                if (this->balls[i].getGlobalBounds().contains(this->mousePosView))
                {
                    bb = true;
                    this->updateText(i, true,true);
                }
            }
            for (int i = 0; i < this->columns.size(); i++)
            {
                if (this->columns[i].getGlobalBounds().contains(this->mousePosView) && !(bb))
                {
                    cc = true;
                    this->updateText(i, true, false);
                }
            }
            if (!(bb||cc)) 
            {
                this->updateText(2, false,false);
            }
        }
    }
    else
    {
        this->mouseHeld = false;
    }
}

void Nodes::updateMousePositions()
{
    /*return void
Updates the mouse position:
Mouse pos relative to window(vector2i)*/
    this->MousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->MousePosWindow);
}

void Nodes::rendernodes(sf::RenderTarget & target)
{
    for (auto& e : this->columns)
    {
        target.draw(e);
    }
    for (auto& e : this->threads)
    {
        target.draw(e);
    }
    for (auto& e : this->balls)
    {
        target.draw(e);
    }
    for (auto& e : this->finthreads)
    {
        target.draw(e);
    }

}

void Nodes::renderText(sf::RenderTarget& target)
{
    target.draw(this->uiText);
}

void Nodes::render()
{
    /*
    * return void
     -clear old frame
     -render objects
     -display the new window

    renders the file objects

    */
    //color(r,g,b,transparency(alpha))
    this->window->clear(sf::Color());
    this->rendernodes(*this->window);
    this->renderText(*this->window);
    this->window->display();
}

void Nodes::drawballs()
{
    for (int i = 0; i < this->columnnum-2; i++)
    {
        for (int j = 0; j <this->recnum[i]; j++)
        {
            this->initNodes(i + 1,j + 1);
        }
        
    }
    for (int i = 0; i < this->columnnum-2; i++)
    {
        this->initThreads(i + 1);
    }
    for (int i = 0; i < this->columnnum - 2; i++)
    {
        this->initColumns(i + 1);
    }
    this->initFinalthreads();
}

