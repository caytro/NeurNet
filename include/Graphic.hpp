#pragma once
#include "DataSet.hpp"
#include "Perceptron.hpp"

#include <SFML/Graphics.hpp>

class Graphic {
public:

// Constructors

    Graphic(const DataSet& dataSet, const Perceptron& perceptron);

// Setters


// Getters

    sf::RenderWindow& getWindow() ;
    bool isOpen() const;


// Other

    void updateDecisionBoundary();   // recalculer la ligne
    void render();                   // afficher la frame

private:
    sf::RenderWindow m_window;
    sf::View m_view;

    const DataSet& m_dataSet;
    const Perceptron& m_perceptron;

    sf::VertexArray m_decisionLine;

    void drawSamples();              // nuages de points
};
