#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <random>
//Global Deðiþkenler

sf::Font font("C:/Windows/Fonts/Tahoma.ttf");
sf::Font addbfont("C:/Windows/Fonts/Candara.ttf");
float c1size = 40.0f;
float c2size = 20.0f;
float c3size = 10.0f;
sf::Color circlecolor = sf::Color::Black;
int circlesize;
float circlespeed = 2.f;
float circlemaxspeed = 18.f;
bool gameIsStarted = false;
bool gameIsStopped = false;
bool rbactive = false;
bool ybactive = false;
bool gbactive = false;
bool c1bactive = false;
bool c2bactive = false;
bool c3bactive = false;
bool paused = false;
bool lastframe = false;
bool isMousePressed = false;

//circle lar için struct

struct Circle {
    bool generated;
    float x;
    float y;
    float xspeed;
    float yspeed;
    sf::Color color;
    float size;
};
//Oluþturulan circle larýn saklanmasý için vektör
std::vector<Circle>circles;

//Rastgele koordinat oluþturmak için fonksiyonlar

int GenerateRandomX() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> xDist(0, 999 - 80.f);

    int x = xDist(rng);
    return x;
}
int GenerateRandomY() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> yDist(0, 799 - 80.0f);
    int x = yDist(rng);
    return x;
}

//Dairelerin farklý yönlerde gitmemesi için - ve ya + 1 üretme.

int GenerateRandomSign() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<>dist(0, 1);
    int sign = dist(gen) == 0 ? 1 : -1;
    return sign;
}
//circle struct

bool isNegative(int n) {
    bool negative = n >= 0;
    if (negative == false) {
        return true;
    }
    else {
        return false;
    }
}

//Daire oluþturma fonksiyonu

void GenerateCircle() {
    Circle circle;
    bool generated = false;
    float x = GenerateRandomX();
    float y = GenerateRandomY();
    float xspeed = circlespeed * GenerateRandomSign();
    float yspeed = circlespeed * GenerateRandomSign();
    sf::Color color = circlecolor;
    float size = circlesize;
    circle.x = x;
    circle.y = y;
    circle.xspeed = xspeed;
    circle.yspeed = yspeed;
    circle.color = circlecolor;
    circle.size = circlesize;
    circles.push_back(circle);
}

//Test için debug fonksiyonu:
void DebugLog(const std::string& message) {
    std::cout << "[DEBUG] " << message << std::endl;
}

int main()
{
    //BUTTON' LAR
        
    //Add button
    float addbx = 410.f;
    float addby = 820.f;
    float addbx1 = 200.f;
    float addby1 = 80.f;
    sf::Text addtext(addbfont, "ADD CIRCLE", 30);
    addtext.setPosition({ addbx + 21, addby + 16 });
    addtext.setFillColor(sf::Color::Black);
    addtext.setOutlineThickness(1.f);
    sf::RectangleShape addButton({addbx1, addby1});
    addButton.setPosition({ addbx, addby });
    addButton.setFillColor(sf::Color::Blue);
    addButton.setOutlineColor(sf::Color::Black);
    addButton.setOutlineThickness(7.f);
        
    //Kýrmýzý renk button 
    float colorbuttonsize = 70.f;

    float redbx = 40.f;
    float redby = 830.f;
    sf::RectangleShape redButton({ colorbuttonsize, colorbuttonsize });
    redButton.setPosition({ redbx, redby });
    redButton.setFillColor(sf::Color::Red);
    redButton.setOutlineColor(sf::Color::Black);
    redButton.setOutlineThickness(3.f);

    //Yeþil renk button

    float greenbx = 160.f;
    float greenby = 830.f;
    sf::RectangleShape greenButton({ colorbuttonsize, colorbuttonsize });
    greenButton.setPosition({ greenbx, greenby });
    greenButton.setFillColor(sf::Color::Green);
    greenButton.setOutlineColor(sf::Color::Black);
    greenButton.setOutlineThickness(3.f);

    //Sarý renk button

    float yellowbx = 280.f;
    float yellowby = 830.f;
    sf::RectangleShape yellowButton({ colorbuttonsize, colorbuttonsize });
    yellowButton.setPosition({ yellowbx, yellowby });
    yellowButton.setFillColor(sf::Color::Yellow);
    yellowButton.setOutlineColor(sf::Color::Black);
    yellowButton.setOutlineThickness(3.f);

    //Boyut button'larý
    
    //En büyük daire
    float c1bx = 660.f;
    float c1by = 830.f;
    sf::CircleShape c1Button(c1size, 60);
    c1Button.setPosition({ c1bx, c1by });
    c1Button.setFillColor(sf::Color(169, 169, 169));
    c1Button.setOutlineColor(sf::Color::Black);
    c1Button.setOutlineThickness(3.f);

    //Orta boyut daire
    float c2bx = 810.f;
    float c2by = 850.f;
    sf::CircleShape c2Button(c2size, 60);
    c2Button.setPosition({ c2bx, c2by });
    c2Button.setFillColor(sf::Color(169, 169, 169));
    c2Button.setOutlineColor(sf::Color::Black);
    c2Button.setOutlineThickness(3.f);

    //En küçük daire
    float c3bx = 920.f;
    float c3by = 860.f;
    sf::CircleShape c3Button(c3size, 60);
    c3Button.setPosition({ c3bx, c3by });
    c3Button.setFillColor(sf::Color(169, 169, 169));
    c3Button.setOutlineColor(sf::Color::Black);
    c3Button.setOutlineThickness(3.f);

    //Ayar button'larý

    //Start button
    float startbx = 220.f;
    float startby = 940.f;
    sf::Text starttext(font, "START", 25);
    starttext.setPosition({ startbx + 13, startby });
    starttext.setFillColor(sf::Color::Black);
    sf::RectangleShape startButton({ 100.f, 40.f });
    startButton.setPosition({ startbx, startby });
    startButton.setFillColor(sf::Color(192, 192, 192));
    startButton.setOutlineColor(sf::Color::Black);
    startButton.setOutlineThickness(1.f);

    //Stop button
    float stopbx = 380.f;
    float stopby = 940.f;
    sf::Text stoptext(font, "STOP", 25);
    stoptext.setPosition({ stopbx + 20, stopby });
    stoptext.setFillColor(sf::Color::Black);
    sf::RectangleShape stopButton({ 100.f, 40.f });
    stopButton.setPosition({ stopbx, stopby});
    stopButton.setFillColor(sf::Color(192, 192, 192));
    stopButton.setOutlineColor(sf::Color::Black);
    stopButton.setOutlineThickness(1.f);

    //Reset button
    float resetbx = 540.f;
    float resetby = 940.f;
    sf::Text resettext(font, "RESET", 25);
    resettext.setPosition({ resetbx + 13, resetby });
    resettext.setFillColor(sf::Color::Black);
    sf::RectangleShape resetButton({ 100.f, 40.f });
    resetButton.setPosition({ resetbx, resetby });
    resetButton.setFillColor(sf::Color(192, 192, 192));
    resetButton.setOutlineColor(sf::Color::Black);
    resetButton.setOutlineThickness(1.f);

    //Speed up button
    float speedupbx = 700.f;
    float speedupby = 940.f;
    sf::Text speeduptext(font, "Speed Up", 25);
    speeduptext.setPosition({ speedupbx + 13, speedupby });
    speeduptext.setFillColor(sf::Color::Black);
    sf::RectangleShape speedUpButton({ 130.f, 40.f });
    speedUpButton.setPosition({ speedupbx, speedupby });
    speedUpButton.setFillColor(sf::Color(192, 192, 192));
    speedUpButton.setOutlineColor(sf::Color::Black);
    speedUpButton.setOutlineThickness(1.f);

    //Ekraný çizdirme

    sf::ContextSettings settings;
    settings.antiAliasingLevel = 4;
    sf::RenderWindow window(sf::VideoMode({ 1000, 1000 }), "Game", sf::Style::Titlebar
     | sf::Style::Close); // Style kullanýlarak ekranýn boyutlandýrýlmasý engellendi
    window.setFramerateLimit(60);
    //GUI

    sf::RectangleShape gui({1000.f, 200.f});
    gui.setPosition({ 0.0f, 800.0f });
    gui.setFillColor(sf::Color(105, 105, 105));

    //Ana döngü
    while (window.isOpen())
    {
        window.clear(sf::Color::Black);
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Mouse pozisyonu

        auto mousePos = sf::Vector2f(sf::Mouse::getPosition(window));

        //Mouse basýlma kontrolü
        bool onMousePress = false;
        bool onMouseRelease = false;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            if (!isMousePressed)
                onMousePress = true; 
            isMousePressed = true;
        }
        else {
            if (isMousePressed) 
                onMouseRelease = true;
            isMousePressed = false;
        }
        //Add Button ý için mouse input u

        if(addButton.getGlobalBounds().contains(mousePos)){
            //Sol mouse a basýlýrsa rengi beyaz yap 
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                addButton.setFillColor(sf::Color(150, 150, 150));
            }
            else if(onMouseRelease){
                addButton.setFillColor(sf::Color::White);
                if (circlecolor == sf::Color::Black) {
                    DebugLog("Color is not selected.");
                }
                else if (circlesize == 0) {
                    DebugLog("Size is not selected.");

                }
                else {
                    GenerateCircle(); 
                    DebugLog("Circle is generated");        
                }
            }
            else {
                addButton.setFillColor(sf::Color::Blue);
            }
        }
        else {
            addButton.setFillColor(sf::Color::Blue);
        }

        //Yeþil button için mouse input u 
        if (greenButton.getGlobalBounds().contains(mousePos)) {
            //Sol mouse a basýlýrsa outline ý beyaz yap ve 
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                greenButton.setOutlineColor(sf::Color::White);
                gbactive = true;
                rbactive = false;
                ybactive = false;
            }
            if (onMouseRelease) {
                DebugLog("Green color selected");
            }
        }
        if (gbactive == false) {
            greenButton.setOutlineColor(sf::Color::Black);  
        }

        //Kýrmýzý button için mouse input u
        if (redButton.getGlobalBounds().contains(mousePos)) {
            //Sol mouse a basýlýrsa outline ý beyaz yap ve 
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                redButton.setOutlineColor(sf::Color::White);
                gbactive = false;
                rbactive = true;
                ybactive = false;
            }
            if (onMouseRelease) {
                DebugLog("Red color selected");
            }
        }
        if (rbactive == false) {
            redButton.setOutlineColor(sf::Color::Black);
        }

        //Sarý button için mouse input u
        if (yellowButton.getGlobalBounds().contains(mousePos)) {
            //Sol mouse a basýlýrsa outline ý beyaz yap ve 
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                yellowButton.setOutlineColor(sf::Color::White);
                gbactive = false;
                rbactive = false;
                ybactive = true;
            }
            if (onMouseRelease) {
                DebugLog("Yellow color selected");                
            }
        }
        if (ybactive == false) {
            yellowButton.setOutlineColor(sf::Color::Black);
        }

        //Renk düðmelerinin aktif olma durumlarýna göre oluþturulacak dairelerin deðerini 
        // deðiþtir.
        if (gbactive) {
            circlecolor = sf::Color::Green;
        }
        if (rbactive) {
            circlecolor = sf::Color::Red;
        }
        if (ybactive) {
            circlecolor = sf::Color::Yellow;
        }

        //Büyük daire button ý için mouse input u
        if (c1Button.getGlobalBounds().contains(mousePos)) {
            //Sol mouse a basýlýrsa outline ý beyaz yap ve 
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                c1Button.setOutlineColor(sf::Color::White);
                c1bactive = true;
                c2bactive = false;
                c3bactive = false;
            }
            if (onMouseRelease) {
                DebugLog("Big circle selected");
            }
        }
        if (c1bactive == false) {
            c1Button.setOutlineColor(sf::Color::Black);
        }

        //Orta boyut daire button ý için mouse input u
        if (c2Button.getGlobalBounds().contains(mousePos)) {
            //Sol mouse a basýlýrsa outline ý beyaz yap ve 
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                c2Button.setOutlineColor(sf::Color::White);
                c1bactive = false;
                c2bactive = true;
                c3bactive = false;
            }
            if (onMouseRelease) {
                DebugLog("Medium circle selected");
            }
        }
        if (c2bactive == false) {
            c2Button.setOutlineColor(sf::Color::Black);
        }

        //Küçük daire button ý için mouse input u

        if (c3Button.getGlobalBounds().contains(mousePos)) {
            //Sol mouse a basýlýrsa outline ý beyaz yap ve 
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                c3Button.setOutlineColor(sf::Color::White);
                c1bactive = false;
                c2bactive = false;
                c3bactive = true;
            }
            if (onMouseRelease) {
                DebugLog("Small circle selected");
            }
        }
        if (c3bactive == false) {
            c3Button.setOutlineColor(sf::Color::Black);
        }

        //Start button ý için mouse input u

        if (startButton.getGlobalBounds().contains(mousePos)) {
            if (onMouseRelease) {
                gameIsStarted = true;
                gameIsStopped = false;
                paused = false;
                DebugLog("Game is started");
            }
        }

        //Stop button ý için mouse input u
        bool stopPressed = false;

        if (stopButton.getGlobalBounds().contains(mousePos)) {
            if (onMouseRelease) {
                gameIsStarted = false;
                gameIsStopped = true;
                paused = true;
                DebugLog("Game is stopped");
            }
        }

        if (stopPressed && !lastframe) {
            paused = !paused;
        }

        //Oyunun baþlamasýna göre dairelerin hareket etmesi
        if (gameIsStarted && !paused) {
            for (auto& circle : circles) {
                float& x = circle.x;
                float& y = circle.y;
                float& xspeed = circle.xspeed;
                float& yspeed = circle.yspeed;
                float size = circle.size;
                if (xspeed == 0 && yspeed == 0) {
                    xspeed = circlespeed;
                    yspeed = circlespeed;
                }
                x += xspeed;
                y += yspeed;

                //Daire boyutuna göre ekrandan sekme kontrolü
                if (size == c1size) {
                    if (x >= 1000 - (c1size * 2)) {
                        xspeed = -xspeed;
                    }
                    if (x <= 0) {
                        xspeed = -xspeed;
                    }
                    if (y >= 800 - (c1size * 2)) {
                        yspeed = -yspeed;
                    }
                    if (y <= 0) {
                        yspeed = -yspeed;
                    }
                }
                if (size == c2size) {
                    if (x >= 1000 - (c2size * 2)) {
                        xspeed = -xspeed;
                    }
                    if (x <= 0) {
                        xspeed = -xspeed;
                    }
                    if (y >= 800 - (c2size * 2)) {
                        yspeed = -yspeed;
                    }
                    if (y <= 0) {
                        yspeed = -yspeed;
                    }
                }
                if (size == c3size) {
                    if (x >= 1000 - (c3size * 2)) {
                        xspeed = -xspeed;
                    }
                    if (x <= 0) {
                        xspeed = -xspeed;
                    }
                    if (y >= 800 - (c3size * 2)) {
                        yspeed = -yspeed;
                    }
                    if (y <= 0) {
                        yspeed = -yspeed;
                    }
                }
            }
        }
        //Oyunun durdurulmasý
        if (gameIsStopped) {
            paused = true;
        }

        //Reset button ý için mouse input u 
        if (resetButton.getGlobalBounds().contains(mousePos)) {
            if (onMouseRelease) {
                if (circles.empty() == true) {
                    DebugLog("Screen is empty");
                }
                else {
                    circles.clear();
                    DebugLog("Circles are cleared");
                }
            }
        }

        //Speed up button ý için mouse input u
        if (speedUpButton.getGlobalBounds().contains(mousePos)) {
            if (onMouseRelease) {
                for (auto& circle : circles) {
                    float& xspeed = circle.xspeed;
                    float& yspeed = circle.yspeed;
                    //xspeed ve yspeed için sýnýr kontrolü
                    //xspeed in negatif olma durumu
                    if (isNegative(xspeed)) {
                        xspeed += -circlespeed;
                        if (xspeed <= -circlemaxspeed) {
                            xspeed = -circlemaxspeed;
                        }
                    }
                    else {
                        xspeed += circlespeed;
                        if (xspeed >= circlemaxspeed) {
                            xspeed = circlemaxspeed;
                        }
                    }
                    //yspeed in negatif olma durumu
                    if (isNegative(yspeed)) {
                        yspeed += -circlespeed;
                        if (yspeed <= -circlemaxspeed) {
                            yspeed = -circlemaxspeed;
                        }
                    }
                    else {
                        yspeed += circlespeed;
                        if (yspeed >= circlemaxspeed) {
                            yspeed = circlemaxspeed;
                        }
                    }
                }
                DebugLog("Speed up");
            }
        }
        //Boyut düðmelerinin aktifliðine göre oluþturulacak dairelerin deðerlerini deðiþtir.
        if (c1bactive) {
            circlesize = c1size;
        }
        if (c2bactive) {
            circlesize = c2size;
        }
        if (c3bactive) {
            circlesize = c3size;
        }

        //GUI ve button' larýn çizdirilmesi
        window.draw(gui);
        window.draw(redButton);
        window.draw(greenButton);
        window.draw(yellowButton);
        window.draw(addButton);
        window.draw(addtext);
        window.draw(c1Button);
        window.draw(c2Button);
        window.draw(c3Button);
        window.draw(startButton);
        window.draw(starttext);
        window.draw(stopButton);
        window.draw(stoptext);
        window.draw(resetButton);
        window.draw(resettext);
        window.draw(speedUpButton);
        window.draw(speeduptext);

        //Vektör içidneki cirle larýn çizdirilmesi
        for (auto circle : circles) {
            bool active = circle.generated;
            float x = circle.x;
            float y = circle.y;
            sf::Color color = circle.color;
            float size = circle.size;

            if(!active){
                sf::CircleShape c(size);
                c.setFillColor(color);
                c.setOutlineColor(sf::Color::White);
                c.setOutlineThickness(3.f);
                c.setPosition({ x, y });
                window.draw(c);
            }
        }

        window.display();
    }
}