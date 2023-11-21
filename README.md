The differential evolution is one of the most powerful obtimization algorithms where it optimizes a problem by iteratively trying to improve a candidate solution. This method is capable of searching very large spaces of candidate solutions. This algorithm was  proposed by Storn and Price in 1995. 
This repository is implementation of this algorithm in Python and C++ for an arbitrary 2D problem where we want to minimize the function f(x,y) = $x^3$ + y^3. The defined range of both x and y is [-3,3]. After running the code, the results are saved in a txt file with 4 columns corresponding to the generation number, best value for x, best value for y and the minimum of the function at that generation number. 
The codes could be modified for any function with arbitrary number of dimensions.
