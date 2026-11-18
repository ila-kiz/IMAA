import pandas as pd

# Укажите полное имя файла с расширением .csv в кавычках
df = pd.read_csv(r"c:\Users\Student\Desktop\Новая папка\https://lens.usercontent.google.com/banana?agsi=CqwBL2Zvb3RwcmludHMtcHJvZC1zZWFyY2gtbXVsdGltb2RhbC11c2VyLXVwbG9hZHMtZXBoZW1lcmFsLWdhaWEtY2xvbmUvZ2xvYmFsOjowMDAwNTVjZmVjNzAwMjZkOjAwMDAwMTY3OjE6MmRiYmIyMDBkOTNiNjFlOTowMDAwNTVjZmVjNzAwMjZkOjAwMDAwMzFkNzAxMDMzNjg6MDAwNjYwNjE4NGE3OTdhZhACGAEiCHRleHQvY3N2KhpGMV8yMDI2X1N0YW5kaW5nc19VVEY4LmNzdg==.csv")

# Сортировка по одному столбцу (по умолчанию — по возрастанию)
df_sorted = df.sort_values(by="название_столбца")

# Вывод результата
print("dd")
print("bf")
print(df_sorted)
