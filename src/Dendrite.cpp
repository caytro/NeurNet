#include "Dendrite.hpp"
#include "Perceptron.hpp"
#include <stdlib.h>

using namespace std;

Dendrite::Dendrite():m_weight(0),m_source(nullptr), m_body(nullptr)
{
    m_source = new Perceptron();
    m_body= new Perceptron();
}

Dendrite::Dendrite(Perceptron* source, Perceptron* body, double weight):m_weight(weight), m_source(nullptr), m_body(nullptr){
    m_source = source;
    m_body = body;
}

Dendrite::~Dendrite()
{
    //dtor
}


void Dendrite::setWeight(double val)
{
    m_weight = val;
}


double Dendrite::getWeight()
{
    return m_weight;
}


void Dendrite::setBody(Perceptron  *body)
{
    m_body = body;
}


Perceptron* Dendrite::getBody()
{
    return m_body;
}


void Dendrite::setSource(Perceptron *source)
{
    m_source = source;
}


Perceptron* Dendrite::getSource()
{
    return m_source;
}



