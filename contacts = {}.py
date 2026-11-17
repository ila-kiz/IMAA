contacts = {}

def show_menu():
    print("1 - добавить, 2 - найти, 3 - все, 0 - выход")

def add_contact():
    name = input("Имя: ").strip()
    if not name:
        print("Имя не может быть пустым.")
        return
    if name in contacts:
        print("Уже есть!")
        return
    phone = input("Телефон: ").strip()
    if not phone:
        print("Телефон не может быть пустым.")
        return
    contacts[name] = phone
    print(f"Контакт {name} добавлен.")

def find_contact():
    name = input("Имя: ").strip()
    if name in contacts:
        print(f"{name}: {contacts[name]}")
    else:
        print("Не найден.")

def show_all():
    if not contacts:
        print("Список контактов пуст.")
        return
    for name, phone in contacts.items():
        print(f"{name}: {phone}")

def main():
    while True:
        show_menu()
        choice = input("> ").strip()
        if choice == "1":
            add_contact()
        elif choice == "2":
            find_contact()
        elif choice == "3":
            show_all()
        elif choice == "0":
            print("Пока!")
            break
        else:
            print("Не понял.")

if __name__ == "__main__":
 main() 