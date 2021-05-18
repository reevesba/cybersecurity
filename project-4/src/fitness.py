''' Fitness Calculator Class

Author: Bradley Reeves
Date:   05/17/2021

'''

from numpy import power, abs, sqrt
from typing import List, TypeVar
from subprocess import check_output
from time import process_time

Fitness = TypeVar("Fitness")

class Fitness:
    def __init__(self: Fitness, length: int) -> None:
        ''' Initialize Fitness Instance
            Parameters
            ----------
            self : Fitness instance
            length : Length of flattened square

            Returns
            -------
            None
        '''
        self.length = length

    def fitness(self: Fitness, values: List) -> int:
        ''' Calculate the fitness of the square
            Parameters
            ----------
            self : Fitness instance
            values : List of square values

            Returns
            -------
            Fitness of square
        '''
        test_value = ''.join(values)
        start_time = process_time()
        check_output(["./securityclass.exe " + test_value + "; exit 0"], shell=True)
        return (process_time() - start_time)
        