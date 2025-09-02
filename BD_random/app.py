import sqlite3
import logging
from datetime import datetime, date
import random
from typing import List, Optional
from flask import Flask, render_template, request, jsonify, flash, redirect, url_for
from flask import send_file
import io
import csv

# Настройка логирования
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)

app = Flask(__name__)
app.secret_key = 'your-secret-key-here'

class Employee:
    def __init__(self, full_name: str, birth_date: str, gender: str):
        # Валидация данных
        try:
            datetime.strptime(birth_date, "%Y-%m-%d")
        except ValueError:
            raise ValueError("Неверный формат даты. Используйте YYYY-MM-DD")
        
        if gender not in ["Male", "Female"]:
            raise ValueError("Пол должен быть 'Male' или 'Female'")
            
        self.full_name = full_name
        self.birth_date = birth_date
        self.gender = gender
    
    def calculate_age(self) -> int:
        birth_date = datetime.strptime(self.birth_date, "%Y-%m-%d").date()
        today = date.today()
        age = today.year - birth_date.year
        if (today.month, today.day) < (birth_date.month, birth_date.day):
            age -= 1
        return age

class EmployeeDirectory:
    def __init__(self, db_name: str = "employees.db"):
        self.db_name = db_name
    
    def __enter__(self):
        self.conn = sqlite3.connect(self.db_name)
        self.conn.row_factory = sqlite3.Row
        self.cursor = self.conn.cursor()
        return self
    
    def __exit__(self, exc_type, exc_val, exc_tb):
        if self.conn:
            self.conn.close()
    
    def create_table(self):
        with self as directory:
            directory.cursor.execute("""
                CREATE TABLE IF NOT EXISTS employees (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    full_name TEXT NOT NULL,
                    birth_date TEXT NOT NULL,
                    gender TEXT NOT NULL
                )
            """)
            directory.conn.commit()
            logger.info("Таблица сотрудников создана успешно")
    
    def clear_database(self):
        with self as directory:
            directory.cursor.execute("DROP TABLE IF EXISTS employees")
            directory.conn.commit()
            self.create_table()
            logger.warning("База данных очищена")
    
    def add_employee(self, employee: Employee):
        with self as directory:
            directory.cursor.execute(
                "INSERT INTO employees (full_name, birth_date, gender) VALUES (?, ?, ?)",
                (employee.full_name, employee.birth_date, employee.gender)
            )
            directory.conn.commit()
            logger.info(f"Сотрудник '{employee.full_name}' добавлен")
    
    def get_employees(self, page: int = 1, per_page: int = 50) -> tuple:
        with self as directory:
            offset = (page - 1) * per_page
            directory.cursor.execute("SELECT COUNT(*) as total FROM employees")
            total = directory.cursor.fetchone()['total']
            
            directory.cursor.execute("""
                SELECT full_name, birth_date, gender 
                FROM employees 
                ORDER BY full_name
                LIMIT ? OFFSET ?
            """, (per_page, offset))
            
            employees = []
            for row in directory.cursor.fetchall():
                emp = Employee(row['full_name'], row['birth_date'], row['gender'])
                employees.append({
                    'full_name': emp.full_name,
                    'birth_date': emp.birth_date,
                    'gender': emp.gender,
                    'age': emp.calculate_age()
                })
            
            return employees, total
    
    def batch_save(self, employees: List[Employee]):
        with self as directory:
            data = [(e.full_name, e.birth_date, e.gender) for e in employees]
            directory.cursor.executemany(
                "INSERT INTO employees (full_name, birth_date, gender) VALUES (?, ?, ?)",
                data
            )
            directory.conn.commit()
            logger.info(f"Добавлено {len(employees)} сотрудников")
    
    def generate_random_employees(self, count: int = 1000):
        try:
            first_names_male = ["Иван", "Петр", "Сергей", "Андрей", "Алексей", "Дмитрий", "Михаил", "Николай"]
            first_names_female = ["Анна", "Мария", "Елена", "Ольга", "Татьяна", "Наталья", "Ирина", "Светлана"]
            last_names = ["Иванов", "Петров", "Сидоров", "Смирнов", "Кузнецов", "Попов", "Волков", "Федоров"]
            middle_names_male = ["Иванович", "Петрович", "Сергеевич", "Андреевич", "Алексеевич"]
            middle_names_female = ["Ивановна", "Петровна", "Сергеевна", "Андреевна", "Алексеевна"]
            
            employees = []
            
            for i in range(count):
                gender = random.choice(["Male", "Female"])
                if gender == "Male":
                    first_name = random.choice(first_names_male)
                    middle_name = random.choice(middle_names_male)
                    last_name = random.choice(last_names)
                else:
                    first_name = random.choice(first_names_female)
                    middle_name = random.choice(middle_names_female)
                    last_name = random.choice(last_names)
                
                full_name = f"{last_name} {first_name} {middle_name}"
                
                year = random.randint(1950, 2005)
                month = random.randint(1, 12)
                day = random.randint(1, 28)
                birth_date = f"{year}-{month:02d}-{day:02d}"
                
                employees.append(Employee(full_name, birth_date, gender))
                
                if len(employees) >= 100:
                    self.batch_save(employees)
                    employees = []
            
            if employees:
                self.batch_save(employees)
            
            logger.info(f"Сгенерировано {count} случайных сотрудников")
            
        except Exception as e:
            logger.error(f"Error in generate_random_employees: {e}")
            raise
    def query_male_f_surnames(self) -> tuple:
        with self as directory:
            start_time = datetime.now()
            
            directory.cursor.execute("""
                SELECT full_name, birth_date, gender 
                FROM employees 
                WHERE gender = 'Male' AND full_name LIKE 'Ф%'
            """)
            
            results = []
            for row in directory.cursor.fetchall():
                emp = Employee(row['full_name'], row['birth_date'], row['gender'])
                results.append({
                    'full_name': emp.full_name,
                    'birth_date': emp.birth_date,
                    'gender': emp.gender,
                    'age': emp.calculate_age()
                })
            
            end_time = datetime.now()
            execution_time = (end_time - start_time).total_seconds()
            
            return results, execution_time
    
    def optimize_database(self):
        with self as directory:
            directory.cursor.execute("""
                CREATE INDEX IF NOT EXISTS idx_gender_surname 
                ON employees(gender, substr(full_name, 1, 1))
            """)
            directory.conn.commit()
            logger.info("База данных оптимизирована")
    
    def get_statistics(self) -> dict:
        with self as directory:
            directory.cursor.execute("SELECT COUNT(*) as total FROM employees")
            total = directory.cursor.fetchone()['total']
            
            directory.cursor.execute("SELECT COUNT(*) as count FROM employees WHERE gender = 'Male'")
            male_count = directory.cursor.fetchone()['count']
            
            directory.cursor.execute("SELECT COUNT(*) as count FROM employees WHERE gender = 'Female'")
            female_count = directory.cursor.fetchone()['count']
            
            return {
                'total_employees': total,
                'male_count': male_count,
                'female_count': female_count
            }

# Инициализация базы данных
def init_db():
    directory = EmployeeDirectory()
    directory.create_table()
    directory.optimize_database()

# Маршруты Flask
@app.route('/')
def index():
    directory = EmployeeDirectory()
    stats = directory.get_statistics()
    return render_template('index.html', 
                         total_employees=stats['total_employees'],
                         male_count=stats['male_count'],
                         female_count=stats['female_count'])

@app.route('/employees')
def employees():
    page = request.args.get('page', 1, type=int)
    per_page = 50
    
    directory = EmployeeDirectory()
    employees_list, total = directory.get_employees(page, per_page)
    
    total_pages = (total + per_page - 1) // per_page
    
    return render_template('employees.html', 
                         employees=employees_list,
                         page=page,
                         total_pages=total_pages,
                         total=total)

@app.route('/add_employee', methods=['GET', 'POST'])
def add_employee():
    if request.method == 'POST':
        try:
            full_name = request.form['full_name']
            birth_date = request.form['birth_date']
            gender = request.form['gender']
            
            employee = Employee(full_name, birth_date, gender)
            directory = EmployeeDirectory()
            directory.add_employee(employee)
            
            flash('Сотрудник успешно добавлен!', 'success')
            return redirect(url_for('employees'))
        except ValueError as e:
            flash(str(e), 'error')
        except Exception as e:
            flash('Произошла ошибка при добавлении сотрудника', 'error')
            logger.error(f"Error adding employee: {e}")
    
    return render_template('add_employee.html')

@app.route('/generate_data', methods=['POST'])
def generate_data():
    try:
        count = request.form.get('count', '1000')
        # Преобразуем в число с обработкой ошибок
        count = int(count) if count.isdigit() else 1000
        count = max(1, min(count, 10000))  # Ограничиваем от 1 до 10000
        
        directory = EmployeeDirectory()
        directory.generate_random_employees(count)
        flash(f'Успешно сгенерировано {count} случайных сотрудников!', 'success')
    except Exception as e:
        flash('Произошла ошибка при генерации данных', 'error')
        logger.error(f"Error generating data: {e}")
    
    return redirect(url_for('index'))
@app.route('/query_f_surnames')
def query_f_surnames():
    directory = EmployeeDirectory()
    results, execution_time = directory.query_male_f_surnames()
    
    return render_template('query_results.html',
                         results=results,
                         execution_time=execution_time,
                         count=len(results))

@app.route('/optimize', methods=['POST'])
def optimize():
    try:
        directory = EmployeeDirectory()
        
        # Замер времени до оптимизации
        results_before, time_before = directory.query_male_f_surnames()
        
        # Оптимизация
        directory.optimize_database()
        
        # Замер времени после оптимизации
        results_after, time_after = directory.query_male_f_surnames()
        
        improvement = ((time_before - time_after) / time_before) * 100 if time_before > 0 else 0
        
        flash(f'Оптимизация завершена! Ускорение: {improvement:.1f}%', 'success')
        return render_template('optimization_results.html',
                             time_before=time_before,
                             time_after=time_after,
                             improvement=improvement,
                             count_before=len(results_before),
                             count_after=len(results_after))
    except Exception as e:
        flash('Произошла ошибка при оптимизации', 'error')
        logger.error(f"Error optimizing: {e}")
        return redirect(url_for('index'))

@app.route('/clear_database', methods=['POST'])
def clear_database():
    try:
        directory = EmployeeDirectory()
        directory.clear_database()
        flash('База данных очищена!', 'warning')
    except Exception as e:
        flash('Произошла ошибка при очистке базы данных', 'error')
        logger.error(f"Error clearing database: {e}")
    
    return redirect(url_for('index'))

@app.route('/export_csv')
def export_csv():
    try:
        directory = EmployeeDirectory()
        employees, _ = directory.get_employees(1, 1000000)
        
        output = io.StringIO()
        writer = csv.writer(output)
        writer.writerow(['ФИО', 'Дата рождения', 'Пол', 'Возраст'])
        
        for emp in employees:
            writer.writerow([emp['full_name'], emp['birth_date'], emp['gender'], emp['age']])
        
        output.seek(0)
        return send_file(
            io.BytesIO(output.getvalue().encode('utf-8')),
            mimetype='text/csv',
            as_attachment=True,
            download_name='employees.csv'
        )
    except Exception as e:
        flash('Произошла ошибка при экспорте', 'error')
        logger.error(f"Error exporting CSV: {e}")
        return redirect(url_for('employees'))

@app.route('/api/stats')
def api_stats():
    directory = EmployeeDirectory()
    stats = directory.get_statistics()
    return jsonify(stats)

if __name__ == '__main__':
    init_db()
    app.run(debug=True, host='0.0.0.0', port=5000)