/*
 * About: ECC Diffie-Hellman Key Exchange Header File
 * Author: Bradley Reeves
 * Date: 04/04/2021
 * 
 * mod: Return a mod b for + and - integers.
 * power: Return xʸ, naive method.
 * gcd: Return GCD of integers a and b.
 * modexp: Modular exponentiation: xʸ mod m.
 * modinv: Modular multiplicative inverse, assumes m is a prime number.
 * equal: Checks if two points are equal.
 * about: Initial output to terminal.
 */

#define INF 2147483647

struct Point {
    int64_t x;
    int64_t y;
};

int64_t mod(int64_t a, int64_t b);
int64_t power(int64_t x, int64_t y);
int64_t gcd(int64_t a, int64_t b);
int64_t modexp(int64_t x, int64_t y, int64_t m);
int64_t modinv(int64_t a, int64_t m);
int equal(struct Point *p1, struct Point *p2);
void about();