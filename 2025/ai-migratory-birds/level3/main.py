import pandas as pd
import numpy as np

filename_weather = "all_data_from_level_1.in"
filename_birds = "level_3_a.in"

df_weather = pd.read_csv(filename_weather, sep=",")

is_fahrenheit = df_weather["Temperature [°C]"] > 55

df_weather["Temperature [°C]"] = df_weather["Temperature [°C]"].astype(float)

df_weather.loc[is_fahrenheit, "Temperature [°C]"] = (
    df_weather.loc[is_fahrenheit, "Temperature [°C]"] - 32
) / 1.8
df_weather["Temperature [°C]"] = df_weather["Temperature [°C]"].round(2)

temp_map = df_weather.set_index("BOP")["Temperature [°C]"].to_dict()

df_birds = pd.read_csv(filename_birds, sep=",")


def parse_path(path):
    return [int(bop) for bop in path.strip().split(" ")]


df_birds["path_list"] = df_birds["BOP Path"].apply(parse_path)

results = {}

for flock_id, group in df_birds.groupby("Flock ID"):
    paths = group["path_list"].tolist()

    all_nodes = [node for path in paths for node in path]
    temps = [temp_map.get(node, np.nan) for node in all_nodes]
    avg_temp = np.nanmean(temps)

    palindromes = sum([1 for p in paths if p == p[::-1]])
    palindrome_score = palindromes / len(paths)

    cycles = sum([1 for p in paths if p[0] == p[-1]])
    cycles_score = cycles / len(paths)

    second_steps = set()
    for p in paths:
        second_steps.add(p[1])
    unique_second_steps = len(second_steps)

    results[flock_id] = {
        "avg_temp": avg_temp,
        "palindrome_score": palindrome_score,
        "cycles_score": cycles_score,
        "unique_second_steps": unique_second_steps,
        "nodes_set": set(all_nodes),
    }

df_results = pd.DataFrame(results).T

final_map = {}
assigned_ids = []

hurracurra_id = df_results["avg_temp"].idxmax()
final_map[hurracurra_id] = "Hurracurra Bird"
assigned_ids.append(hurracurra_id)

candidates = df_results.drop(assigned_ids)
bluetit_id = candidates["palindrome_score"].idxmax()
final_map[bluetit_id] = "Medieval Bluetit"
assigned_ids.append(bluetit_id)

candidates = df_results.drop(assigned_ids)
blackfinch_id = candidates["cycles_score"].idxmax()
final_map[blackfinch_id] = "Flanking Blackfinch"
assigned_ids.append(blackfinch_id)

bluetit_nodes = results[bluetit_id]["nodes_set"]
candidates = df_results.drop(assigned_ids)

best_overlap = -1
wolfthroat_id = -1

for flock_id in candidates.index:
    flock_nodes = results[flock_id]["nodes_set"]

    overlap = len(flock_nodes.intersection(bluetit_nodes))
    if overlap > best_overlap:
        best_overlap = overlap
        wolfthroat_id = flock_id

final_map[wolfthroat_id] = "Sticky Wolfthroat"
assigned_ids.append(wolfthroat_id)

candidates = df_results.drop(assigned_ids)

if not candidates.empty:
    goldhammer_id = candidates["unique_second_steps"].idxmin()
    final_map[goldhammer_id] = "Rusty Goldhammer"

    remaining = candidates.drop(goldhammer_id)
    if not remaining.empty:
        firefinch_id = remaining.index[0]
        final_map[firefinch_id] = "Red Firefinch"

df_output = pd.DataFrame(list(final_map.items()), columns=['Flock ID', 'Species'])
df_output = df_output.sort_values('Flock ID')
df_output.to_csv('output.csv', index=False)
