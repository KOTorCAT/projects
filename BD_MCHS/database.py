import mysql.connector
from werkzeug.security import check_password_hash
from config import host, user, db_password, db_name, USERS

def get_db_connection():
    return mysql.connector.connect(
        host=host,
        user=user,
        password=db_password,
        database=db_name
    )

def authenticate_user(username, input_password):
    """Аутентификация пользователя на основе данных из config.py"""
    user_data = USERS.get(username)
    if user_data and check_password_hash(user_data['password'], input_password):
        return {
            'username': username,
            'role': user_data['role'],
            'permissions': user_data['permissions']
        }
    return None