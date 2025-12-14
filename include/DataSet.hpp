#pragma once

#include "Matrix.hpp"
#include <vector>

class DataSet
{
    public:
    // Constructors
        DataSet();
        DataSet(size_t inputDimension, size_t outputDimension);

    // Setters
        void setInputDimension(size_t inputDimension);
        void setOutputDimension(size_t outputDimension);
        void addSample(const Matrix& sampleInput, const Matrix& sampleOutput);

    // Getters
        size_t getInputDimension() const;
        size_t getOutputDimension() const;
        Matrix& getInput();
        const Matrix& getInput() const;
        Matrix& getOutput();
        const Matrix& getOutput() const;

    // Other

        // genereDiscDataset à conserver comme modèle pour dimension N
        void genereDiscDataset(size_t nSamples,
                           double xc, double yc,
                           double radius,
                           double output);

    // Normalization
        void computeFeatureMinMax();
        void normalizeFeatureWise();
        // const auto& mins() const;
        // const auto& maxs() const;

    protected:

    private:
        size_t m_inputDimension;
        size_t m_outputDimension;
        Matrix m_input;
        Matrix m_output;
        std::vector<double> m_mins;
        std::vector<double> m_maxs;
};

