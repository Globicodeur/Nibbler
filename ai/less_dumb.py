from snake import Direction, GameOptions, Position
from collections import defaultdict

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

DELTAS = [
    Position(0, -1),
    Position(0,  1),
    Position(-1, 0),
    Position(1,  0),
]

def is_obstacle(pos, snakes, obstacles):
    # Borders
    if not GameOptions.torus:
        if pos.x < 0 or pos.x >= GameOptions.width or\
           pos.y < 0 or pos.y >= GameOptions.height:
           return True
    else:
        pos = Position(pos.x % GameOptions.width, pos.y % GameOptions.height)

    # Snakes
    for snake in snakes:
        if pos in snake:
            return True
    # Obstacles
    if pos in obstacles:
        return True

    return False

def goto_food_metric(metrics, snake, food):
    if not GameOptions.torus:
        metrics[Direction.Up] += food.y < snake.head().y
        metrics[Direction.Down] += food.y > snake.head().y
        metrics[Direction.Left] += food.x < snake.head().x
        metrics[Direction.Right] += food.x > snake.head().x
    else:
        distDown = (food.y - snake.head().y) % GameOptions.height
        distUp = (snake.head().y - food.y) % GameOptions.height
        distLeft = (snake.head().x - food.x) % GameOptions.width
        distRight = (food.x - snake.head().x) % GameOptions.width
        metrics[Direction.Up] += distUp < distDown
        metrics[Direction.Down] += distUp and distUp >= distDown
        metrics[Direction.Left] += distLeft < distRight
        metrics[Direction.Right] += distLeft and distLeft >= distRight


def dont_die_metric(metrics, snake, snakes, obstacles):
    for direction in ALL_DIRS:
        next_head = snake.head() + DELTAS[direction]
        metrics[direction] += (not is_obstacle(next_head, snakes, obstacles)) * 2

def ai(snake, snakes, food, obstacles):
    metrics = defaultdict(float)
    goto_food_metric(metrics, snake, food)
    dont_die_metric(metrics, snake, snakes, obstacles)
    # resolve
    del metrics[OPPOSITES[snake.direction]]
    best_dir = max(metrics, key=metrics.get)
    # either choose best_dir
        # snake.turn(best_dir)
    # or choose randomly among directions that have the same score as best_dir
    best_score = metrics[best_dir]
    dirs = []
    for d, v in metrics.items():
        if v == best_score:
            dirs.append(d)
    snake.turn(random.choice(dirs))
