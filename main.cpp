#include <iostream>
#include <omp.h>
#include <vector>

// Function for the Linear Congruential Generator
int lcg(int seed) {
    // Parameter choices explained in README
    int a = 258524;
    int c = 0;
    int m = 34359738337; // 2^35 - 31

    return (a * seed + c) % m;
}

// Normalizes the generated random number to be between 0 and 1
// Required for Monte Carlo simulation
double random_float(int seed) {
    return static_cast<double>(lcg(seed)) / 34359738337.0;
}

// Function to estimate π using Monte Carlo simulation
double estimate_pi(const std::vector<double>& random_numbers) {
    int inside_circle = 0;
    int total_numbers = random_numbers.size();

    for (size_t i = 0; i < total_numbers; i += 2) {
        double x = random_numbers[i];
        double y = random_numbers[i + 1];
        if (x * x + y * y <= 1.0) {
            ++inside_circle;
        }
    }

    return 4.0 * inside_circle / total_numbers;
}

int main() {
    // Set the seed for the built-in random number generator used to generate the seed for our LCG
    std::srand(static_cast<unsigned>(std::time(0)));

    // Set number of parallel threads to use and how many random numbers should be generated
    int threads = 4;
    int numbers_generated = 1000000;
    int numbers_per_thread = numbers_generated / threads;

    // Generate seeds for each thread
    std::vector<int> seeds(threads);
    for (int i = 0; i < threads; ++i) {
        // Use built-in random number generator to generate seeds
        seeds[i] = std::rand();
    }

    // Vector for storing the generated random numbers
    std::vector<double> random_numbers_parallel(numbers_generated);

    // Measure the speed of parallel random number generation
    double start_time_parallel = omp_get_wtime();
    #pragma omp parallel for
    for (int i = 0; i < threads; ++i) {
        int seed = seeds[i];
        for (int j = 0; j < numbers_per_thread; ++j) {
            int index = i * numbers_per_thread + j;
            random_numbers_parallel[index] = random_float(seed);
            seed = lcg(seed);
        }
    }

    // Run Monte Carlo simulation using the generated random numbers, stop timer once done
    double pi_estimate_para = estimate_pi(random_numbers_parallel);
    double parallel_time = omp_get_wtime() - start_time_parallel;

    // Vector for storing the sequentially generated random numbers
    std::vector<double> random_numbers_seq(numbers_generated);

    // Measure the speed of sequential random number generation
    double start_time_sequential = omp_get_wtime();
    for (int i = 0; i < threads; ++i) {
        int seed = seeds[i];
        for (int j = 0; j < numbers_per_thread; ++j) {
            int index = i * numbers_per_thread + j;
            random_numbers_seq[index] = random_float(seed);
        }
    }

    // Run Monte Carlo simulation using the generated random numbers, stop timer once done
    double pi_estimate_seq = estimate_pi(random_numbers_seq);
    double sequential_time = omp_get_wtime() - start_time_sequential;

    std::cout << "Parallel Random Number Generation Time: " << parallel_time << " seconds" << std::endl;
    std::cout << "Sequential Random Number Generation Time: " << sequential_time << " seconds" << std::endl;

    return 0;
}