from flask import Flask, render_template_string, request, redirect, url_for, flash, session
from functools import wraps
from database import get_db_connection, authenticate_user
from templates import (
    get_base_template, 
    LOGIN_TEMPLATE, 
    INDEX_TEMPLATE, 
    TABLE_TEMPLATE, 
    VIEW_ALL_TEMPLATE, 
    EDIT_ROW_TEMPLATE
)
from config import SECRET_KEY, db_name, MAX_ROWS_TO_DISPLAY

app = Flask(__name__)
app.secret_key = SECRET_KEY

# Декораторы
def login_required(f):
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if 'user' not in session:
            flash('Пожалуйста, войдите в систему', 'danger')
            return redirect(url_for('login'))
        return f(*args, **kwargs)
    return decorated_function

def permission_required(permission):
    def decorator(f):
        @wraps(f)
        def decorated_function(*args, **kwargs):
            if 'user' not in session:
                return redirect(url_for('login'))
            if permission not in session.get('permissions', []):
                flash('У вас недостаточно прав для этого действия', 'danger')
                return redirect(url_for('index'))
            return f(*args, **kwargs)
        return decorated_function
    return decorator

# Маршруты
@app.route('/')
@login_required
def index():
    try:
        conn = get_db_connection()
        cursor = conn.cursor()
        cursor.execute("SHOW TABLES")
        tables = [table[0] for table in cursor]
        cursor.close()
        conn.close()
        return render_template_string(
            INDEX_TEMPLATE,
            title="Главная",
            tables=tables,
            permissions=session.get('permissions', []))
    except Exception as e:
        flash(f"Ошибка подключения к БД: {str(e)}", "error")
        return render_template_string(
            INDEX_TEMPLATE,
            title="Главная",
            tables=[],
            permissions=session.get('permissions', []))

@app.route('/view_all')
@login_required
@permission_required('view')
def view_all():
    conn = None
    cursor = None
    try:
        conn = get_db_connection()
        cursor = conn.cursor(dictionary=True, buffered=True)
        
        cursor.execute("SHOW TABLES")
        tables = [table["Tables_in_" + db_name] for table in cursor]
        
        if not tables:
            flash("В базе данных нет таблиц", "info")
            return redirect(url_for('index'))
        
        tables_data = {}
        
        for table_name in tables:
            try:
                cursor.execute(f"SHOW COLUMNS FROM `{table_name}`")
                columns_info = cursor.fetchall()
                columns = [col['Field'] for col in columns_info]
                
                cursor.execute(f"SELECT * FROM `{table_name}` LIMIT {MAX_ROWS_TO_DISPLAY}")
                rows = cursor.fetchall()
                
                tables_data[table_name] = {
                    'columns': columns,
                    'rows': rows
                }
                
            except Exception as e:
                error_msg = str(e) if str(e) else "Неизвестная ошибка (код: 0)"
                flash(f"Ошибка при загрузке таблицы `{table_name}`: {error_msg}", "warning")
                continue
        
        if not tables_data:
            flash("Не удалось загрузить данные ни из одной таблицы", "danger")
            return redirect(url_for('index'))
        
        return render_template_string(
            VIEW_ALL_TEMPLATE,
            title="Все данные",
            tables_data=tables_data,
            permissions=session.get('permissions', []),
            MAX_ROWS_TO_DISPLAY=MAX_ROWS_TO_DISPLAY)
        
    except Exception as e:
        error_msg = str(e) if str(e) else "Неизвестная ошибка (пустое сообщение)"
        flash(f"Критическая ошибка при загрузке данных: {error_msg}", "danger")
        return redirect(url_for('index'))
        
    finally:
        if cursor:
            cursor.close()
        if conn:
            conn.close()

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        input_password = request.form.get('password')
        
        user = authenticate_user(username, input_password)
        
        if user:
            session['user'] = user['username']
            session['role'] = user['role']
            session['permissions'] = user['permissions']
            flash('Вы успешно вошли в систему', 'success')
            return redirect(url_for('index'))
        else:
            flash('Неверные учетные данные', 'danger')
    
    return render_template_string(LOGIN_TEMPLATE, title="Вход")

@app.route('/logout')
def logout():
    session.clear()
    flash('Вы вышли из системы', 'info')
    return redirect(url_for('login'))

@app.route('/table/<table_name>')
@login_required
@permission_required('view')
def show_table(table_name):
    try:
        conn = get_db_connection()
        cursor = conn.cursor(dictionary=True)
        
        cursor.execute(f"SHOW COLUMNS FROM `{table_name}`")
        columns = [column['Field'] for column in cursor]
        
        cursor.execute(f"SELECT * FROM `{table_name}`")
        rows = cursor.fetchall()
        
        cursor.close()
        conn.close()
        
        return render_template_string(
            TABLE_TEMPLATE,
            title=f"Таблица `{table_name}`",
            table_name=table_name,
            columns=columns,
            rows=rows,
            permissions=session.get('permissions', []))
    except Exception as e:
        flash(f"Ошибка загрузки таблицы: {str(e)}", "error")
        return redirect(url_for('index'))

@app.route('/add_row/<table_name>', methods=['GET', 'POST'])
@login_required
@permission_required('add')
def add_row(table_name):
    if request.method == 'GET':
        try:
            conn = get_db_connection()
            cursor = conn.cursor(dictionary=True)
            cursor.execute(f"SHOW COLUMNS FROM `{table_name}`")
            columns = cursor.fetchall()
            cursor.close()
            conn.close()
            
            return render_template_string(
                EDIT_ROW_TEMPLATE,
                title=f"Добавление в `{table_name}`",
                table_name=table_name,
                columns=columns,
                row=None,
                action='add',
                permissions=session.get('permissions', []))
        except Exception as e:
            flash(f"Ошибка: {str(e)}", "error")
            return redirect(url_for('show_table', table_name=table_name))
    
    elif request.method == 'POST':
        try:
            conn = get_db_connection()
            cursor = conn.cursor()
            
            data = {}
            cursor.execute(f"SHOW COLUMNS FROM `{table_name}`")
            for column in cursor:
                field = column[0]
                if field in request.form:
                    value = request.form[field] if request.form[field] != '' else None
                    data[field] = value
            
            columns = ', '.join(data.keys())
            placeholders = ', '.join(['%s'] * len(data))
            sql = f"INSERT INTO {table_name} ({columns}) VALUES ({placeholders})"
            
            cursor.execute(sql, tuple(data.values()))
            conn.commit()
            
            flash("Запись успешно добавлена!", "success")
            return redirect(url_for('show_table', table_name=table_name))
        
        except Exception as e:
            conn.rollback()
            flash(f"Ошибка добавления: {str(e)}", "error")
            return redirect(url_for('add_row', table_name=table_name))
        
        finally:
            cursor.close()
            conn.close()

@app.route('/edit_row/<table_name>/<int:row_id>', methods=['GET', 'POST'])
@login_required
@permission_required('edit')
def edit_row(table_name, row_id):
    if request.method == 'GET':
        try:
            conn = get_db_connection()
            cursor = conn.cursor(dictionary=True)
            
            cursor.execute(f"SHOW COLUMNS FROM `{table_name}`")
            columns = cursor.fetchall()
            
            if not columns:
                raise Exception("No columns found in table")
                
            primary_key = columns[0]['Field']
            cursor.execute(f"SELECT * FROM `{table_name}` WHERE {primary_key} = %s", (row_id,))
            row = cursor.fetchone()
            
            cursor.close()
            conn.close()
            
            return render_template_string(
                EDIT_ROW_TEMPLATE,
                title=f"Редактирование `{table_name}`",
                table_name=table_name,
                columns=columns,
                row=row,
                action='edit',
                permissions=session.get('permissions', []))
        except Exception as e:
            flash(f"Ошибка: {str(e)}", "error")
            return redirect(url_for('show_table', table_name=table_name))
    
    elif request.method == 'POST':
        conn = None
        cursor = None
        try:
            conn = get_db_connection()
            cursor = conn.cursor()
            
            cursor.execute(f"SHOW COLUMNS FROM `{table_name}`")
            columns = cursor.fetchall()
            if not columns:
                raise Exception("No columns found in table")
            primary_key = columns[0][0]
            
            data = {}
            for column in columns:
                field = column[0]
                if field in request.form and field != primary_key:
                    value = request.form[field] if request.form[field] != '' else None
                    data[field] = value
            
            if not data:
                flash("Нет данных для обновления", "warning")
                return redirect(url_for('edit_row', table_name=table_name, row_id=row_id))
            
            set_clause = ', '.join([f"{k} = %s" for k in data.keys()])
            sql = f"UPDATE {table_name} SET {set_clause} WHERE {primary_key} = %s"
            
            cursor.execute(sql, (*data.values(), row_id))
            conn.commit()
            
            flash("Запись успешно обновлена!", "success")
            return redirect(url_for('show_table', table_name=table_name))
        
        except Exception as e:
            if conn:
                conn.rollback()
            flash(f"Ошибка обновления: {str(e)}", "error")
            return redirect(url_for('edit_row', table_name=table_name, row_id=row_id))
        
        finally:
            if cursor:
                cursor.close()
            if conn:
                conn.close()

@app.route('/delete_row/<table_name>/<int:row_id>')
@login_required
@permission_required('delete')
def delete_row(table_name, row_id):
    try:
        conn = get_db_connection()
        cursor = conn.cursor()
        
        cursor.execute(f"SHOW COLUMNS FROM `{table_name}`")
        primary_key = cursor.fetchone()[0]
        cursor.fetchall()
        
        cursor.execute(f"DELETE FROM `{table_name}` WHERE {primary_key} = %s", (row_id,))
        conn.commit()
        
        flash("Запись успешно удалена!", "success")
    except Exception as e:
        conn.rollback()
        flash(f"Ошибка удаления: {str(e)}", "error")
    finally:
        cursor.close()
        conn.close()
    
    return redirect(url_for('show_table', table_name=table_name))

if __name__ == '__main__':
    app.run(debug=True)