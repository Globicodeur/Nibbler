from snake import Direction, GameOptions, Position

import random

ALL_DIRS = [
    Direction.Up,
    Direction.Down,
    Direction.Left,
    Direction.Right,
]

OPPOSITES = [
    Direction.Down,
    Direction.Up,
    Direction.Right,
    Direction.Left,
]

def ai(snake, others, food, obstacles):
    metrics = dict()
    metrics[Direction.Up] = food.y < snake.head().y
    metrics[Direction.Down] = food.y > snake.head().y
    metrics[Direction.Left] = food.x < snake.head().x
    metrics[Direction.Right] = food.x > snake.head().x
    del metrics[OPPOSITES[snake.direction]]
    new_dir = max(metrics, key=lambda k: metrics[k])
    snake.turn(new_dir)
