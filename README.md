## Parallel random number generator

# Project goal
The goal of the project is to create a random number generator using the Linear
Congruential Generator (LCG) algorithm, which can be used in parallel to create very large
sets of random numbers quickly. These sets of numbers can then be used for any high-
demand applications which require randomness

# Expected outcome
The expected outcome is a random number generator which hopefully improves the
performance and increases the scalability of large-scale applications. Outcome can
easily be tested by running Monte Carlo simulations of varying size, using both
sequential and parallel generation of numbers and comparing the results. Simulations
making use of parallel generation should perform more efficiently than the simulations
using sequential generation.

## Linear Congruential Generator algorithm

# Parameter choice
The 3 most commonly used schools of parameter choices for LCG are (m prime, c = 0), (m a power of 2, c = 0) and (m a power of 2, c != 0).
While (m a power of 2, c = 0) is a common choice because of its efficiency, I chose to go with the slower but more high quality randomness
providing (m prime, c = 0). A less efficient algorithm showcases the benefits of parallel programming better, and for some applications quality 
is more important than speed.

I chose the specific values for the parameter semi-randomly, choosing a set of values from "Table 3. LCGs with good figures of merit and a(m − 1) < 2^53" (https://www.ams.org/journals/mcom/1999-68-225/S0025-5718-99-00996-5/S0025-5718-99-00996-5.pdf). 
The chosen values are:
**m** = 34359738337 (2^35 - 31)
**a** = 258524
**c** = 0
**seed** = Chosen by built-in random number generator

# Results table
### Results table
| Test Case | Numbers generated      | Sequential generation (seconds) | 4 Parallel threads (seconds) | 8 Parallel threads (seconds) | Speedup 4 threads | Speedup 8 threads |
|-----------|------------------------|-----------------------|--------------------|--------------------|-------------------|-------------------|
| 0         | 100 000 000            | 0.003005              | 0.002285           | 0.0015555          | 1.31509x          | 1.93185x          |
| 1         | 1 000 000 000          | 0.0302723             | 0.013881           | 0.0100172          | 2.1808×           | 3.02203×          |
| 2         | 2 500 000 000          | 0.0716702             | 0.0338124          | 0.0270869          | 2.119642x         | 2.64593x          |
| 3         | 5 000 000 000          | 0.117796              | 0.0656713          | 0.0500011          | 1.79372x          | 2.35586x          |
| 4         | 10 000 000 000         | 0.20927               | 0.121689           | 0.0939494          | 1.71971x          | 2.22747x          |
| 5         | 100 000 000 000        | 2.133                 | 0.901345           | 0.754522           | 2.36646x          | 2.82695x          |
| 6         | 1 000 000 000 000      | 20.5079               | 9.37974            | 7.37208            | 2.186403x         | 2.78183x          |
