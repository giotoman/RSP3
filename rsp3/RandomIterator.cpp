//
// Created by thomas on 12/2/21.
//

#include "RandomIterator.h"

/* Constructor for RandomIterator class.
 * Parameters:
 *     - amount => Amount of numbers to generate
 *     - min    => Minimum number in range to generate
 *     - max    => Maximum number in range to generate
 *
 * The constructor also instanstiates the variable gen
 * with a new random_device.
 */
RandomIterator::RandomIterator(const unsigned long long &amount, const unsigned long long &min, const unsigned long long &max):gen((std::random_device())())
{
    floor = min;
    num_left = amount;
    last_k = min;
    n = max - 1;
}

// Return a bool to determine if there are any numbers left to generate
bool RandomIterator::has_next() const
{
    return num_left > 0;
}

// Generate the next random number
unsigned long long RandomIterator::next()
{
    if (num_left > 0)
    {
        // Partition the range of numbers to generate from
        unsigned long long range_size = (n - last_k) / num_left;

        // Initialize random generator
        std::uniform_int_distribution<unsigned long long> rnd(floor, range_size);

        // Generate random number
        unsigned long long r = rnd(gen) + last_k + 1;

        // Set last_k to r so that r is not generated again
        last_k = r;
        num_left--;
        return r;
    }
    else
    {
        throw std::out_of_range("Exceeded amount of random numbers to generate.");
    }
}