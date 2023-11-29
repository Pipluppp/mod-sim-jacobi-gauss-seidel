// Online C compiler to run C program online
#include <stdio.h>
#include <math.h>
#define MATRIX_SIZE 3
#define ERROR_SET 0.0001
#define DIVERGE_SET 1000000

int main() {
    // Matrix of coefficients of the system
    int matrix[3][3] = { {3, 1, 1}, 
                         {2, 6, 3}, 
                         {2, 1, 4} };
    
    // Resulting vector
    int resulting_vec[3] = {1, 2, 3};

    printf("JACOBI METHOD\n");
    printf("Solving the following System of Linear Equations in three (3) variables\n");
    printf("3x + y + z = 1 \n 2x + 6y + 3z = 2 \n 2x + y + 4z = 3\n");
    
    // For the previous and current iteration's approximations
    float previous_approximation[3] = {0, 0, 0};
    float current_approximation[3] = {0, 0, 0}; 
    
    // Errors
    float error = 1; 
    float err[3] = {0}; // Errors for X, Y, Z
    float product_errors = 1; // To check divergence of error
    
    int iter = 0; 
    
    // Check if Diagonally Dominant
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        float diag_var = matrix[i][i];

        for (int j = 0; j < MATRIX_SIZE; j++)
            if (i != j)
                diag_var -= matrix[i][j];
        
        if (diag_var <= 0)
        {
            printf("Not Diagonally Dominant\n");
            break;
        }
    }

    // Jacobi Method Algorithm
    while (error >= ERROR_SET)
    {   
        for (int i = 0; i < MATRIX_SIZE; i++)
        {            
            current_approximation[i] += resulting_vec[i]; // Add resulting vector coefficient

            // Subtract dot product of row with approx (i != j)
            for (int j = 0; j < MATRIX_SIZE; j++)
                if (i != j)
                    current_approximation[i] -= matrix[i][j] * previous_approximation[j];

            current_approximation[i] /= matrix[i][i]; // Divide whole expression by coefficient of variable being solved
        } 
        
        // Calculate errors
        error = 0;
        for (int i = 0; i < MATRIX_SIZE; i++)
        {
            err[i] = fabs((current_approximation[i] - previous_approximation[i]) / current_approximation[i]);
            error += err[i] / MATRIX_SIZE;
        }

        // Diverging errors check
        product_errors *= error;
        if (product_errors > DIVERGE_SET)
        {
            printf("Diverging");
            break;
        }

        // Print iteration's values
        printf("\nITERATION %d:\n", iter);
        for (int i = 0; i < 3; i++)
            printf("%c: %f\n", 88 + i, current_approximation[i]);
        printf("Error: %f\n", error);

        // Update the approximations
        for (int i = 0; i < MATRIX_SIZE; i++)
            previous_approximation[i] = current_approximation[i];
        
        // Reset current_approximation 
        for (int i = 0; i < MATRIX_SIZE; i++)
            current_approximation[i] = 0;
    
        iter++;
    }
}