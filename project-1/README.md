# Project 1


1. Implement the A5/1 algorithm. Suppose that, after a particular step, the values in the registers are

        X = (x<sub>0</sub>, x&#x2081;, ..., x<sub>18</sub>) = (1010101010101010101)
        Y = (y<sub>0</sub>, y<sub>1</sub>, ..., y<sub>21</sub>) = (1100110011001100110011)
        Z = (z<sub>0</sub>, z<sub>1</sub>, ..., z<sub>22</sub>) = (11100001111000011110000)

    List the next 32 keystream bits and give the contents of X, Y, and Z after these 32 bits have been generated. 


2.	Implement the Tiny Encryption Algorithm (TEA). Use your TEA algorithm to encrypt the 64-bit plaintext block

        0x0123456789ABCDEF

    using the 128-bit key

        0xA56BABCD00000000FFFFFFFFABCDEF01

    Decrypt the resulting ciphertext and verify that you obtain the original plaintext. The prefix 0x means hexadecimal integer.

    What to upload in a compressed folder (Canvas): Your code, the results, your conclusions/observations.

    ## Grading criteria (100 points maximum)

    ### Implement the A51 algorithm
    | Criteria | Points |
    | - | - |	
    | Show the output of the next 32 keystream bits | 20 |
    | Show contents/output of X, Y, Z after these 32 bits have been generated |	20 |

    ### Implement the TEA
    | Criteria | Points |
    | - | - | 	
    | Encrypt the given plain text with given key | 20 |
    | Decrypt the cipher text and obtain original text | 20 |

    ### Overall
    | Criteria | Points | 
    | - | - |
    | Correct outputs | 15 |
    | Conclusions and/or Output included | 5 |
