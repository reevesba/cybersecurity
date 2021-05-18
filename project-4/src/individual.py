''' Individual Class

Author: Bradley Reeves
Date:   05/17/2021

'''

from fitness import Fitness
from typing import List, TypeVar
from sklearn.utils import shuffle
from string import digits
from random import choice

# Custom types
Individual = TypeVar("Individual")

class Individual:
    def __init__(self: Individual, length: int, values: List, parent_a: Individual, parent_b: Individual) -> None:
        ''' Initialize Individual instance
            Parameters
            ----------
            self : Individual instance
            length : Individual length
            values : Individual values
            parent_a : Individual's first parent
            parent_b : Individual's second parent

            Returns
            -------
            None
        '''
        self.length = length
        if values: self.values = values
        else: self.values = self.__random_Individual()
        self.parent_a = parent_a
        self.parent_b = parent_b
        self.fitness_function = Fitness(self.length)
        self.fitness = self.fitness_function.fitness(self.values)
        
    def __random_Individual(self: Individual) -> List:
        ''' Generate random Individual values
            Parameters
            ----------
            self : Individual instance

            Returns
            -------
            Random Individual values
        '''
        return shuffle([choice(digits) for i in range(self.length)])

    def get_values(self: Individual) -> List:
        ''' Return Individual values
            Parameters
            ----------
            self : Individual instance

            Returns
            -------
            Individual values
        '''
        return self.values

    def get_parent_a(self: Individual) -> Individual:
        ''' Return Individual's first parent
            Parameters
            ----------
            self : Individual instance

            Returns
            -------
            Individual's first parent
        '''
        return self.parent1
    
    def get_parent_b(self: Individual) -> Individual:
        ''' Return Individual's second parent
            Parameters
            ----------
            self : Individual instance

            Returns
            -------
            Individual's second parent
        '''
        return self.parent2

    def get_fitness(self: Individual) -> int:
        ''' Return Individual's fitness score
            Parameters
            ----------
            self : Individual instance

            Returns
            -------
            Individual's fitness
        '''
        return self.fitness