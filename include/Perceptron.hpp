#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <vector>
#include <memory>
#include "Dendrite.hpp"

class Perceptron
{
    public:
        Perceptron();
        virtual ~Perceptron();
        void connectSource(Perceptron *source, double weight);
        double calcOutput();
        void setVal(double val);
        double getVal();
        void setBiais(double biais);
        double getBiais();
        std::vector<std::unique_ptr<Dendrite>> *getDendrites();

    protected:

    private:
        std::vector<std::unique_ptr<Dendrite>> m_dendrites;
        double m_value; /* Pour les neurones d'entrée. Si as de dendrite alors calcOutput retourne m_value */
        double m_biais;

};

#endif // PERCEPTRON_H
