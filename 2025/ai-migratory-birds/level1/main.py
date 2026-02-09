import pandas as pd

filename = "level_1_e.in"

df = pd.read_csv(filename, sep=',')

bops = df.values.tolist()
bops.sort(key=lambda x: (-x[1], x[2]))

with open('output.out', 'w') as out_file:
    for bop in bops:
        out_file.write(str(bop[0]) + ' ')



