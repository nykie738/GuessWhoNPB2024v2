#include <SFML/Graphics.hpp>
#include "iostream"

#include "Game.h"
//#include "Textbox.h"

sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 4) - 500, (sf::VideoMode::getDesktopMode().height / 4) - 535);
Game textbox1(30, sf::Color::Red, true);
std::string selectedTeam;
//bool wrong = false;

Game::Game(): 
    window(sf::VideoMode(1000, 1200), "Guess the Baseball Player!"),
    currentState(Gamestate::Initial), tempState(Gamestate::Initial) {
    playerManager.loadPlayers("players.csv");
    window.setPosition(centerWindow);
    window.setKeyRepeatEnabled(true);
     }


void Game::run() {
    while (window.isOpen()) {
        processEvents();
        if (tempState == currentState) {
            rend = 0;
        }
        else {
            rend = 1; 
            tempState = currentState;
        }
        update();
        render();
    }
}

void Game::update() {
    switch (currentState) {
        case Gamestate::Initial:
            handleInitial();
            break;
        case Gamestate::Selection:
            handleSelection();
            break;
        case Gamestate::Guessing:
            handleGuessing();
            break;
        //case Gamestate::Correct:
            //handleCorrect();
            //break;
        //case Gamestate::Incorrect:
            //handleIncorrect();
            //break;
    }
}

void Game::render() {
    if (rend != 0) {
        window.clear(sf::Color::Black);
    }
    if (currentState == Gamestate::Guessing) {
        //textbox1.drawTo(window);
    }
    // Render elements based on current state
    window.display();
}

void Game::handleInitial() {
    sf::RectangleShape startButton(sf::Vector2f(300, 150));
    startButton.setFillColor(sf::Color::Yellow);
    startButton.setPosition(350, 500);


    sf::Font font;
    if (!font.loadFromFile("misaki_gothic_2nd.ttf")) { // Use a font file (e.g. "arial.ttf")
            std::cerr << "Failed to load font." << std::endl;
            // Error handling (e.g. exit the program)
            std::exit(EXIT_FAILURE);
        }

    sf::Text startText("Start", font, 100);
    startText.setFillColor(sf::Color::Black);
    startText.setPosition(370, 500);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (startButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            currentState = Gamestate::Selection;
        }
    }

    window.draw(startButton);
    window.draw(startText);
}

void Game::handleSelection() {
    sf::Font font;
    if (!font.loadFromFile("misaki_gothic_2nd.ttf")) { // Use a font file (e.g. "arial.ttf")
            std::cerr << "Failed to load font." << std::endl;
            // Error handling (e.g. exit the program)
            std::exit(EXIT_FAILURE);
        }

    sf::RectangleShape HanshinB(sf::Vector2f(300, 50));
    HanshinB.setFillColor(sf::Color::Yellow);
    HanshinB.setPosition(325, 150);

    sf::Text HanshinT("Hanshin Tigers", font, 25);
    HanshinT.setFillColor(sf::Color::Black);
    HanshinT.setPosition(385, 160);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (HanshinB.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            currentState = Gamestate::Guessing;
            selectedTeam = "Hanshin Tigers";
            //break;
        }
    }

    window.draw(HanshinB);
    window.draw(HanshinT);
}

void Game::handleGuessing() {
    if (!currentPlayer && isGuessing) {
        currentPlayer = &playerManager.getRandomPlayerByTeam(selectedTeam, order);
        std::cout << order <<std::endl;
        //currentPlayer = &playerManager.getRandomPlayer();
        }
    
    sf::Sprite playerSprite(currentPlayer->getTexture());

    //readjust the image size info to fit into sfml window
    sf::Vector2u textureSize = playerSprite.getTexture()->getSize();
    const float adjWidth = 400.0f;
    const float adjHeight = 600.0f;
    float scaleX = adjWidth / textureSize.x;
    float scaleY = adjHeight / textureSize.y;
    float scale = std::min(scaleX, scaleY);

    playerSprite.setScale(scaleX, scaleY);
    playerSprite.setPosition(325, 135);


    sf::Font font;
    if (!font.loadFromFile("misaki_gothic_2nd.ttf")) { // Use a font file (e.g. "arial.ttf")
            std::cerr << "Failed to load font." << std::endl;
            // Error handling (e.g. exit the program)
            std::exit(EXIT_FAILURE);
        }

    //Textbox textbox1(15, sf::Color::Black, true);
    textbox1.setFont(font);
    textbox1.setPosition({375, 775});

    sf::RectangleShape inputBox(sf::Vector2f(300, 50));
    inputBox.setFillColor(sf::Color::White);
    inputBox.setOutlineColor(sf::Color::Yellow);
    inputBox.setOutlineThickness(4);
    inputBox.setPosition(375, 775);

    sf::RectangleShape confirmButton(sf::Vector2f(100, 50));
    confirmButton.setFillColor(sf::Color::White);
    confirmButton.setPosition(465, 870);

    sf::Text dareda("Guess the Player!", font, 50);
    dareda.setFillColor(sf::Color::Yellow);
    dareda.setPosition(325, 50);

    sf::Text confirmText("Confirm", font, 20);
    confirmText.setFillColor(sf::Color::Black);
    confirmText.setPosition(480, 880);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        if (mouseTrigger) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (confirmButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                //bool deleteSprite = true;
                if (textbox1.getText() == currentPlayer->getName()) {
                    std::cout << "SEIKAI" << std::endl;
                    std::cout << textbox1.getText() << std::endl;
                    currentPlayer = nullptr;
                    //isGuessing = false;
                    std::cout << "Next player aboard." << std::endl;
                    // Correct guess
                    //score++; // Assuming you've added a 'score' member to Game class
                    // Move to next player or round
                } 
                else {
                    std::cout << "Incorrect! Try again." << std::endl;

                    // Incorrect guess
                    // Perhaps show correct answer and then move to next player or round
                }
                textbox1.clearText();
                mouseTrigger = false;

            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                //bool deleteSprite = true;
                if (textbox1.getText() == currentPlayer->getName()) {
                    std::cout << "SEIKAI" << std::endl;
                    std::cout << textbox1.getText() << std::endl;
                    currentPlayer = nullptr;
                    //isGuessing = false;
                    std::cout << "Next player aboard." << std::endl;
                    // Correct guess
                    //score++; // Assuming you've added a 'score' member to Game class
                    // Move to next player or round
                } 
                else {
                    std::cout << "Incorrect! Try again." << std::endl;

                    // Incorrect guess
                    // Perhaps show correct answer and then move to next player or round
                }
                textbox1.clearText();
                mouseTrigger = false;

            }
        }
    }
    else {
        mouseTrigger = true;
    }
    window.clear(sf::Color::Black);
    window.draw(playerSprite);
    window.draw(dareda);
    window.draw(inputBox);
    window.draw(confirmButton);
    window.draw(confirmText);
    window.draw(inputText);
    textbox1.drawTo(window);
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {

            case sf::Event::Closed:
                window.close();
            case sf::Event::TextEntered:
                textbox1.typedOn(event);
        }
        // Handle other events based on current state
    }
}