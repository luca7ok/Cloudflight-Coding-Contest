import pandas as pd
import numpy as np
from sklearn.linear_model import LinearRegression

filename_level_1 = "all_data_from_level_1.in"
filename_a = "level_2_a.in"
filename_b = "level_2_b.in"
filename_c = "level_2_c.in"

df_weather = pd.read_csv(filename_level_1, sep=",")

is_fahrenheit = df_weather["Temperature [°C]"] > 55

df_weather["Temperature [°C]"] = df_weather["Temperature [°C]"].astype(float)

df_weather.loc[is_fahrenheit, "Temperature [°C]"] = (
    df_weather.loc[is_fahrenheit, "Temperature [°C]"] - 32
) / 1.8
df_weather["Temperature [°C]"] = df_weather["Temperature [°C]"].round(2)

df_bio_a = pd.read_csv(filename_a, sep=",", na_values=["missing"])
df_bio_b = pd.read_csv(filename_b, sep=",", na_values=["missing"])
df_bio_c = pd.read_csv(filename_c, sep=",", na_values=["missing"])

df_bio_a["origin_file"] = "A"
df_bio_b["origin_file"] = "B"
df_bio_c["origin_file"] = "C"

df_bio_all = pd.concat([df_bio_a, df_bio_b, df_bio_c], ignore_index=True)
df_full = pd.merge(df_weather, df_bio_all, on="BOP", how="inner")

feature_cols = [
    "Temperature [°C]",
    "Humidity [%]",
    "Vegetation [%]",
    "Insects [g/m²]",
    "Urban Light [%]",
]
target_col = "Bird Love Score [<3]"

df_full = df_full.dropna(subset=feature_cols)

train_data = df_full[df_full[target_col].notnull()]
missing_data = df_full[df_full[target_col].isnull()]

model = LinearRegression()
model.fit(train_data[feature_cols], train_data[target_col])

predicted_scores = model.predict(missing_data[feature_cols])

df_full.loc[missing_data.index, target_col] = predicted_scores

df_output = df_full.loc[missing_data.index]
df_output = df_output[df_output['origin_file'] == 'C']

df_output = df_output[['BOP', target_col]].copy()
df_output[target_col] = df_output[target_col].round(2)

df_output.to_csv("output.csv", index=False)
