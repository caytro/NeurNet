#pragma once

#define DATASET_HPP

#include <DataSample.hpp>

#include <vector>
#include <ranges>


class DataSet
{
    public:
    // Constructors
        DataSet();
        explicit DataSet(size_t dimension);

    // Setters
        void setDimension(size_t dimension);

    // Getters
        size_t getDimension() const;
        const std::vector<DataSample>& getSamples() const;

    // Other
        void addSample(std::vector<double>& input, double output);
        void genereDiscDataset(size_t nSamples,
                           double xc, double yc,
                           double radius,
                           double output);

    // Normalization
        void computeFeatureMinMax();
        void normalizeFeatureWise();
        void normalizeSample(DataSample& s);
        const auto& mins() const;
        const auto& maxs() const;

    protected:

    private:
        size_t m_dimension; // Utile ?
        std::vector<DataSample> m_samples;
        std::vector<double> m_mins;
        std::vector<double> m_maxs;
};

