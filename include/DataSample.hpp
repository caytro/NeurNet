#ifndef DATASAMPLE_HPP
#define DATASAMPLE_HPP

#include <vector>

class DataSample
{
    public:
        DataSample();
        DataSample(std::vector<double>&input, double output);
        void setInput(std::vector<double>& input);
        const std::vector<double>& getInput() const;
        std::vector<double>& getInput(); // mutable
        void setOutput(double output);
        double getOutput() const;

    protected:

    private:
        std::vector<double> m_input;
        double m_output;
};

#endif // DATASAMPLE_HPP
