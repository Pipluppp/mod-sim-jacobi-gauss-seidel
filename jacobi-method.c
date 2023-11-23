// Online C compiler to run C program online
#include <stdio.h>
#include <math.h>
#define MATRIX_SIZE 3
#define ERROR_SET 0.01

int main() {
    // Matrix of coefficients of the system
    int matrix[3][3] = { {3, 1, 1}, 
                         {2, 6, 3}, 
                         {2, 1, 4} };
    
    // Resulting vector
    int resulting_vec[3] = {1, 2, 3};
    
    /* An extra copy to have access to the current and also the previous iteration's approximated variables
    For each iteration, tmp_approx holds the new calculated variables, but then we copy it to approx by the end */
    float approx[3] = {0, 0, 0};
    float tmp_approx[3] = {0, 0, 0}; 
    
    // Error variables
    float error = 1;
    float err[3] = {0};
    
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

    // TODO: Check if possible to be rearranged into Diagonally Dominant
    // TODO: Rearrange to Diagonally Dominant

    // Jacobi Method Algorithm
    while (error >= ERROR_SET)
    {   
        for (int i = 0; i < MATRIX_SIZE; i++)
        {            
            // Subtract dot product of row with approx (i != j)
            for (int j = 0; j < MATRIX_SIZE; j++)
                if (i != j)
                    tmp_approx[i] -= matrix[i][j] * approx[j];

            tmp_approx[i] += resulting_vec[i]; // Add resulting vector coefficient

            tmp_approx[i] /= matrix[i][i]; // Divide whole expression by coefficient of var being solved
        } 
        
        // Calculate errors
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
            tmp_approx[i] = 0;
    
        iter++;
    }
}