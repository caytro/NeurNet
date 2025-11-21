#ifndef DATASET_HPP
#define DATASET_HPP

#include <DataSample.hpp>
#include <vector>


class DataSet
{
    public:
        DataSet();
        void setInputDimension(size_t inputDimension);
        size_t getInputDimension() const;
        void addDataSample(std::vector<double>& input, double output);
        const std::vector<DataSample>& getDatas() const;

    protected:

    private:
        size_t m_inputDimension;
        std::vector<DataSample> m_samples;
};

#endif // DATASET_HPP
