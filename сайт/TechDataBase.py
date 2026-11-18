import sqlite3
import pandas as pd
df = pd.read_csv('Table.csv', sep=';') #загружает данные из файла
df = df.drop(columns=['Unnamed: 5']) # удаление лишнего столбика


print("--- Загруженная база данных ---")
print(df.head().to_string(index=False))

print("\n--- Информация о таблице ---")
print(df.info())

found = df[df['Цели:'] == 'Развлекательные'] #фильтрует таблицу
found_sorted = found.sort_values(by='Жанр игр:') #выводит на экран только два столбца

result = found_sorted[['Жанр игр:', 'Примеры:']]
print("\n--- Найденные жанры ---")
print(result.to_string(index=False))#превращает таблицу в обычный текст и отключает отображение левого столбца с техническими номерами строк


print("\nКоличество найденных жанров:", len(result)) #функция len() считает, сколько строк попало в итоговую таблицу result
print("\nКоличество жанров по целям:")
for goal, count in df['Цели:'].value_counts().items(): #подсчитывает, сколько раз встречается каждая цель в столбце 'Цели:' (.value_counts()), и с помощью .items() разбивает результат на пары «название цели (goal) — количество (count)», чтобы перебрать их в цикле
    print(f"- {goal}: {count}") #печатает каждую пару в виде аккуратного маркированного списка (например, - Развлекательные: 7), убирая технические служебные надписи

result.to_csv('result.csv', sep=';', index=False, encoding='utf-8-sig')#разделяет столбцы точкой с запятой, не записывает в файл автоматические номера строк, сохраняет файл в кодировке

with open('Table.csv', encoding='utf-8') as f:
    for line in f:
        if 'Образовательные' in line:
            clean_line = line.strip().replace(';', ' - ') #убрать ; заменив на пробел
            print(clean_line.strip())
