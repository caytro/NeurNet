#ifndef DENDRITE_H
#define DENDRITE_H

class Perceptron;

class Dendrite
{
    public:
        Dendrite();
        Dendrite(Perceptron* source, Perceptron* cible, double weight);
        virtual ~Dendrite();

        double getWeight();
        void setWeight(double val);
        Perceptron* getSource();
        void setSource(Perceptron *source);
        Perceptron* getBody();
        void setBody(Perceptron *body);

    protected:

    private:
        double m_weight;
        Perceptron *m_source;
        Perceptron *m_body;
};

#endif // DENDRITE_H
