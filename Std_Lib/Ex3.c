#include <stdio.h>
#include <math.h>

int main() {
    double num;

    printf("Enter a floating-point number: ");
    scanf("%lf", &num);

    double sqrt_value = sqrt(num);
    printf("Square root of %.2f: %.2f\n", num, sqrt_value);

    double rounded_value = round(num);
    printf("Rounded value: %.0f\n", rounded_value);

    double sine_value = sin(num);
    printf("Sine of %.2f (in radians): %.2f\n", num, sine_value);

    return 0;
}