import pandas as pd

df = pd.read_csv(r"C:\Users\Student\Documents\РУП-9\Губанов\Тхник\python\data\products.csv", sep=";")

print("\n--- Шаг 1. Создание запроса ---")
request = df[['марка', 'модель', 'цвет', 'цена']]
print(request.head())

print("\n--- Шаг 2. Настройка условий отображения (цена выше 2 000 000) ---")
table = df[df['цена'] > 2000000]
print(table)

print("\n--- Шаг 3. Фильтрация и обработка (скидка 10%) ---")
table = table.assign(скидка = table['цена'] - (table['цена'] * 0.2))
print(table)
print("\n--- Шаг 4. Проврека результатов ---")

print("Колличество пропусков в отфильтрованных данных:")
print(table.isna().sum())
