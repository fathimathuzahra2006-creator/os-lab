// multithread_stats.c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int numbers[100];
int n;

double mean;
double median;
double std_deviation;

// -----------------------------------
// Thread function to calculate Mean
// -----------------------------------
void *calculate_mean(void *arg)
{
    int sum = 0;

    for (int i = 0; i < n; i++)
    {
        sum += numbers[i];
    }

    mean = (double)sum / n;

    pthread_exit(0);
}

// -----------------------------------
// Function to sort array
// -----------------------------------
void sort()
{
    int temp;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (numbers[i] > numbers[j])
            {
                temp = numbers[i];
                numbers[i] = numbers[j];
                numbers[j] = temp;
            }
        }
    }
}

// -----------------------------------
// Thread function to calculate Median
// -----------------------------------
void *calculate_median(void *arg)
{
    sort();

    if (n % 2 == 0)
    {
        median = (numbers[n / 2] +
                  numbers[(n / 2) - 1]) / 2.0;
    }
    else
    {
        median = numbers[n / 2];
    }

    pthread_exit(0);
}

// -----------------------------------
// Thread function to calculate
// Standard Deviation
// -----------------------------------
void *calculate_std_deviation(void *arg)
{
    double sum = 0;

    for (int i = 0; i < n; i++)
    {
        sum += pow(numbers[i] - mean, 2);
    }

    std_deviation = sqrt(sum / n);

    pthread_exit(0);
}

// -----------------------------------
// Main Function
// -----------------------------------
int main(int argc, char *argv[])
{
    pthread_t tid1, tid2, tid3;

    if (argc < 2)
    {
        printf("Usage: %s numbers\n", argv[0]);
        return 1;
    }

    n = argc - 1;

    // Store command-line integers
    for (int i = 0; i < n; i++)
    {
        numbers[i] = atoi(argv[i + 1]);
    }

    // Create Mean Thread
    pthread_create(&tid1, NULL,
                   calculate_mean, NULL);

    pthread_join(tid1, NULL);

    // Create Median Thread
    pthread_create(&tid2, NULL,
                   calculate_median, NULL);

    // Create Standard Deviation Thread
    pthread_create(&tid3, NULL,
                   calculate_std_deviation, NULL);

    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);

    // Display Results
    printf("\nMean = %.2f\n", mean);
    printf("Median = %.2f\n", median);
    printf("Standard Deviation = %.2f\n",
           std_deviation);

    return 0;
}