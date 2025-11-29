#pragma once

#include <SFML/Graphics.hpp>
#include "DataSet.hpp"
#include "Perceptron.hpp"

class Graphic {
public:
    Graphic(const DataSet& dataSet, const Perceptron& perceptron);
    sf::RenderWindow& getWindow() ;

    void updateDecisionBoundary();   // recalculer la ligne
    void render();                   // afficher la frame
    bool isOpen() const { return m_window.isOpen(); }

private:
    sf::RenderWindow m_window;
    sf::View m_view;

    const DataSet& m_dataSet;
    const Perceptron& m_perceptron;

    sf::VertexArray m_decisionLine;

    void drawSamples();              // nuages de points
};
