import random as r

COUNTRYS = [
    ("Russia", "Moscow", "Eurasia", "0"),
    ("USA", "Washington", "America", "0"),
    ("Germany", "Berlin", "Eurasia", "1"),
    ("France", "Paris", "Eurasia", "1"),
    ("Britain", "London", "Eurasia", "1"),
    ("Ireland", "Dublin", "Eurasia", "1"),
    ("Niderlands", "Amsterdam", "Eurasia", "1"),
    ("Switzerland", "Beri", "Eurasia", "1"),
    ("Austria", "Vena", "Eurasia", "1"),
    ("Scotland", "Stockholm", "Eurasia", "1")
]

n = int(input("Число стран: "))
s = input("Название файла: ")
f = open(s, "w+")
for i in range(n):
    cost = str(r.randint(10, 10000) * 10)
    time = str(r.randint(10, 1000))
    vac_t = str(r.randint(0, 2))
    country = r.choice(COUNTRYS)
    if (vac_t == "0"):
        vac  = [f"{r.randint(1, 1000)}", f"{r.randint(0, 2)}"]
    elif (vac_t == "1"):
        vac = [f"{r.randint(0, 3)}"]
    else:
        vac = [f"{r.randint(0, 3)}", f"{r.random() * 100:.3f}", f"{r.random() * 100:.3f}"]
    # print(vac)
    f.writelines("\n".join(country) + "\n")
    f.writelines(time + "\n")
    f.writelines(cost + "\n")
    f.writelines(vac_t + "\n")
    f.writelines("\n".join(vac) + "\n")
