#ifndef PERCEPTRON_H
#define PERCEPTRON_H


class Perceptron
{
    public:
        Perceptron();
        virtual ~Perceptron();
        void connectSource(Perceptron* source, double weight);
        double getVal();

    protected:

    private:
        vector<Dendrite *> m_dendrites;

};

#endif // PERCEPTRON_H
