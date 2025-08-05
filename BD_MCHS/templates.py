def get_base_template(content):
    return f'''
<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>MySQL Admin - {{ title }}</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css" rel="stylesheet">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0/css/all.min.css">
    <style>
        body {{ 
            background-color: #f8f9fa; 
            padding-top: 20px;
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
        }}
        .container {{ max-width: 1400px; }}
        .table-responsive {{ 
            margin: 20px 0;
            box-shadow: 0 0 10px rgba(0,0,0,0.1);
            border-radius: 8px;
            overflow: hidden;
        }}
        .actions-column {{ white-space: nowrap; width: 150px; }}
        .navbar {{ 
            margin-bottom: 20px;
            box-shadow: 0 2px 4px rgba(0,0,0,0.1);
        }}
        .form-group {{ margin-bottom: 15px; }}
        .card {{ 
            border: none;
            box-shadow: 0 0 15px rgba(0,0,0,0.1);
            border-radius: 10px;
        }}
        .card-header {{
            background-color: #f8f9fa;
            border-bottom: 1px solid #eee;
            font-weight: 600;
        }}
        .list-group-item:hover {{
            background-color: #f8f9fa;
        }}
        .badge {{
            font-weight: normal;
        }}
        .home-icon {{
            color: #fff;
            font-size: 1.2rem;
            margin-right: 5px;
        }}
        .view-all-btn {{
            margin-left: 10px;
        }}
        .table th {{
            background-color: #f8f9fa;
            font-weight: 600;
        }}
        .table td {{
            vertical-align: middle;
        }}
        .alert {{
            border-radius: 8px;
        }}
        .scroll-to-top {{
            position: fixed;
            bottom: 20px;
            right: 20px;
            display: none;
            z-index: 1000;
        }}
    </style>
</head>
<body>
    <nav class="navbar navbar-expand-lg navbar-dark bg-primary">
        <div class="container">
            <a class="navbar-brand" href="/">
                <i class="fas fa-home home-icon"></i>Домой
            </a>
            <div class="navbar-nav">
                {'{% if "user" in session %}'}
                    <div class="dropdown">
                        <button class="btn btn-outline-light dropdown-toggle" type="button" 
                                id="userMenu" data-bs-toggle="dropdown">
                            {'{{ session["user"] }}'} ({'{{ session["role"] }}'})
                        </button>
                        <ul class="dropdown-menu">
                            <li><a class="dropdown-item" href="/logout">Выйти</a></li>
                        </ul>
                    </div>
                {'{% else %}'}
                    <a class="nav-link" href="/login">Войти</a>
                {'{% endif %}'}
            </div>
        </div>
    </nav>

    <div class="container">
        {'{% for category, message in get_flashed_messages(with_categories=true) %}'}
            <div class="alert alert-{'{{ "danger" if category == "error" else "success" }}'} alert-dismissible fade show">
                {'{{ message }}'}
                <button type="button" class="btn-close" data-bs-dismiss="alert"></button>
            </div>
        {'{% endfor %}'}

        {content}
    </div>

    <a href="#" class="btn btn-primary scroll-to-top" id="scrollToTop">
        <i class="fas fa-arrow-up"></i>
    </a>

    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.bundle.min.js"></script>
    <script>
        window.onscroll = function() {{
            var scrollToTopBtn = document.getElementById("scrollToTop");
            if (document.body.scrollTop > 20 || document.documentElement.scrollTop > 20) {{
                scrollToTopBtn.style.display = "block";
            }} else {{
                scrollToTopBtn.style.display = "none";
            }}
        }};

        document.getElementById("scrollToTop").addEventListener("click", function(e) {{
            e.preventDefault();
            window.scrollTo({{top: 0, behavior: 'smooth'}});
        }});
    </script>
</body>
</html>
'''

LOGIN_TEMPLATE = get_base_template('''
<div class="row justify-content-center">
    <div class="col-md-6">
        <div class="card">
            <div class="card-header">Вход в систему</div>
            <div class="card-body">
                <form method="POST">
                    <div class="mb-3">
                        <label for="username" class="form-label">Логин</label>
                        <input type="text" class="form-control" id="username" name="username" required>
                    </div>
                    <div class="mb-3">
                        <label for="password" class="form-label">Пароль</label>
                        <input type="password" class="form-control" id="password" name="password" required>
                    </div>
                    <button type="submit" class="btn btn-primary">Войти</button>
                </form>
            </div>
        </div>
    </div>
</div>
''')

INDEX_TEMPLATE = get_base_template('''
    <h1>Таблицы базы данных</h1>
    {% if tables %}
        <div class="list-group">
            {% for table in tables %}
                <a href="/table/{{ table }}" 
                   class="list-group-item list-group-item-action d-flex justify-content-between align-items-center">
                    {{ table }}
                    <span class="badge bg-primary rounded-pill">›</span>
                </a>
            {% endfor %}
        </div>
        <div class="mt-4">
            <a href="/view_all" class="btn btn-primary">
                <i class="fas fa-table"></i> Просмотреть все данные
            </a>
        </div>
    {% else %}
        <div class="alert alert-warning">Нет доступных таблиц</div>
    {% endif %}
''')

TABLE_TEMPLATE = get_base_template('''
    <div class="d-flex justify-content-between align-items-center mb-4">
        <h1>Таблица: {{ table_name }}</h1>
        <div>
            <a href="/view_all#{{ table_name }}" class="btn btn-info view-all-btn">
                <i class="fas fa-list"></i> В общем просмотре
            </a>
            {% if 'add' in permissions %}
                <a href="/add_row/{{ table_name }}" class="btn btn-success">
                    <i class="fas fa-plus"></i> Добавить запись
                </a>
            {% endif %}
        </div>
    </div>

    {% if rows %}
        <div class="table-responsive">
            <table class="table table-hover table-bordered">
                <thead class="table-light">
                    <tr>
                        {% for column in columns %}
                            <th>{{ column }}</th>
                        {% endfor %}
                        {% if 'edit' in permissions or 'delete' in permissions %}
                            <th class="actions-column">Действия</th>
                        {% endif %}
                    </tr>
                </thead>
                <tbody>
                    {% for row in rows %}
                        <tr>
                            {% for column in columns %}
                                <td>{{ row[column] if row[column] is not none else 'NULL' }}</td>
                            {% endfor %}
                            {% if 'edit' in permissions or 'delete' in permissions %}
                                <td class="actions-column">
                                    {% if 'edit' in permissions %}
                                        <a href="/edit_row/{{ table_name }}/{{ row[columns[0]] }}" 
                                           class="btn btn-sm btn-outline-primary" title="Редактировать">
                                           <i class="fas fa-edit"></i>
                                        </a>
                                    {% endif %}
                                    {% if 'delete' in permissions %}
                                        <a href="/delete_row/{{ table_name }}/{{ row[columns[0]] }}" 
                                           class="btn btn-sm btn-outline-danger" 
                                           onclick="return confirm('Удалить эту запись?')" title="Удалить">
                                           <i class="fas fa-trash"></i>
                                        </a>
                                    {% endif %}
                                </td>
                            {% endif %}
                        </tr>
                    {% endfor %}
                </tbody>
            </table>
        </div>
    {% else %}
        <div class="alert alert-info">Таблица пуста</div>
    {% endif %}
''')

VIEW_ALL_TEMPLATE = get_base_template('''
    <h1>Все данные базы данных</h1>
    {% if tables_data %}
        <div class="alert alert-info">
            <i class="fas fa-info-circle"></i> Отображается максимум {{ MAX_ROWS_TO_DISPLAY }} строк из каждой таблицы
        </div>
        {% for table_name, data in tables_data.items() %}
            <div class="mb-5" id="{{ table_name }}">
                <div class="d-flex justify-content-between align-items-center mb-3">
                    <h2>Таблица: {{ table_name }}</h2>
                    <div>
                        <a href="/table/{{ table_name }}" class="btn btn-sm btn-outline-primary">
                            <i class="fas fa-external-link-alt"></i> Открыть полностью
                        </a>
                        <span class="badge bg-secondary ms-2">
                            {{ data.rows|length }} строк
                        </span>
                    </div>
                </div>
                
                {% if data.rows %}
                    <div class="table-responsive">
                        <table class="table table-hover table-bordered">
                            <thead class="table-light">
                                <tr>
                                    {% for column in data.columns %}
                                        <th>{{ column }}</th>
                                    {% endfor %}
                                </tr>
                            </thead>
                            <tbody>
                                {% for row in data.rows %}
                                    <tr>
                                        {% for column in data.columns %}
                                            <td>{{ row[column] if row[column] is not none else 'NULL' }}</td>
                                        {% endfor %}
                                    </tr>
                                {% endfor %}
                            </tbody>
                        </table>
                    </div>
                {% else %}
                    <div class="alert alert-warning">
                        <i class="fas fa-exclamation-circle"></i> Таблица не содержит данных
                    </div>
                {% endif %}
            </div>
        {% endfor %}
    {% else %}
        <div class="alert alert-danger">
            <i class="fas fa-exclamation-triangle"></i> Не удалось загрузить данные из базы данных
        </div>
    {% endif %}
''')

EDIT_ROW_TEMPLATE = get_base_template('''
    <div class="card">
        <div class="card-header">
            <h2>{{ "Добавление" if action == "add" else "Редактирование" }} записи</h2>
        </div>
        <div class="card-body">
            <form method="POST" class="needs-validation" novalidate>
                {% for column in columns %}
                    <div class="mb-3">
                        {% set field_type = column['Type'] %}
                        {% set type_hint = 
                            'число' if 'int' in field_type|string or 'decimal' in field_type|string or 'float' in field_type|string else
                            'дата' if 'date' in field_type|string or 'time' in field_type|string else
                            'текст' %}
                        
                        <label for="{{ column['Field'] }}" class="form-label">
                            <strong>{{ column['Field'] }} ({{ type_hint }})</strong>
                        </label>
                        
                        {% if column['Null'] == 'NO' and column['Default'] is none and column['Extra'] == 'auto_increment' %}
                            <input type="text" class="form-control" id="{{ column['Field'] }}" 
                                   value="AUTO" disabled>
                        {% else %}
                            <input type="text" class="form-control" id="{{ column['Field'] }}" 
                                   name="{{ column['Field'] }}"
                                   value="{{ row[column['Field']] if row and column['Field'] in row else '' }}"
                                   {{ 'required' if column['Null'] == 'NO' and column['Default'] is none else '' }}>
                        {% endif %}
                    </div>
                {% endfor %}
                
                <div class="d-grid gap-2 d-md-flex justify-content-md-end mt-4">
                    <a href="/table/{{ table_name }}" class="btn btn-secondary me-md-2">
                        <i class="fas fa-times"></i> Отмена
                    </a>
                    <button type="submit" class="btn btn-primary">
                        <i class="fas fa-save"></i> {{ "Добавить" if action == "add" else "Сохранить" }}
                    </button>
                </div>
            </form>
        </div>
    </div>
''')