""" GA

This code is selected and adapted from the aima-python code repository.  
Specifically, functions and examples from the search.py and search.ipynb related
to genetic algorithms are presented here. 

The example problem considered is the generation of a target phrase from 
population of random strings. 
"""

import random
import bisect
from utils import (
    is_in, argmin, argmax, argmax_random_tie, probability, weighted_sampler,
    memoize, print_table, open_data, Stack, FIFOQueue, PriorityQueue, name,
    distance, vector_add
)


# the target phrase to be generated
target = '4811 + AI +GAs = fun!'


# define the possible characters in the gene pool 
ucase = [chr(x) for x in range(65,91)]
lcase = [chr(x) for x in range(97,123)]
digits = [chr(x) for x in range(48,58)]

gene_pool = [] 
gene_pool.extend(ucase)  # add uppercase letters to pool
gene_pool.extend(lcase)  # add lowercase letters to pool
gene_pool.extend(digits) # add numbers to pool
gene_pool.append(' ')    # add punctuation to gene pool 
gene_pool.append('!')
gene_pool.append('.')
gene_pool.append('+')
gene_pool.append('-')
gene_pool.append(',')
gene_pool.append('?')


# DEFAULT PARAMETERS 
# *************************************
#  You will modify these in Question 2
# *************************************
max_population = 100 
mutation_rate = 0.07    # 7% 
ngen = 1000 
f_thres = len(target)   # the alg. terminates when the target phrase is found or ngen is hit


def fitness_fn(sample):
    fitness = 0
    for i in range(len(sample)):
        if sample[i] == target[i]:
            fitness += 1
    return fitness


# Functions defining the basic genetic algorithm operation: 
def init_population(pop_number, gene_pool, state_length):
    """Initializes population for genetic algorithm
    pop_number  :  Number of individuals in population
    gene_pool   :  List of possible values for individuals
    state_length:  The length of each individual"""
    g = len(gene_pool)
    population = []
    for i in range(pop_number):
        new_individual = [gene_pool[random.randrange(0, g)] for j in range(state_length)]
        population.append(new_individual)

    return population

def select(r, population, fitness_fn):
    fitnesses = map(fitness_fn, population)
    sampler = weighted_sampler(population, fitnesses)
    return [sampler() for i in range(r)]


def recombine(x, y):
    n = len(x)
    c = random.randrange(0, n)
    return x[:c] + y[c:]


def recombine_uniform(x, y):
    n = len(x)
    result = [0] * n;
    indexes = random.sample(range(n), n)
    for i in range(n):
        ix = indexes[i]
        result[ix] = x[ix] if i < n / 2 else y[ix]
    try:
        return ''.join(result)
    except:
        return result
        

def mutate(x, gene_pool, pmut):
    if random.uniform(0, 1) >= pmut:
        return x

    n = len(x)
    g = len(gene_pool)
    c = random.randrange(0, n)
    r = random.randrange(0, g)

    new_gene = gene_pool[r]
    return x[:c] + [new_gene] + x[c+1:]


def fitness_threshold(fitness_fn, f_thres, population):
    if not f_thres:
        return None

    fittest_individual = argmax(population, key=fitness_fn)
    if fitness_fn(fittest_individual) >= f_thres:
        return fittest_individual

    return None


# ---------------------------------------------------------------------
def genetic_algorithm_stepwise(population, fitness_fn, gene_pool=[0, 1], f_thres=None, 
    ngen=1000, pmut=0.07, mute=False):
    for generation in range(ngen):
        population = [mutate(recombine(*select(2, population, fitness_fn)), gene_pool, pmut) for i in range(len(population))]
        # stores the individual genome with the highest fitness in the current population
        current_best = ''.join(max(population, key=fitness_fn))
        #print('Current best: {current_best}\t\tGeneration: {str(generation)}\t\tFitness: {fitness_fn(current_best)}\r', end='')
        if (generation % 50 == 0) & (mute==False):
            print('Current best: %20s\tGeneration %d\tFitness: %d' \
             % (current_best, generation, fitness_fn(current_best)))
        
        # compare the fitness of the current best individual to f_thres
        fittest_individual = fitness_threshold(fitness_fn, f_thres, population)
        
        # if fitness is greater than or equal to f_thres, we terminate the algorithm
        if fittest_individual:
            print('Final2:        %20s\tGeneration %d\tFitness: %d' 
                % (current_best, generation, fitness_fn(current_best)))
            return fittest_individual, f_thres, generation
    print('Final:        %20s\tGeneration %d\tFitness: %d' 
        % (current_best, generation, fitness_fn(current_best)))
    return max(population, key=fitness_fn) , fitness_fn(max(population, key=fitness_fn)),  generation


