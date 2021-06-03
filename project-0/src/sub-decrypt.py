# About:    Project 0 Questions 3 & 4
# Author:   Bradley Reeves
# Date:     03/27/2021

'''
Potential Improvements:
    1. handle upper-case and foreign characters
    2. handle invalid inputs
    3. handle parial key guesses
'''


def char_counter(ciphertext):
    ''' Counts the frequency of each character in string

        Parameters
        ----------
        ciphertext : string
            Message encrypted with simple substitution

        Returns
        -------
        dict
            Character frequency mapping in descending order
    '''
    counts = {}

    for char in ciphertext:
        counts[char] = counts.get(char, 0) + 1

    return dict(sorted(counts.items(), key=lambda x: x[1], reverse=True))


def build_dict(key_guess):
    ''' Maps the plaintext alphabet to a ciphertext alphabet (key)

        Parameters
        ----------
        key_guess : string
            A ciphertext alphabet (key)

        Returns
        -------
        dict
            Plaintext to ciphertext alphabet mapping
    '''
    plaintext_alphabet = [
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
        'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
        'u', 'v', 'w', 'x', 'y', 'z'
    ]
    return dict(zip(plaintext_alphabet, key_guess))


def decrypt(ciphertext, key_guess):
    ''' Decrypts the ciphertext given a ciphertext alphabet (key)

        Parameters
        ----------
        ciphertext : string
            Message encrypted with simple substitution
        key_guess : string
            A ciphertext alphabet (key)

        Returns
        -------
        string
            Plaintext message
    '''
    conversion_dict = build_dict(key_guess)
    return ''.join(conversion_dict[char] for char in ciphertext)


def main():
    ciphertext = input("Enter Ciphertext: ").lower()

    counts = char_counter(ciphertext)
    print("Character Counts: " + str(counts))

    key_guess = input("Enter Possible Key: ").lower()
    plaintext = decrypt(ciphertext, key_guess)
    print("Result: " + plaintext)


if __name__ == "__main__":
    main()
