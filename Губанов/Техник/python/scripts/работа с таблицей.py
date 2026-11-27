import pandas as pd

df = pd.read_csv(r"C:\Users\Student\Documents\РУП-9\Губанов\Тхник\python\data\products.csv", sep=";")

print("--- Загруженная база данных ---")
print(df.head())

print("\n--- Информация о таблице ---")
df.info()

print("\n--- Шаг 1. Поиск данных (поиск всех чёрных машин) ---")
search = df.query("цвет == 'чёрный'")
print(search)

print("\n--- Шаг 2. Сортировка данных (по убывани цены) ---")
sort = search.sort_values(by="цена", ascending=False)
print(sort)

print("\n--- Шаг 3. Фильтрация и обработка ---")
filter_df = (df.query("`дата выпуска` >= 2015").assign(возраст_авто=lambda x: x["дата выпуска"].rsub(2026)))
print(filter_df.loc[:, ["марка", "модель", "дата выпуска", "возраст_авто"]])

print("\n--- Шаг 4. Проврека результатов ---")
print("Колличество пропусков в отфильтрованных данных:")
print(filter_df.isna().sum())
