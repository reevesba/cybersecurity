/*
 * About: ECC Diffie-Hellman Key Exchange Utilites
 * Author: Bradley Reeves
 * Date: 04/04/2021
 */

#include <stdio.h>
#include <stdlib.h>
#include "ecdhlib.h"

// Return a mod b for + and - integers
int64_t mod(int64_t a, int64_t b) {
    return (a % b + b) % b;
}

// Return xʸ, naive method
int64_t power(int64_t x, int64_t y) {
    int64_t val = 1;
    for (int i = 0; i < y; i++)
        val *= x;
    return val;
}

// Return GCD of integers a and b
int64_t gcd(int64_t a, int64_t b) {
    if (a == 0)
        // Should always return 1 for this application
        return 1;

    // By Euclidean Algorithm, gcd(a, b) = gcd((b % a), a) until a = 0
    return gcd(mod(b, a), a);
}

// Modular exponentiation: xʸ mod m
int64_t modexp(int64_t x, int64_t y, int64_t m) {
    if (y == 0)
        return 1;

    int64_t p = mod(modexp(x, y/2, m), m);
    p = mod((p*p), m);
    return (mod(y, 2) == 0) ? p : mod((x*p), m);
}

// Modular multiplicative inverse, assumes m is a prime number
int64_t modinv(int64_t a, int64_t m) {
    int64_t g = gcd(a, m);

    if (g != 1) 
        printf("Warning: inverse doesn't exist for %ld mod %ld.\n", a, m);
    else
        // By Fermat's Little Theorem, aᵐ⁻² ≡ a⁻¹ (mod m)
        return modexp(a, m - 2, m);
}

// Checks if two points are equal
int equal(struct Point *p1, struct Point *p2) {
    return p1->x == p2->x && p1->y == p2->y;
}

// Initial output to terminal.
void about() {
    printf("                                                                \n");
    printf("   ad8888888888ba                                               \n");
    printf("  dP'         `\"8b,                                            \n");
    printf("  8  ,aaa,       \"Y888a     ,aaaa,     ,aaa,  ,aa,             \n");
    printf("  8  8' `8           \"88baadP\"\"\"\"YbaaadP\"\"\"YbdP\"\"Yb   \n");
    printf("  8  8   8              \"\"\"        \"\"\"      \"\"    8b    \n");
    printf("  8  8, ,8         ,aaaaaaaaaaaaaaaaaaaaaaaaddddd88P            \n");
    printf("  8  `\"\"\"'       ,d8""                                       \n");
    printf("  Yb,         ,ad8\"    Diffie Hellman Key Exchange             \n");
    printf("   \"Y8888888888P\"      v1.0                                   \n");
    printf("                                                                \n");
}