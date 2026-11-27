contacts = {}

def show_menu():
    print("1 - Добавить\n2 - Найти\n3 - Все\n0 - Выход\n")

def add_contact():
    name = input("Имя: ").strip()
    if not name:
        return
    if name in contacts:
        print("Уже есть!")
        return
    phone = input("Телефон: ").strip()
    if not phone:
        return
    contacts[name] = phone
    print("Добавлено.")

def find_contact():
    name = input("Имя: ").strip()
    if not name:
        return
    if name in contacts:
        print(contacts[name])
    else:
        print("Не найден.")

def show_all():
    if not contacts:
        print("Пусто.")
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