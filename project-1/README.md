# Project 1


1. Implement the A5/1 algorithm. Suppose that, after a particular step, the values in the registers are

        X = (x₀, x₁, ..., x₁₈) = (1010101010101010101)
        Y = (y₀, y₁, ..., y₂₁) = (1100110011001100110011)
        Z = (z₀, z₁, ..., z₂₂) = (11100001111000011110000)

    List the next 32 keystream bits and give the contents of X, Y, and Z after these 32 bits have been generated. 

    A. 
    ![A5/1 Output](img/a51-out.PNG?raw=true "Title")

    [View Source Code](a51/src/a51.c)


2.	Implement the Tiny Encryption Algorithm (TEA). Use your TEA algorithm to encrypt the 64-bit plaintext block

        0x0123456789ABCDEF

    using the 128-bit key

        0xA56BABCD00000000FFFFFFFFABCDEF01

    Decrypt the resulting ciphertext and verify that you obtain the original plaintext. The prefix 0x means hexadecimal integer.

    A.
    ![TEA Output](img/tea-out.PNG?raw=true "Title")
    
    [View Source Code](tea/src)

