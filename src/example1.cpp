#include <iostream>
#include <chrono>
#include <omp.h>

#define NUM_THREADS 2

double step;
static long num_steps = 100000000;

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    int n_threads;
    double pi;
    double sum[NUM_THREADS];

    step = 1.0 / (double)num_steps;

#pragma omp parallel num_threads(NUM_THREADS)
    {
        int i;
        double x;
        int id = omp_get_thread_num();

        std::cout << "Hello from thread: " << id << std::endl;

        if (id == 0)
            n_threads = omp_get_num_threads();

        for (i = id, sum[id] = 0.0; i < num_steps; i += n_threads)
        {
            x = (i + 0.5) * step;
            sum[id] += 4.0 / (1.0 + x * x);
        }
    }

    int i;
    for (i = 0, pi = 0; i < n_threads; i++)
    {
        pi += sum[i] * step;
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout << "Calcuated pi: " << pi << " in " << duration.count() << " ms" << std::endl;

    return 0;
}