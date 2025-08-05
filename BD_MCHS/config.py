# Данные для подключения к БД
host = "localhost"
user = "root"
db_password = "MySQL_17"
db_name = "mydb"

from werkzeug.security import generate_password_hash

# Настройки приложения
SECRET_KEY = "1234567890"  # Для безопасности замените на случайный ключ

# Список пользователей и их ролей
USERS = {
    "admin": {
        "password": generate_password_hash("admin123"),
        "role": "admin",
        "permissions": ["view", "add", "edit", "delete", "manage_users"]
    },
    "manager": {
        "password": generate_password_hash("manager123"),
        "role": "manager",
        "permissions": ["view", "add", "edit"]
    },
    "viewer": {
        "password": generate_password_hash("viewer123"),
        "role": "viewer",
        "permissions": ["view"]
    }
}

# Шаблоны ролей (можно расширять)
ROLES = {
    'admin': ['view', 'add', 'edit', 'delete', 'manage_users'],
    'manager': ['view', 'add', 'edit'],
    'viewer': ['view']
}

# Ограничение на количество строк
MAX_ROWS_TO_DISPLAY = 1000