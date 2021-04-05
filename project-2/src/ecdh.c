/*
 * About: ECC Diffie-Hellman Key Exchange
 * Author: Bradley Reeves
 * Date: 04/04/2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ecdhlib.h"

// Returns value to be used in P3 calculation where P3 = P1 + P2
int64_t m(struct Point *p1, struct Point *p2, int64_t a, int64_t p) {
    int val;

    if (!equal(p1, p2))
        // m = (y₂ - y₁) ⋅ (x₂ - x₁)⁻¹ mod p
        val = mod((p2->y - p1->y)*modinv(p2->x - p1->x, p), p);
    else
        // m = (3x₁² + a) ⋅ (2y₁)⁻¹ mod p
        val = mod((3*power(p1->x, 2) + a)*modinv(2*p1->y, p), p);

    return val;
}

// Adds two points on elliptic curve
struct Point add(struct Point *p1, struct Point *p2, int64_t a, int64_t p) {
    struct Point p3;
    int64_t em = m(p1, p2, a, p);

    // Special case 1: if m = ∞ then P3 = ∞
    if (em >= INF) {
        p3.x = (int64_t) INF;
        p3.y = (int64_t) INF;
        return p3;
    }

    // Special case 2: ∞ + P = P for all P
    if (p1->x >= INF && p1->y >= INF) {
        p3.x = p2->x;
        p3.y = p2->y;
        return p3;
    }

    if (p2->x >= INF && p2->y >= INF) {
        p3.x = p1->x;
        p3.y = p1->y;
        return p3;
    }

    // x₃ = m² - x₁ - x₂ (mod p)
    p3.x = mod(power(em, 2) - p1->x - p2->x, p);

    // y₃ = m(x₁ - x₃) - y₁ (mod p)
    p3.y = mod(em*(p1->x - p3.x) - p1->y, p);

    return p3;
}

// Returns point on elliptic curve multiplied by scalar n
struct Point * nP(struct Point *G, int64_t n, int64_t a, int64_t p) {
    struct Point *p3 = malloc(sizeof(struct Point));
    *p3 = add(G, G, a, p);

    for (int i = 1; i < n - 1; i++)
        *p3 = add(G, p3, a, p);

    return p3;
}

// Test cases from textbook
void testHarness() {
    /* 
     * Test Case 1: add two points on elliptic curve
     */

    // E: y² = x³ + 2x + 3 (mod 5)
    int64_t a = 2, p = 5;

    // Point (2, 7)
    struct Point *G = malloc(sizeof(struct Point));
    G->x = 2, G->y = 7;

    assert(equal(G, G) == 1);

    // P1 = (1, 4), P2 = (3, 1)
    struct Point *p1 = malloc(sizeof(struct Point));
    struct Point *p2 = malloc(sizeof(struct Point));
    p1->x = 1, p1->y = 4;
    p2->x = 3, p2->y = 1;

    assert(m(p1, p2, a, p) == 1);

    struct Point p3 = add(p1, p2, a, p);
    assert(p3.x == 2 && p3.y == 0);

    /* 
     * Test Case 2: Diffie Hellman key exchange
     */

    // Alice and Bob's secret multipliers
    int64_t multA = 15, multB = 22;

    // E: y² = x³ + 11x + 19 (mod 5)
    a = 11, p = 167;

    // Compute values for transmission
    struct Point *secretA = nP(G, multA, a, p);
    struct Point *secretB = nP(G, multB, a, p); 
    assert(secretA->x == 102 && secretA->y == 88);
    assert(secretB->x == 9 && secretB->y == 43);

    // Compute shared secret
    struct Point *sharedA = nP(secretB, multA, a, p);
    struct Point *sharedB = nP(secretA, multB, a, p);
    assert(sharedA->x == 131 && sharedA->y == 140);
    assert(equal(sharedA, sharedB));

    free(G);
    free(p1);
    free(p2);
    free(secretA);
    free(secretB);
    free(sharedA);
    free(sharedB);

    printf("INFO: all tests passed.\n");
}

// Establish shared secret using Diffie Hellman exchange
void ecdh(struct Point *G, int64_t a, int64_t p, int64_t multA, int64_t multB) {
    // Compute values for transmission
    struct Point *secretA = nP(G, multA, a, p);
    struct Point *secretB = nP(G, multB, a, p);
    printf("Alice sends: (%ld, %ld)\n", secretA->x, secretA->y);
    printf("  Bob sends: (%ld, %ld)\n", secretB->x, secretB->y);

    // Compute shared secret
    struct Point *sharedA = nP(secretB, multA, a, p);
    struct Point *sharedB = nP(secretA, multB, a, p);
    printf("Alice computes shared key: (%ld, %ld)\n", sharedA->x, sharedA->y);
    printf("  Bob computes shared key: (%ld, %ld)\n", sharedB->x, sharedB->y);

    if (equal(sharedA, sharedB))
        printf("Shared key established!\n");
    else
        printf("Something went wrong!\n");

    free(secretA);
    free(secretB);
    free(sharedA);
    free(sharedB);
}

// Program driver
int main(int argc, char *argv[]) {
    about();
    testHarness();

    // E: y² = x³ + 11x + 19 (mod 5)
    int64_t a = 11, p = 167;

    // Point (2, 7)
    struct Point *G = malloc(sizeof(struct Point));
    G->x = 2, G->y = 7;

    // Alice and Bob's secret multipliers
    int64_t multA = 12, multB = 31;

    // Establish shared secret
    ecdh(G, a, p, multA, multB);

    free(G);
    return 0;
}