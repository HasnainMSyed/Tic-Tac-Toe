#include <vector>
#include <stdexcept>
#include <iostream>
#include <cmath>

// Road Map
/*
1. class Tensor
2. Tensor Operator
3. Tensor Add
4. Tensor ReLU
5. Tensor tanh
6. std::pair<Tensor,Tensor>softmax
7. class LinearLayer
8. class Network
9. Free helpers for Xavier init
10. grab stub (optional noq)
*/


class Tensor {
public:
    //---- constructors ----
    Tensor() = default;                       // empty tensor (0x0)
    Tensor(int r, int c);                     // build rows=r, cols=c, UN-initialised memory

    //---- shape queries ----
    int rows() const { return rows_; }
    int cols() const { return cols_; }
    std::size_t size() const { return data_.size(); }   // == rows_*cols_

    //---- element access ----
    float& operator()(int r, int c);          // A(r,c) = x   (no bounds check, fast)
    float  operator()(int r, int c) const;    // x = A(r,c)

    float& at(int r, int c);                  // bounds-checked; throws if bad
    float  at(int r, int c) const;

    //---- tiny utilities ----
    void fill(float val);                     // set every element to val
    void print() const;                       // dump to std::cout for debugging

private:
    int rows_ = 0;
    int cols_ = 0;
    std::vector<float> data_;                 // row-major storage
};

int main(){
    Tensor A(3,3);
    A(1,2) = 4.2;
    std::cout << A(1,2);
}