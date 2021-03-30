# Project 0

1.	Edgar Allan Poe's 1843 short story, The Gold Bug features a cryptanalytic attack.

        a. What type of cipher is broken and how?
        b. What happens as a result of this cryptanalytic success?

    A. The cipher that was broken is a symmetric simple substitution cipher. It was broken by first determing the language likely used. With some context about the ciphertext, it was assumed to be in english. The next step was to create a character frequency table using the ciphertext. Armed with statistical knowledge of the english language, the cipher is easily broken. For example, the character '8' appears most in the ciphertext. The character 'e' is the most common in the english language so there is a starting place. All '8's in the cipher text can be substituted with 'e's. Finally, words can be formed ('the' for example). As more context is uncovered, the key is eventually established and the ciphertext is translated to plaintext. 
    
    As a result of the cryptanalytic success, the character is able to ascertain the location of buried treasure. Eventually, human bodies are found in the hole. 


2.	Given that simple substitution with a shift was used, find the plaintext and the shift that corresponds to the following ciphertext:
CSYEVIXIVQMREXIH

    A. Using exhaustive key search:

        n = 0 =  CSYEVIXIVQMREXIH
        n = 1 =  DTZFWJYJWRNSFYJI
        n = 2 =  EUAGXKZKXSOTGZKJ
        n = 3 =  FVBHYLALYTPUHALK
        n = 4 =  GWCIZMBMZUQVIBML
        n = 5 =  HXDJANCNAVRWJCNM
        n = 6 =  IYEKBODOBWSXKDON
        n = 7 =  JZFLCPEPCXTYLEPO
        n = 8 =  KAGMDQFQDYUZMFQP
        n = 9 =  LBHNERGREZVANGRQ
        n = 10 = MCIOFSHSFAWBOHSR
        n = 11 = NDJPGTITGBXCPITS
        n = 12 = OEKQHUJUHCYDQJUT
        n = 13 = PFLRIVKVIDZERKVU
        n = 14 = QGMSJWLWJEAFSLWV
        n = 15 = RHNTKXMXKFBGTMXW
        n = 16 = SIOULYNYLGCHUNYX
        n = 17 = TJPVMZOZMHDIVOZY
        n = 18 = UKQWNAPANIEJWPAZ
        n = 19 = VLRXOBQBOJFKXQBA
        n = 20 = WMSYPCRCPKGLYRCB
        n = 21 = XNTZQDSDQLHMZSDC
        n = 22 = YOUARETERMINATED
        n = 23 = ZPVBSF...
        n = 24 = AQWCTG...
        n = 25 = BRXDUH...
        n = 26 = CSYEVI...

    The partial string at n = 26 shows that we didn't mess up while rotating the characters. Of all the 'plaintext' strings, the string at n = 22 seems to make the most sense.
    
    Given that they key is 22, the ciphertext reads YOUARETERMINATED in plaintext. 

3.	Write a program to help an analyst decrypt a simple substitution cipher. Your program should take the ciphertext as input, compute letter frequency counts, and display these for the analyst. The program should then allow the analyst to guess a key and display the results of the corresponding "decryption" with the putative key.

    A. [View Source Code](sub-decrypt.py)


4.	Use the program to determine the plaintext and key for the ciphertext that appears in the following Alice in Wonderland quote: 

        MXDXBVTZWVMXNSPBQXLIMSCCSGXSCJXBOVQXCJZMOJZCVCTVWJCZAAXZBCSSCJXBQCJZCOJZCNSPOXBXSBTVWJCJZDXGXXMOZQMSCSCJXBOVQXCJZMOJZCNSPJZHGXXMOSPLHJZDXZAAXZBXHCSCJXTCSGXSCJXBOVQX

    The message was encrypted with a simple substitution cipher and the plaintext has no spaces or punctuation.

    A. Character Counts: {'X': 25, 'C': 21, 'J': 16, 'Z': 15, 'S': 15, 'B': 10, 'O': 9, 'M': 8, 'V': 8, 'Q': 6, 'T': 4, 'P': 4, 'G': 4, 'A': 4, 'D': 3, 'W': 3, 'N': 3, 'H': 3, 'L': 2, 'I': 1}

    Result: neverimagineyourselfnottobeotherwisethanwhatitmightappeartoothersthatwhatyouwereormighthavebeenwasnototherwisethanwhatyouhadbeenwouldhaveappearedtothemtobeotherwise

    Key:
    prtvxjbdfhklnywusqomzigeca

    Note: other keys may be possible. We need additional encrypted messages to test other letters of the alphabet. 


5.	Decrypt the ciphertext:

        IAUTMDCSMNIMREBOTNELSTRHEREOAEVMWIH
        TSEEATMAEOHWHSYCEELTTEOHMUOUFEHTRFT


    This message was encrypted with a double transposition (of the type discussed in the text) using a matrix of 7 rows and 10 columns.

    Hint: The first word is "there." Put the ciphertext in a 7 x 10 array. Then the letters of "there" will all appear (in scrambled order) in one row. This gives a start on the column permutation. Once the column perms are known, the row perms are easily determined.

    A. 

    ## Original Array
    | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 |
    | - | - | - | - | - | - | - | - | - | - |
    | I | A | U | T | M | D | C | S | M | N |
    | I | M | R | E | B | O | T | N | E | L |
    | S | T | R | H | E | R | E | O | A | E |
    | V | M | W | I | H | T | S | E | E | A |
    | T | M | A | E | O | H | W | H | S | Y |
    | C | E | E | L | T | T | E | O | H | M |
    | U | O | U | F | E | H | T | R | F | T |

    ## Column Permutations

    ### original col --> new col

    ### C2 --> C1

    | 2 | - | - | - | - | - | - | - | - | - |
    | - | - | - | - | - | - | - | - | - | - |
    | A | I | U | T | M | D | C | S | M | N |
    | M | I | R | E | B | O | T | N | E | L |
    | T | S | R | H | E | R | E | O | A | E |
    | M | V | W | I | H | T | S | E | E | A |
    | M | T | A | E | O | H | W | H | S | Y |
    | E | C | E | L | T | T | E | O | H | M |
    | O | U | U | F | E | H | T | R | F | T |

    ### C4 --> C2

    | 2 | 4 | - | - | - | - | - | - | - | - |
    | - | - | - | - | - | - | - | - | - | - | 
    | A | T | I | U | M | D | C | S | M | N |
    | M | E | I | R | B | O | T | N | E | L |
    | T | H | S | R | E | R | E | O | A | E |
    | M | I | V | W | H | T | S | E | E | A |
    | M | E | T | A | O | H | W | H | S | Y |
    | E | L | C | E | T | T | E | O | H | M |
    | O | F | U | U | E | H | T | R | F | T |

    ### C7 --> C3

    | 2 | 4 | 7 | - | - | - | - | - | - | - |
    | - | - | - | - | - | - | - | - | - | - | 
    | A | T | C | I | U | M | D | S | M | N |
    | M | E | T | I | R | B | O | N | E | L |
    | T | H | E | S | R | E | R | O | A | E |
    | M | I | S | V | W | H | T | E | E | A |
    | M | E | W | T | A | O | H | H | S | Y |
    | E | L | E | C | E | T | T | O | H | M |
    | O | F | T | U | U | E | H | R | F | T |

    ### C6 --> C4

    | 2 | 4 | 7 | 6 | - | - | - | - | - | - |
    | - | - | - | - | - | - | - | - | - | - | 
    | A | T | C | D | I | U | M | S | M | N |
    | M | E | T | O | I | R | B | N | E | L |
    | T | H | E | R | S | R | E | O | A | E |
    | M | I | S | T | V | W | H | E | E | A |
    | M | E | W | H | T | A | O | H | S | Y |
    | E | L | E | T | C | E | T | O | H | M |
    | O | F | T | H | U | U | E | R | F | T |

    ### C5 --> C5

    | 2 | 4 | 7 | 6 | 5 | - | - | - | - | - |
    | - | - | - | - | - | - | - | - | - | - | 
    | A | T | C | D | M | I | U | S | M | N |
    | M | E | T | O | B | I | R | N | E | L |
    | T | H | E | R | E | S | R | O | A | E |
    | M | I | S | T | H | V | W | E | E | A |
    | M | E | W | H | O | T | A | H | S | Y |
    | E | L | E | T | T | C | E | O | H | M |
    | O | F | T | H | E | U | U | R | F | T |

    ### C9 --> C6

    | 2 | 4 | 7 | 6 | 5 | 9 | - | - | - | - |
    | - | - | - | - | - | - | - | - | - | - | 
    | A | T | C | D | M | M | I | U | S | N |
    | M | E | T | O | B | E | I | R | N | L |
    | T | H | E | R | E | A | S | R | O | E |
    | M | I | S | T | H | E | V | W | E | A |
    | M | E | W | H | O | S | T | A | H | Y |
    | E | L | E | T | T | H | C | E | O | M |
    | O | F | T | H | E | F | U | U | R | T |

    ### C3 --> C7

    | 2 | 4 | 7 | 6 | 5 | 9 | 3 | - | - | - |
    | - | - | - | - | - | - | - | - | - | - | 
    | A | T | C | D | M | M | U | I | S | N |
    | M | E | T | O | B | E | R | I | N | L |
    | T | H | E | R | E | A | R | S | O | E |
    | M | I | S | T | H | E | W | V | E | A |
    | M | E | W | H | O | S | A | T | H | Y |
    | E | L | E | T | T | H | E | C | O | M |
    | O | F | T | H | E | F | U | U | R | T |

    ### C10 --> C8

    | 2 | 4 | 7 | 6 | 5 | 9 | 3 | 10 | - | - |
    | - | - | - | - | - | - | - | - | - | - | 
    | A | T | C | D | M | M | U | N | I | S |
    | M | E | T | O | B | E | R | L | I | N |
    | T | H | E | R | E | A | R | E | S | O |
    | M | I | S | T | H | E | W | A | V | E |
    | M | E | W | H | O | S | A | Y | T | H |
    | E | L | E | T | T | H | E | M | C | O |
    | O | F | T | H | E | F | U | T | U | R |

    ### C1 --> C9

    | 2 | 4 | 7 | 6 | 5 | 9 | 3 | 10 | 1 | - |
    | - | - | - | - | - | - | - | - | - | - | 
    | A | T | C | D | M | M | U | N | I | S |
    | M | E | T | O | B | E | R | L | I | N |
    | T | H | E | R | E | A | R | E | S | O |
    | M | I | S | T | H | E | W | A | V | E |
    | M | E | W | H | O | S | A | Y | T | H |
    | E | L | E | T | T | H | E | M | C | O |
    | O | F | T | H | E | F | U | T | U | R |

    ### C8 --> C10

    | 2 | 4 | 7 | 6 | 5 | 9 | 3 | 10 | 1 | 8 |
    | - | - | - | - | - | - | - | - | - | - | 
    | A | T | C | D | M | M | U | N | I | S |
    | M | E | T | O | B | E | R | L | I | N |
    | T | H | E | R | E | A | R | E | S | O |
    | M | I | S | T | H | E | W | A | V | E |
    | M | E | W | H | O | S | A | Y | T | H |
    | E | L | E | T | T | H | E | M | C | O |
    | O | F | T | H | E | F | U | T | U | R |

    ### Column Permutation is [2, 4, 7, 6, 5, 9, 3, 10, 1, 8]

    ## Row Permutations

    ### original row --> new row

    | - | 2 | 4 | 7 | 6 | 5 | 9 | 3 | 10 | 1 | 8 |
    | - | - | - | - | - | - | - | - | - | - | - | 
    | 1 | A | T | C | D | M | M | U | N | I | S |
    | 2 | M | E | T | O | B | E | R | L | I | N |
    | 3 | T | H | E | R | E | A | R | E | S | O |
    | 4 | M | I | S | T | H | E | W | A | V | E |
    | 5 | M | E | W | H | O | S | A | Y | T | H |
    | 6 | E | L | E | T | T | H | E | M | C | O |
    | 7 | O | F | T | H | E | F | U | T | U | R |

    ### R3 --> R1

    | - | 2 | 4 | 7 | 6 | 5 | 9 | 3 | 10 | 1 | 8 |
    | - | - | - | - | - | - | - | - | - | - | - | 
    | 3 | T | H | E | R | E | A | R | E | S | O |
    | - | A | T | C | D | M | M | U | N | I | S |
    | - | M | E | T | O | B | E | R | L | I | N |
    | - | M | I | S | T | H | E | W | A | V | E |
    | - | M | E | W | H | O | S | A | Y | T | H |
    | - | E | L | E | T | T | H | E | M | C | O |
    | - | O | F | T | H | E | F | U | T | U | R |

    ### R5 --> R2

    | - | 2 | 4 | 7 | 6 | 5 | 9 | 3 | 10 | 1 | 8 |
    | - | - | - | - | - | - | - | - | - | - | - | 
    | 3 | T | H | E | R | E | A | R | E | S | O |
    | 5 | M | E | W | H | O | S | A | Y | T | H |
    | - | A | T | C | D | M | M | U | N | I | S |
    | - | M | E | T | O | B | E | R | L | I | N |
    | - | M | I | S | T | H | E | W | A | V | E |
    | - | E | L | E | T | T | H | E | M | C | O |
    | - | O | F | T | H | E | F | U | T | U | R |

    ### R1 --> R3

    | - | 2 | 4 | 7 | 6 | 5 | 9 | 3 | 10 | 1 | 8 |
    | - | - | - | - | - | - | - | - | - | - | - | 
    | 3 | T | H | E | R | E | A | R | E | S | O |
    | 5 | M | E | W | H | O | S | A | Y | T | H |
    | 1 | A | T | C | D | M | M | U | N | I | S |
    | - | M | E | T | O | B | E | R | L | I | N |
    | - | M | I | S | T | H | E | W | A | V | E |
    | - | E | L | E | T | T | H | E | M | C | O |
    | - | O | F | T | H | E | F | U | T | U | R |

    ### R4 --> R4

    | - | 2 | 4 | 7 | 6 | 5 | 9 | 3 | 10 | 1 | 8 |
    | - | - | - | - | - | - | - | - | - | - | - | 
    | 3 | T | H | E | R | E | A | R | E | S | O |
    | 5 | M | E | W | H | O | S | A | Y | T | H |
    | 1 | A | T | C | D | M | M | U | N | I | S |
    | 4 | M | I | S | T | H | E | W | A | V | E |
    | - | M | E | T | O | B | E | R | L | I | N |
    | - | E | L | E | T | T | H | E | M | C | O |
    | - | O | F | T | H | E | F | U | T | U | R |

    ### R7 --> R5

    | - | 2 | 4 | 7 | 6 | 5 | 9 | 3 | 10 | 1 | 8 |
    | - | - | - | - | - | - | - | - | - | - | - | 
    | 3 | T | H | E | R | E | A | R | E | S | O |
    | 5 | M | E | W | H | O | S | A | Y | T | H |
    | 1 | A | T | C | D | M | M | U | N | I | S |
    | 4 | M | I | S | T | H | E | W | A | V | E |
    | 7 | O | F | T | H | E | F | U | T | U | R |
    | - | M | E | T | O | B | E | R | L | I | N |
    | - | E | L | E | T | T | H | E | M | C | O |

    ### R6 --> R6

    | - | 2 | 4 | 7 | 6 | 5 | 9 | 3 | 10 | 1 | 8 |
    | - | - | - | - | - | - | - | - | - | - | - | 
    | 3 | T | H | E | R | E | A | R | E | S | O |
    | 5 | M | E | W | H | O | S | A | Y | T | H |
    | 1 | A | T | C | D | M | M | U | N | I | S |
    | 4 | M | I | S | T | H | E | W | A | V | E |
    | 7 | O | F | T | H | E | F | U | T | U | R |
    | 6 | E | L | E | T | T | H | E | M | C | O |
    | - | M | E | T | O | B | E | R | L | I | N |

    ### R2 --> R7

    | - | 2 | 4 | 7 | 6 | 5 | 9 | 3 | 10 | 1 | 8 |
    | - | - | - | - | - | - | - | - | - | - | - | 
    | 3 | T | H | E | R | E | A | R | E | S | O |
    | 5 | M | E | W | H | O | S | A | Y | T | H |
    | 1 | A | T | C | D | M | M | U | N | I | S |
    | 4 | M | I | S | T | H | E | W | A | V | E |
    | 7 | O | F | T | H | E | F | U | T | U | R |
    | 6 | E | L | E | T | T | H | E | M | C | O |
    | 2 | M | E | T | O | B | E | R | L | I | N |

    ### Row Permutation is [3, 5, 1, 4, 7, 6, 2]

    ### "There are some who say that cdmmunism is the wave of the future. Let them come to Berlin."


