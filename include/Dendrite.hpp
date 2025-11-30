#pragma once

class Perceptron;

class Dendrite {
public:

//Constructors

    Dendrite(Perceptron& source, double weight);

// Setters

    void setWeight(double weight);

//Getters

    Perceptron& getSource() const;
    double getWeight() const;


private:
    Perceptron& m_source;
    double m_weight;
};
