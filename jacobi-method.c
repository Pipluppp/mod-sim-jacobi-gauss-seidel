// Online C compiler to run C program online
#include <stdio.h>
#include <math.h>
#define MATRIX_SIZE 3
#define ERROR_SET 0.01

int main() {
    // Matrix
    int a[3][3] = { {3, 1, 1}, 
                    {2, 6, 3}, 
                    {2, 1, 4}};
    
    // Resulting vector
    int vec[3] = {1, 2, 3};
    
    // Vars
    float approx[3] = {0, 0, 0};
    float tmp_approx[3] = {0, 0, 0};
    
    float error = 1;
    float err[3] = {0};
    
    int iter = 0;
    
    // TODO: Diagonal checker
    
    // Jacobi Method Algorithm
    while (error >= ERROR_SET)
    {
        iter++;
        
        for (int i = 0; i < MATRIX_SIZE; i++)
        {
            // Add resulting vector coefficient
            tmp_approx[i] += vec[i];
            
            // Subtract dot product of row with approx (i != j)
            for (int j = 0; j < MATRIX_SIZE; j++)
            {
                if (i == j)
                    continue;
                    
                tmp_approx[i] -= a[i][j] * approx[j];
            }
            
            // Divide by coefficient of current
            tmp_approx[i] /= a[i][i];
        }
        
        // Error calculations
        error = 0;
        for (int i = 0; i < MATRIX_SIZE; i++)
        {
            err[i] = fabs((tmp_approx[i] - approx[i]) / tmp_approx[i]);
            error += err[i] / MATRIX_SIZE;
        }
    
        // Update the current approximations
        for (int i = 0; i < MATRIX_SIZE; i++)
            approx[i] = tmp_approx[i];
        
        // Print iteration's values
        printf("\nITERATION %d:\n", iter);
        for (int i = 0; i < 3; i++)
            printf("Approximation X_%d: %f\n", i + 1, approx[i]);
        printf("Error: %f\n", error);
        
        // Reset tmp_approx
        for (int i = 0; i < MATRIX_SIZE; i++)
        {
            tmp_approx[i] = 0;
        }
    
    }

    return 0;
}