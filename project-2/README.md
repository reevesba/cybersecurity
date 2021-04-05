# Project 2

1.  Suppose that Alice's RSA public key is (N, e) = (33, 3) and her private key is d = 7.

    a. If Bob encrypts the message M = 19 using Alice's public key, what is the ciphertext C? Show that Alice can decrypt C to obtain M.

            C = Mᵉ mod N = 19³ mod 33 = 6859 mod 33 = 28
            M = cᵈ mod N = 28⁷ mod 33 = 13492928512 mod 33 = 19
    
    b. Let S be the result when Alice digitally signs the message M = 25. What is S? If Bob receives M and S, explain the process Bob will use to verify the signature and show that in this particular case, the signature verification succeeds. 

            S = Mᵈ mod N = 25⁷ mod 33 = 6103515625 mod 33 = 31
            V = Sᵉ mod N = 31³ mod 33 = 29791 mod 33 = 25 = M

            V = M, so verification succeeds.


2.  Consider the knapsack cryptosystem. Suppose the public key consists of (18, 30, 7, 26) and n = 47.

    a. Find the private key, assuming m = 6.

            Find mod inverse using Extended Euclidean Algorithm (yes, it's simple, but I wanted to review):
            Step 1. Find the GCD of 47 and 6.
               47 = 7(6) + 5
                6 = 1(5) + 1
                  = 1

            Step 2. Express 1 as difference between multiples of 47 and 6.
                1 = 6 - 1(5)
                5 = 47 - 7(6)
                
                1 = 6 - 1[47 - 7(6)]
                  = 8(6) - 1(47)
                
            Step 3. Apply mod 47 to both sides
                1 = (8(6) - 1(47)) mod 47
                1 = 8(6) mod 47

            m⁻¹ mod n = 6⁻¹ mod 47 = 8

            x₀ = 18 × 8 mod 47 = 144 mod 47 = 3
            x₁ = 30 × 8 mod 47 = 240 mod 47 = 5
            x₂ =  7 × 8 mod 47 =  56 mod 47 = 9
            x₃ = 26 × 8 mod 47 = 208 mod 47 = 20

            private key = (3, 5, 9, 20)

    b. Encrypt the message M = 1101 (given in binary). Give your result in decimal.

            given (18, 30, 7, 26) and M = 1101, 

            C = 18 + 30 + 26 = 74

3.  Consider the elliptic curve:

        E: y² = x³ + 11x + 19 (mod 167)
    
    a. Verify that the point P = (2, 7) is on E.

            y² = x³ + 11x + 19 mod 167
            7² = 2³ + 11 × 2 + 19 mod 167
            y² = 49 mod 167
            y = 7 mod 167

    b. Suppose this E and P = (2, 7) are used in an ECC Diffie-Hellman key exchange, where Alice chooses the secret value A = 12 and Bob chooses the secret value B = 31. What value does Alice send to Bob? What does Bob send to Alice? What is the shared secret?

    For this problem, write code. Since you will apply the mod operator also on negative numbers, use the following definition:

        a mod b = (a % b + b) % b

    ![TEA Output](img/acdh-out.PNG?raw=true "Title")
    
    [View Source Code](src)



