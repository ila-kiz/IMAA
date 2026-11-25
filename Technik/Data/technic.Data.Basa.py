# import pandas as pd
# df = pd.read_csv("База данных.csv", sep = ";")
# print("---Загруженная база данных---")
# print(df.head())
# print("\n---Информация о таблице ---")
# print(df.info())


# #   Поиск данных
# df["Год начала"] = pd.to_numeric(
#     df["Даты эксплуатации"].str.split("-").str[0], errors="coerce")

# # ищем только модели, которые ещё выпускаются (в графе стоит «н.в.»)
# search = df[df["Даты эксплуатации"].str.contains("н.в.", na=False)].copy()

# # --- Шаг 3. Сортировка (от самых новых к самым старым) ---
# sorted = search.sort_values(by="Год начала", ascending=False)

# # --- Шаг 4. Фильтрация и обработка ---
# final = sorted.assign(Статус="Эксплуатируются")

# # --- Шаг 5. Проверка результатов ---
# print("\n--- Итоговая выборка ---")
# print(final[["Название трамвая", "Модель", "Даты эксплуатации", "Статус"]])
# print(f"Проверка пройдена: {final['Год начала'].is_monotonic_decreasing}")

# print("\nНажмите Enter для выхода...")
# input()






import os
import pandas as pd

# --- Шаг 1. Создание запроса: загрузка базы и выбор нужных полей ---

# путь к файлу строим от папки, где лежит сам скрипт,
# чтобы запуск из любого терминала находил базу
script_dir = os.path.dirname(os.path.abspath(__file__))
csv_path = os.path.join(script_dir, "База данных.csv")

df = pd.read_csv(csv_path, sep=";", encoding="utf-8-sig")

print("--- Загруженная база данных ---")
print(df.head())
print("\n--- Информация о таблице ---")
print(df.info())

# Вычисляемое поле: год начала эксплуатации из даты вида "1995-н.в."
df["Год начала"] = pd.to_numeric(
    df["Даты эксплуатации"].str.split("-").str[0],
    errors="coerce"
)

# --- Шаг 2. Настройка условий отбора ---
# только модели, которые ещё выпускаются (в графе стоит «н.в.»)
search = df[df["Даты эксплуатации"].str.contains("н.в.", na=False)].copy()

# и эксплуатируются с 2010 года (начало не раньше 2010)
search = search[search["Год начала"] >= 2010]

# --- Шаг 3. Обработка данных: сортировка от новых к старым ---
result = search.sort_values(by="Год начала", ascending=False)
result = result.assign(Статус="эксплуатируются")

# --- Шаг 4. Проверка результата ---
print("\n--- Итоговая выборка ---")
print(result[["Название трамвая", "Модель", "Даты эксплуатации", "Статус"]])

print(f"\nПроверка сортировки пройдена: "
      f"{result['Год начала'].is_monotonic_decreasing}")
print(f"Проверка условия 'с 2010 года': "
      f"{(result['Год начала'] >= 2010).all()}")
print(f"Всего моделей в выборке: {len(result)}")

print("\nНажмите Enter для выхода...")
input()