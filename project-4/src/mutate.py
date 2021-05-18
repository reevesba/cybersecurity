''' Mutator Class

Author: Bradley Reeves
Date:   05/17/2021

'''

from numpy import random
from typing import List, TypeVar
from string import digits
from random import choice

# Custom types
Mutator = TypeVar("Mutator")

class Mutator:
    def __init__(self: Mutator, length: int, mutation_prob: float) -> None:
        ''' Initialize Mutator instance
            Parameters
            ----------
            self : Mutator instance
            length : Square length
            mutation_prob : Probability of mutation occuring

            Returns
            -------
            None
        '''
        self.length = length
        self.mutation_prob = mutation_prob

    def mutate(self: Mutator, children: List) -> List:
        ''' Possibly mutate children
            Parameters
            ----------
            self : Mutator instance
            children : Mutator candidates

            Returns
            -------
            children : Children with possible mutations
        '''
        for child in children:
            if random.rand() < self.mutation_prob:
                index = random.randint(0, self.length)
                child[index] = choice(digits)
        return children