#include <vector>
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


template <typename T>
class Tensor {
public:
    // 1. Data Storage
    std::vector<T> data;
    
    // 2. Shape / Dimensions (often called 'shape')
    std::vector<int> shape;
    
    // 3. Strides (optional but highly recommended for efficiency)
    std::vector<int> strides;
    
    // Rank is implicitly shape.size()
    // int rank; 
};


int main(){
    return 0;
}