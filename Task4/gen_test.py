import random as r
import os

OP_SIZES = [100, 500, 1000, 2000, 3000, 5000, 7500, 10000]
STANDARD_SIZES = [3, 5, 10]
try:
    os.mkdir("data")
except FileExistsError:
    pass

try:
    os.mkdir("data/operation")
except FileExistsError:
    pass

try:
    os.mkdir("data/standard")
except FileExistsError:
    pass

for size in OP_SIZES:
    f = open(f"./data/operation/data_{size}.txt", "w")

    for _ in range(size):
        op = r.choice("+-*/")
        if (op == '/'):
            num = r.choice([r.randint(-20, -1), r.randint(1, 20)])
        else:
            num = r.randint(-20, 20)
        f.write(f"{num} {op} ")
    f.write(f"{r.randint(-20, 20)}\n")
    f.close()

for size in STANDARD_SIZES:
    f = open(f"./data/standard/data_{size}.txt", "w")

    for _ in range(size):
        f.write(f"{r.randint(-100, 100)}\n")
    f.close()

