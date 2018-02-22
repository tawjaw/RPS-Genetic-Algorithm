# Coevolution of Rock-Paper-Scissor Players
The idea of evolutionary algorithms is inspired from nature
and the emergence of life on Earth. There are many different
variations and designs of EAs, but the concept stays the same.
In any population of individuals within some environment,
competition for survival occurs (survivor of the fittest). The
higher the fitness of an individual the higher the chance of its
selection to survive by nature. The process in which an
evolutionary algorithm works is as follows: given a population
of individuals: 
1. evaluate the fitness of all individuals in the
population
2. select parents from the population to 
3. generate the offspring of individuals using mutation and crossover, and
finally 
4. select from the new generated offspring the next
population based on their fitness (survivor of the fittest)
## Individual
Every individual contains a set of RPS rules. These rules
allow the individual to decide what move to play at a certain
round depending on the history of the game. A rule is defined
as follows: 
```
<conditions>:<action>
```
For an individual to play
the move in the  `<action>`, the conditions of this rule must be
satisfied.
A condition is any two possible moves played by both
players; `RP, RR, RS, PR, PP, PS, SR, SP, SS`. The first move
in the condition (left) is always in the perspective of player one
and the second move (right) is in the perspective of player two.
However, one condition can also include multiple conditions.
For example, a condition can be `RP or PP or SR`.
An example of a rule: 
```RS (RR or SS): R```
If in the previous round first player played `R` and second
player played `R` or first player played `S` and second player
played `S`, and in the round before that the first player played `R`
and the second player played `S` then the rule is satisfied and the
individual can play `R`.

Because an individual contains a set of rules then multiple
rules can be satisfied at once. To choose which rule’s action to
be played, a score scale is introduced to give a score to a rule
based on its accuracy. The more ORs in a condition there is the
less the score is. However, if none of the rules of an individual is satisfied, then the individual plays the last move it played.
For example, the condition `RR or SS or RS or PS` has a score of 5, but a condition of `RR` has a score of 9. The score of a rule is the sum of all the scores of the conditions in a rule. If multiple rules are satisfied the rule with the highest score will determine the individual’s action (move to be played by this individual).

## Fitness
Every individual starts with a fitness of `0.5 + noise`; where noise is between -0.05 and 0.05. the fitness of an individual determines how well this individual is playing compared to the rest of population. After every round of the game the fitness of all individuals are updated using a reward.
```Fitness = fitness*(1 – alpha) + reward*alpha```
Alpha is a number between 0 and 1. If the individual wins the round then the reward is +1, if it loses then the reward is -1 and if a draw occurs the reward is 0.

## Coevolution
Coevolution is a competitive environment of two evolving populations competing against each other. Every population will try to win against the other, and every time this happens the other population will evolve to counter the winning of the other one. The fitness of every population is determined by the other population. This scenario is found in nature where species effect other species in determining the fitness of an organism.
Using coevolution to evolve two populations playing rock paper scissor has shown interesting results. As both populations are adapting and changing their game strategies to win against the other. Whenever a population wins the most over a certain amount of rounds it is expected to lose the most over a certain amount of rounds after that (the graphs in the [report](RPSPaper.pdf "report") shows that).

