''' Crossover Class

Author: Bradley Reeves
Date:   05/17/2021

'''

from numpy import random
from typing import List, TypeVar

# Custom types
Individual = TypeVar("Individual")
Crossover = TypeVar("Crossover")

class Crossover:
    def __init__(self: Crossover, length: int) -> None:
        ''' Initialize Crossover instance
            Parameters
            ----------
            self : Crossover instance
            length : Length of Individual

            Returns
            -------
            None
        '''
        self.length = length

    def __do_xover(self: Crossover, parents: List) -> List:
        ''' Cross two inversion sequences
            Parameters
            ----------
            self : Crossover instance
            parent_a : First parent
            parent_b : Second parent

            Returns
            -------
            child_values : New child values
        '''
        xover_point = random.randint(0, self.length)

        child_values = []
        for i in range(self.length):
            if i <= xover_point: child_values.append(parents[0].get_values()[i])
            else: child_values.append(parents[1].get_values()[i])
        return child_values

    def xover(self: Crossover, parents: List) -> List:
        ''' Single point crossover
            ----------
            self : Crossover instance
            parents : Parents to crossover

            Returns
            -------
            New children
        '''
        # Return children
        return [self.__do_xover(parents), self.__do_xover(parents)]