#ifndef RAND_GENERATOR_H_
#define RAND_GENERATOR_H_

#define ENABLE_LOGGER false

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "Common.hpp"

const unsigned int k_rand_vec_length = 9973;

class RandGenerator
{
private:
    std::vector<float> random_num_vec_;
    unsigned int offset_;

    inline unsigned int get_offset() 
    {
        if(++offset_ == k_rand_vec_length) {
            offset_ = 0;
        }
        return offset_;
    }
    
public:
    RandGenerator()
    {
        reset();
    };

    void reset() 
    {
        offset_ = 0;
        random_num_vec_.clear();
        srand(time(NULL));
        for(int i = 0; i < k_rand_vec_length; i++) {
            random_num_vec_.push_back(static_cast<float> (rand() / static_cast<float> (RAND_MAX)));
        }
    }

    inline float generate_uniform(float u_min, float u_max)
    {
        return u_min + ((u_max - u_min) * random_num_vec_.at(get_offset()));
    }

    inline float generate_gaussian(float std_deviation, float mean) 
    {
        return mean + std_deviation * random_num_vec_.at(get_offset());
    }

#if ENABLE_LOGGER
    void logger() 
    {
        for(int i = 0; i < k_rand_vec_length; i++) 
        {
            std::cout << random_num_vec_.at(i) << ' ';
        }
    }
#endif

    ~RandGenerator(){};
};

// RandGenerator::RandGenerator() 
// {
//     reset();
// }
// RandGenerator::~RandGenerator() {}


#endif // RAND_GENERATOR_H_