from snake import Direction

import random

ALL_DIRS = [
    Direction.Up,
    Direction.Down,
    Direction.Left,
    Direction.Right
]

def ai(snake):
    new_dir = random.choice(ALL_DIRS)
    snake.turn(new_dir)
