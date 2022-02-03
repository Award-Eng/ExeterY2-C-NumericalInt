/*
=================================
Project One for PHY2027 module
Date: 14/12/2018
=================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
===============================================================================
This is a program designed to perform the numerical integration of user entered
polynomial functions
===============================================================================
*/


/*
Functions created for this program
*/
float height(float b, float a, float n);
float trap_rule(float h, float a, float b, float n, float* order_array, int delta);
float simp_rule(float h, float a, float b, float n, float* order_array, int delta);
float equation(float* order_array, float array_x, int delta);

int main()
{
    float a, b, n, trap_sum_test, simp_sum_test;
    int order, choice;
    float* order_array;

    printf("This is a program designed for you to enter a Polynomial then choose how you want to integrate it\n");
    printf("\nPlease enter your upper limit for your Polynomial\n");
    while (!scanf("%f", &b))
    {
        while (getchar() != '\n');
            printf("Limit is not valid, please enter again: \n");
    }


    printf("\nPlease enter your lower limit for your Polynomial\n");
    while (!scanf("%f", &a))
    {
        while (getchar() != '\n');
            printf("Limit is not valid, please enter again: \n");
    }


    printf("\nEnter the number of terms\n");
    while (!scanf("%f", &n))
    {
        while (getchar() != '\n');
            printf("Limit is not valid, please enter again: \n");
    }


    order_array = (float *)malloc( n*sizeof(float));
    float h = height(b,a,n);


    printf("\nPlease enter your order of coefficients(+ve only)\n");
    scanf("%d", &order);
    printf("Your order is: %d\n", order);


    int delta = order+1;
    printf("\nPlease enter %d coefficients(starting with your x^0 term)\n", delta);
    for (int i=0; i<delta;++i)
    {
        scanf("%f", &order_array[i]);
    }

/*
Prints out your equation including any negatives
*/
    for (int i=0;i<delta;++i)
    {
        if (delta<0)
        {
            break;
        }
        if (order_array[i]>0)
        {
            printf(" + ");
        }
        else if (order_array[i]<0)
        {
            printf(" - ");
        }
        else
        {
            printf(" ");
        }
        printf("%dx^%d ", abs(order_array[i]), i);
    }

/*
Menu to select how you want to integrate
*/
    printf("\n What type of Integration method would you like to use?\n\n"
           "\t 1. Trapezium Rule\n"
           "\t 2. Simpson Rule\n\n"
           "\t 3. Quit the program\n");
    do{
        scanf("%d", &choice);

        if (choice < 1 && choice > 3 && getchar() != '\n'){
            printf("Please look over the options and try again\n");
        }
    }while (choice < 1 && choice > 3 && getchar() != '\n');

    switch (choice) {
       case 1:
            printf("\nYou have selected the Trapezium Rule\n\n");
            trap_sum_test = trap_rule(h, a, b, n, order_array, delta);
            printf("\n%f is your final sum", trap_sum_test);
            break;

       case 2:
            printf("You have selected the Simpson Rule\n");
            simp_sum_test = simp_rule(h, a, b, n, order_array, delta);
            printf("\n%f is your final sum", simp_sum_test);
            break;

       case 3:
            printf("You have selected to terminate the program\n");
            return 0;


}
}

/*
Function to calculate the height of the area to be integrated
*/
float height(float b, float a, float n)
{
    float h;
    h = ((b-a)/(n)); //When plotting count zero as a term so n + 1
    printf("Your value of h is %f", h);
    return h;
}

/*
Function containing the user inputted equation and allows its terms to be worked out
*/
float equation(float* order_array, float array_x, int delta)
{
    float f;
    for(int j=0;j<delta;++j)
    {
        f+=order_array[j]*pow(array_x,j);
    }
    return f;
}

/*
Function to calculate the trapezium rule of your polynomial
*/
float trap_rule(float h, float a, float b, float n, float* order_array, int delta)
{
    float trap_sum, total;
    float* array_x;
    array_x = (float *)malloc( n*sizeof(float));
    float* array_y;
    array_y = (float *)malloc( n*sizeof(float));


    printf("\nYou have chosen to integrate a function by using the trapezium rule\n");
    int final_term = n-1;

    for(int i=1;i<final_term;++i)
    {
        array_x[i]=a+(i*h);
        array_y[i]=equation(order_array, array_x[i], delta);
        total += array_y[i];
    }


    trap_sum=(h/2.0)*((equation(order_array, a, delta))+(equation(order_array, b, delta))+(2*total));
    //printf("%g\n",b);
    return trap_sum;
}

/*
Function calculating the Simpson Rule
*/
float simp_rule(float h, float a, float b, float n, float* order_array, int delta)
{
    float simp_sum, adder, odd, even;
    float* array_x;
    array_x = (float *)malloc( n*sizeof(float));
    float* array_y;
    array_y = (float *)malloc( n*sizeof(float));


    printf("\nYou have chosen to integrate a function by using the Simpsons rule\n");
    int final_term = n-1;

    for (int i=1;i<final_term;++i)
    {
        array_x[i]=a+(i*h);
        array_y[i]=equation(order_array, array_x[i], delta);
        if(i % 2 ==0)
            adder+=2*array_y[i];
        else if (i % 2 !=0)
            adder+=4*array_y[i];
    }
    /*for(int i=1;i<final_term;i+=2)
    {
        array_x[i]=a+(i*h);
        array_y[i]=equation(order_array, array_x[i], delta);
        odd += array_y[i];
    }
        for(int i=2;i<final_term;i+=2)
    {
        array_x[i]=a+(i*h);
        array_y[i]=equation(order_array, array_x[i], delta);
        even += array_y[i];
    }
    */

    simp_sum=((1.0/3.0)*h)*(equation(order_array, a, delta)+equation(order_array, b, delta)+adder);
    //printf("%g\n",array_x[final_term]);
    return simp_sum;
}

/*
=============================================TESTING======================================================
This is a program designed for you to enter a Polynomial then choose how you want to integrate it

Please enter your upper limit for your Polynomial
6

Please enter your lower limit for your Polynomial
2

Enter the number of terms
4
Your value of h is 1.000000
Please enter your order of coefficients(+ve only)
2
Your order is: 2

Please enter 3 coefficients(starting with your x^0 term)
2 0 1
 + 2x^0  0x^1  + 1x^2
 What type of Integration method would you like to use?

         1. Trapezium Rule
         2. Simpson Rule

         3. Quit the program
1

You have selected the Trapezium Rule


You have chosen to integrate a function by using the trapezium rule

94.000000 is your final sum

Exact solution is 77.333

This is a program designed for you to enter a Polynomial then choose how you want to integrate it

Please enter your upper limit for your Polynomial
8

Please enter your lower limit for your Polynomial
2

Enter the number of terms
8
Your value of h is 0.750000
Please enter your order of coefficients(+ve only)
2
Your order is: 2

Please enter 3 coefficients(starting with your x^0 term)
0 0 1
 0x^0  0x^1  + 1x^2
 What type of Integration method would you like to use?

         1. Trapezium Rule
         2. Simpson Rule

         3. Quit the program
2
You have selected the Simpson Rule

You have chosen to integrate a function by using the Simpsons rule

338.906250 is your final sum

Exact solution is 168
*/
