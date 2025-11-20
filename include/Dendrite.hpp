#pragma once

class Perceptron;

class Dendrite {
public:
    Dendrite(Perceptron& source, double weight);

    Perceptron& getSource() const;
    double getWeight() const;

private:
    Perceptron& m_source;
    double m_weight;
};
