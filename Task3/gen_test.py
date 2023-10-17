import random as r
import os
# SIZES = [50, 100, 500, 1000, 2000, 3000]
PROC = [10, 20, 40, 80]
SIZES = [10]
# PROC = [80]

# SIZES = [100]
# PROC = [10]
# os.mkdir("data")
# os.mkdir("data/mat")
# os.mkdir("data/vec")
for size in SIZES:
    for proc in PROC:
        fname_mat = f"data/mat/mat_{size}_{proc}.txt"
        fname_vec = f"data/vec/vec_{size}_{proc}.txt"
        fout_mat = open(fname_mat, "w")
        fout_vec = open(fname_vec, "w")
        mat = [[0] * size for _ in range(size)]
        vec = [0] * size

        chance = proc / 100
        # print(chance)

        mat_elems = int(size * size * chance)
        population = []
        for i in range(size):
            population.extend([(i, j, r.randint(1, 2000)) for j in range(size)])
        mat_not_null = sorted(sorted(r.sample(population, k=mat_elems), key=lambda x:x[1]), key = lambda x: x[0])
        # print(mat_not_null)
        # for i in range(size):
        #     for j in range(size):
        #         rnum = r.random()
        #         # print(rnum)
        #         if (rnum < chance):
        #             mat_elems += 1
        #             mat[i][j] = r.randint(1, 200000)
        
        vec_elems = int(size * chance)
        population = [(j, r.randint(1, 2000)) for j in range(size)]
        vec_not_null = sorted(r.sample(population, k=vec_elems), key=lambda x: x[0])
        # for i in range(size):
        #     rnum = r.random()
        #     if (rnum < chance):
        #         vec_elems += 1
        #         vec[i] = r.randint(1, 200000)
        
        fout_mat.write(f"{size} {size} {mat_elems}\n")
        for elem in mat_not_null:
            fout_mat.write(f"{' '.join([str(i + 1) for i in elem])}\n")
        fout_mat.close()
        
        fout_vec.write(f"{size} {vec_elems}\n")
        for elem in vec_not_null:
            fout_vec.write(f"{' '.join([str(i + 1) for i in elem])}\n")
        fout_vec.close()
        # for i in range(size):
        #     for j in range(size):
        #         if (mat[i][j] != 0):
        #             fout_mat.write(f"{i + 1} {j + 1} {mat[i][j]}\n")
        # fout_mat.close()

        # fout_vec.write(f"{size} {vec_elems}\n")
        # for i in range(size):
        #     if (vec[i] != 0):
        #         fout_vec.write(f"{i + 1} {vec[i]}\n")
        # fout_vec.close()
        