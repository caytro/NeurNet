#include "Dendrite.h"
#include <stdlib.h>

using namespace std;

Dendrite::Dendrite(Perceptron* source)
{
    m_source = source;
}

Dendrite::~Dendrite()
{
    //dtor
}
/** @brief (one liner)
  *
  * (documentation goes here)
  */
void Dendrite::setWeight(double val)
{
    m_weight = val;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
double Dendrite::getWeight()
{
    return m_weight;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void Dendrite::setBody(Perceptron*  body)
{
    m_body = body;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
Perceptron* Dendrite::getBody()
{
    return m_body;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void Dendrite::setSource(Perceptron* source)
{
    m_source = source;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
Perceptron* Dendrite::getSource()
{
    return m_source;
}



