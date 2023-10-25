#include "imports.hpp"

class Matrix {
    public:
        Matrix(unsigned int dimension);
        ~Matrix();

        static Matrix fromFile(std::string filename);

        unsigned int dim;

        void initRandom(unsigned int seed);
        void makeLU();
        void makePLU();
        double * getLine(unsigned int i);
    
    private:
        double ** m;
}
