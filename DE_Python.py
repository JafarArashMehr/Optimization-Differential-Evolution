import random
import numpy as np

def urand():
    return random.random()


def func(X):

    #print ("aaa")
    return pow(X[0],3)+pow(X[1],3)

up_bound = [3,3]
low_bound = [-3,-3]

dim= 2
NP = 10
cr = 0.90  # crossover probability
F5 = 0.50  # Scaling factor

Iteration_Number=20

parent_start = []
parent_val_start = []

def start():

    for j in range(NP):
        x = []
        for k in range (dim):
            x.append(random.uniform(low_bound[k],up_bound[k]))
        parent_start.append(x)
        parent_val_start.append(func(x))

start()


all_ind = []
for j in range (len(parent_start)):
    all_ind.append(j)

def DE():

    generation = 0
    iteration = []
    param1 = []
    param2 = []
    cost_func = []

    for z in range(0, Iteration_Number):

        generation=generation+1

        for i in range (len(parent_start)):

            trials = []

            p1 = random.choice([e for k,e in zip(all_ind,all_ind) if k != i])
            p2 = random.choice([e for k,e in zip(all_ind,all_ind) if k != i and k != p1])
            p_target = random.choice([e for k,e in zip(all_ind,all_ind) if k != i and k != p1 and k != p2])

            for k in range(0, dim):
                if urand() <= cr:
                    trials.append((parent_start[p_target])[k] + F5 * ((parent_start[p1])[k] - (parent_start[p2])[k]))
                else:
                    trials.append((parent_start[i])[k])

            for s in range(dim):

                if trials[s] > up_bound[s]:
                    trials[s]=up_bound[s]
                elif trials[s] < low_bound[s]:
                    trials[s]=low_bound[s]
                elif low_bound[s] <= trials[s] <= up_bound[s]:
                    trials[s]=trials[s]

            child_val = func(trials)

            if child_val <= parent_val_start[i]:
                parent_start[i] = trials
                parent_val_start[i] = child_val

        soretd_val = sorted(parent_val_start,reverse=False)
        ind = parent_val_start.index(soretd_val[0])

        iteration.append(generation)
        param1.append(parent_start[ind][0])
        param2.append(parent_start[ind][1])
        cost_func.append(soretd_val[0])

    col_format = "{:<30}" * 4 + "\n"
    with open("RESULTS-Python.txt", 'w') as of:
        for x in zip(iteration, param1, param2,cost_func):
            of.write(col_format.format(*x))

DE()