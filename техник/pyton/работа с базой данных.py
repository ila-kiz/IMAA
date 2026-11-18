import pandas as pd

df = pd.read_csv("D:\Кузин Илья 1РУП-9-26\техник\data\аксессуары.csv", sep=";")
print("--- загруженная база данных ---")
print(df.head())
print("\n--- Информация о таблице ---")
print(df.info())



df['Защита'] = pd.to_numeric(df['Защита'], errors='coerce')
# поиск данных
search = df[df['Защита'] >= 2]
# Сортировка
sorted = search.sort_values(by = 'Защита' , ascending=False)
# --- Шаг 3. Фильтрация и обработка ---
final = sorted[sorted['Защита'] >= 2].assign(Статус='Обработано')
# --- Шаг 4. Проверка результатов ---
print("\n--- Итоговая выборка ---")
print(final[['Название аксессуара', 'Защита', 'Статус']]) 
print(f"Проверка пройдена: {final['Защита'].is_monotonic_decreasing}")
input("\nНажмите Enter для продолжения...")






























print("\n")
print("\n")
print("\n")
print("\n")
print("\n")
print("\n")
print("\n")
print("\n")
print("\n")
print("\n")
print("\n")
print("\n")
print("\n")
print("\n")
print("\n")
print("\n")
print("\n")
print("\n")
print("\n")
print("\n")
print("\n")
print("\n")
print("\n")
print("\n")





















pole = ['Название аксессуара', 'Тип / Категория', 'Защита']
zapr = df[pole].copy()
print(zapr.head(), "\n")


print("\n")
print("\n")
print("\n")



usl = (df['Тип / Категория'].str.contains('Боевой', na=False))
flt = df[usl].copy()
print(flt[pole].head(), "\n")


print("\n")
print("\n")
print("\n")



flt['Рейтинг'] = flt['Защита'] * 10

def cost(row):
    if row['Защита'] >= 4:
        return "Топ-уровень"
    elif row['Защита'] >= 2:
        return "Хороший"
    else:
        return "Базовый"
flt['Оценка'] = flt.apply(cost, axis=1)
print(flt[['Название аксессуара', 'Защита', 'Рейтинг', 'Оценка', 'Тип / Категория']].head(), "\n")


print("\n")
print("\n")
print("\n")



if len(flt) > 0:
    print(f"Проверка пройдена! Найдено записей: {len(flt)}")
else:
    
    print("Ошибка: ничего не найдено.")


print("\n")
print("\n")
print("\n")

print("\n--- ИТОГОВЫЙ РЕЗУЛЬТАТ ЗАПРОСА ---")
print(flt[['Название аксессуара', 'Тип / Категория', 'Защита', 'Оценка']].to_string(index=False))

print("\n")

input("\nНажмите Enter для выхода...")