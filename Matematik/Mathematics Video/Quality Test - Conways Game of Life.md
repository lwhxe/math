This part is for testing the quality of the videos I could theoretically produce.

@Scene 1

Conways game of life, is not a game. Not the type of game you are used to at least. It's game, where there is no player in sight. All that exists is a grid of boxes, that have 2 states. Either alive or dead.

@Scene 2

The rules are simple:
An alive box dies if it has less than 2 or more than 3 alive neighboring boxes.
And a dead square turns alive if it has exactly 3 alive neighboring boxes.
So if $x$ is the amount of alive neighbors, $a$ is the state of the box, and $a'$ is the next state of the box.
$a' = \begin{cases} 1 & \text{if } (a = 1 \land x \in \{2, 3\}) \lor (a = 0 \land x = 3) \\ 0 & \text{otherwise} \end{cases}$
