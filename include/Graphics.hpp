#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP
#include "DataSet.hpp"

class Graphics
{
    public:
        Graphics();
        virtual ~Graphics();
        void test();
        void displayDataSet(const DataSet& dataSet) const;

    protected:

    private:
};

#endif // GRAPHICS_HPP
