#include "Graphics.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include "DataSample.hpp"

using namespace std;

Graphics::Graphics()
{
    //ctor
}

Graphics::~Graphics()
{
    //dtor
}


void Graphics::test() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Demo");

    sf::CircleShape point(5);
    point.setFillColor(sf::Color::Red);
    point.setPosition(100, 100);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        window.draw(point);
        window.display();
    }

}

void Graphics::displayDataSet(const DataSet& dataSet) const
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML Demo");
    double xOffset = 400;
    double yOffset = 400;
    double scale = 50;
    vector<sf::CircleShape> points;
    vector<DataSample> samples = dataSet.getSamples();
    for (size_t i=0 ; i < samples.size() ; i++)
    {
        sf::CircleShape point (2);
        DataSample sample = samples.at(i);
        point.setPosition((sample.getInput().at(0) * scale + xOffset) , (sample.getInput().at(1) * scale + yOffset ));
        point.setFillColor(sf::Color::Red);
        points.push_back(point);
    }


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        for( size_t i = 0 ; i < points.size() ; i++ )
        {
            window.draw(points.at(i));
        }
        window.display();
    }

}

