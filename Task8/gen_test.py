import random as r
import os
NODES = [5, 10, 15, 20, 25, 30]
PROCS = [5, 10, 15, 20, 30, 50]
try:
    os.mkdir("data")
except BaseException:
    pass

for size in NODES:
    for proc in PROCS:
        fname = f"data/graph_{size}_{proc}.txt"
        fout = open(fname, "w")
        nodes = [str(i + 1) for i in range(size)]
        edges = [(i, j) for j in range(size) for i in range(size)]
        # print(edges)
        chance = proc / 100

        edges_cnt = int(len(edges) * chance)
        edges = list(r.sample(population=edges, k=edges_cnt))
        fout.write(str(size) + '\n')
        for elem in nodes:
            fout.write(elem + '\n')
        for elem in edges:
            fout.write(f"{elem[0]} {elem[1]}\n")
        fout.close()