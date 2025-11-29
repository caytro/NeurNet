#include "Graphic.hpp"

Graphic::Graphic(const DataSet& dataSet, const Perceptron& perceptron)
    : m_window(sf::VideoMode(800, 600), "Perceptron Decision Boundary"),
    m_view(sf::FloatRect(-2.f, -2.f, 4.f, 4.f)),
    m_dataSet(dataSet),
    m_perceptron(perceptron),
    m_decisionLine(sf::Lines, 2)
{
    m_window.setView(m_view);
    updateDecisionBoundary();
}

void Graphic::updateDecisionBoundary()
{
    const auto& w = m_perceptron.getWVector();
    double w1 = w[0];
    double w2 = w[1];
    double b  = m_perceptron.getBiais();

    float xmin = -100.f;
    float xmax = 100.f;

    if (w2 != 0.0) {
        float y1 = (-w1 * xmin - b) / w2;
        float y2 = (-w1 * xmax - b) / w2;

        m_decisionLine[0].position = {xmin, y1};
        m_decisionLine[1].position = {xmax, y2};
    }
    else {
        // droite verticale x = -b/w1
        float x = -b / w1;
        m_decisionLine[0].position = {x, -10000.f};
        m_decisionLine[1].position = {x, +10000.f};
    }

    m_decisionLine[0].color = sf::Color::Red;
    m_decisionLine[1].color = sf::Color::Red;
}

void Graphic::drawSamples()
{
    const auto& samples = m_dataSet.getSamples();

    for (const auto& s : samples) {
        const auto& x = s.getInput();
        float px = x[0];
        float py = x[1];

        sf::CircleShape point(0.01f);
        point.setOrigin(0.01f, 0.01f);
        point.setPosition(px, py);

        point.setFillColor(s.getOutput() == 0 ? sf::Color::Blue
                                              : sf::Color::Green);

        m_window.draw(point);
    }
}

sf::RenderWindow& Graphic::getWindow()
{
    return m_window;
}

void Graphic::render()
{
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            m_window.close();
    }

    m_window.clear(sf::Color::White);

    drawSamples();
    m_window.draw(m_decisionLine);

    m_window.display();
}
