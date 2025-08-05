import numpy as np
import matplotlib.pyplot as plt
from numba import jit
from PyQt5.QtWidgets import (QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
                             QLabel, QListWidget, QListWidgetItem, QPushButton,
                             QStatusBar, QFrame, QGridLayout, QAction, QSizePolicy,
                             QButtonGroup, QRadioButton)
from PyQt5.QtCore import Qt, QSize
from PyQt5.QtGui import QFont, QColor, QIcon, QKeySequence
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.figure import Figure


@jit(nopython=True)

def compute_julia(c_real, c_imag, width, height, xmin, xmax, ymin, ymax, max_iter):
    # Инициализация матрицы результатов
    image = np.zeros((height, width))

    # Перебор всех пикселей изображения
    for x in range(width):
        for y in range(height):
            # Преобразование координат пикселя в плоскость
            zx = xmin + (xmax - xmin) * x / (width - 1)
            zy = ymin + (ymax - ymin) * y / (height - 1)
            # Итерационный процесс
            for i in range(max_iter):
                # Вычисление нового значения
                zx_new = zx * zx - zy * zy + c_real
                zy_new = 2 * zx * zy + c_imag
                # Проверка условия "убегания"
                if zx_new * zx_new + zy_new * zy_new > 4:
                    image[y, x] = i  # Запоминаем количество итераций
                    break
                zx, zy = zx_new, zy_new
            else:
                # Если не вышли за границу за max_iter итераций
                image[y, x] = max_iter

    return image


class JuliaFractalApp(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Исследователь фракталов Жюлиа")
        self.setGeometry(100, 100, 1200, 900)

        # Цветовая схема
        self.bg_color = QColor(40, 44, 52)
        self.panel_color = QColor(33, 37, 43)
        self.text_color = QColor(220, 220, 220)
        self.accent_color = QColor(62, 166, 255)
        self.highlight_color = QColor(75, 80, 90)
        self.button_color = QColor(50, 54, 60)
        self.radio_color = QColor(60, 64, 72)

        # Пресеты фракталов
        self.fractals = {
            "Классический": {"c_real": -0.7, "c_imag": 0.27, "zoom": (-2, 2, -2, 2), "cmap": "magma", "iter": 150},
            "Дендрит": {"c_real": 0, "c_imag": 1, "zoom": (-2, 2, -2, 2), "cmap": "viridis", "iter": 100},
            "Спираль": {"c_real": -0.4, "c_imag": 0.6, "zoom": (-2, 2, -2, 2), "cmap": "plasma", "iter": 120},
            "Морской конек": {"c_real": -0.8, "c_imag": 0.156, "zoom": (-1.5, 1.5, -1.5, 1.5), "cmap": "inferno",
                              "iter": 130},
            "Снежинка": {"c_real": -0.123, "c_imag": 0.745, "zoom": (-1, 1, -1, 1), "cmap": "cividis", "iter": 140},
            "Галактика": {"c_real": -0.75, "c_imag": 0.11, "zoom": (-1.8, 1.8, -1.8, 1.8), "cmap": "twilight",
                          "iter": 160},
            "Паутина": {"c_real": -0.5, "c_imag": 0.55, "zoom": (-2, 2, -2, 2), "cmap": "bone", "iter": 110}
        }

        self.current_zoom = (-2, 2, -2, 2)
        self.current_fractal = "Классический"
        self.move_step = 0.2
        self.setup_ui()
        self.generate_fractal()

    def setup_ui(self):
        central_widget = QWidget()
        central_widget.setStyleSheet(f"background-color: {self.bg_color.name()};")
        self.setCentralWidget(central_widget)

        main_layout = QHBoxLayout(central_widget)
        main_layout.setContentsMargins(0, 0, 0, 0)
        main_layout.setSpacing(0)

        # Левая панель (фиксированная ширина 300px)
        left_panel = QFrame()
        left_panel.setStyleSheet(f"""
            background-color: {self.panel_color.name()};
            border-right: 1px solid {self.highlight_color.name()};
        """)
        left_panel.setFixedWidth(300)
        left_panel.setSizePolicy(QSizePolicy.Fixed, QSizePolicy.Expanding)

        left_layout = QVBoxLayout(left_panel)
        left_layout.setContentsMargins(15, 15, 15, 15)
        left_layout.setSpacing(20)

        # Заголовок
        title = QLabel("Фракталы Жюлиа")
        title.setStyleSheet(f"""
            color: {self.accent_color.name()};
            font-size: 20px;
            font-weight: bold;
            padding-bottom: 10px;
            border-bottom: 2px solid {self.highlight_color.name()};
        """)
        left_layout.addWidget(title)

        # Выбор фрактала 
        fractal_group = QFrame()
        fractal_group.setStyleSheet(f"background-color: {self.panel_color.name()};")
        fractal_layout = QVBoxLayout(fractal_group)
        fractal_layout.setContentsMargins(0, 0, 0, 0)
        fractal_layout.setSpacing(10)

        fractal_label = QLabel("Выберите фрактал:")
        fractal_label.setStyleSheet(f"color: {self.text_color.name()}; font-size: 14px;")
        fractal_layout.addWidget(fractal_label)

        self.fractal_buttons = QButtonGroup()
        for i, name in enumerate(self.fractals.keys()):
            btn = QRadioButton(name)
            btn.setStyleSheet(f"""
                QRadioButton {{
                    color: {self.text_color.name()};
                    font-size: 14px;
                    padding: 8px;
                    border-radius: 4px;
                }}
                QRadioButton::indicator {{
                    width: 16px;
                    height: 16px;
                }}
                QRadioButton:hover {{
                    background-color: {self.highlight_color.name()};
                }}
            """)
            if i == 0:
                btn.setChecked(True)
            self.fractal_buttons.addButton(btn, i)
            fractal_layout.addWidget(btn)

        self.fractal_buttons.buttonClicked.connect(self.on_fractal_selected)
        left_layout.addWidget(fractal_group)

        # Панель навигации
        nav_group = QFrame()
        nav_group.setStyleSheet(f"background-color: {self.panel_color.name()};")
        nav_layout = QVBoxLayout(nav_group)
        nav_layout.setContentsMargins(0, 0, 0, 0)
        nav_layout.setSpacing(10)

        nav_label = QLabel("Навигация:")
        nav_label.setStyleSheet(f"color: {self.text_color.name()}; font-size: 14px;")
        nav_layout.addWidget(nav_label)

        # Сетка для кнопок навигации
        grid_frame = QFrame()
        grid_layout = QGridLayout(grid_frame)
        grid_layout.setContentsMargins(0, 0, 0, 0)
        grid_layout.setSpacing(5)

        # Стиль для кнопок
        button_style = f"""
            QPushButton {{
                background-color: {self.button_color.name()};
                color: {self.text_color.name()};
                border: 1px solid {self.highlight_color.name()};
                border-radius: 4px;
                font-size: 16px;
                font-weight: bold;
                min-width: 45px;
                max-width: 45px;
                min-height: 45px;
            }}
            QPushButton:hover {{
                background-color: {self.highlight_color.name()};
            }}
            QPushButton:pressed {{
                background-color: {self.accent_color.name()};
                color: white;
            }}
        """

        # Центральная кнопка (домой)
        self.home_btn = QPushButton("⌂")
        self.home_btn.setStyleSheet(button_style)
        self.home_btn.setToolTip("Вернуться к исходному виду (H)")
        self.home_btn.clicked.connect(self.reset_view)
        grid_layout.addWidget(self.home_btn, 1, 1)

        # Кнопки навигации
        self.move_up_btn = QPushButton("↑")
        self.move_up_btn.setStyleSheet(button_style)
        self.move_up_btn.setToolTip("Вверх (↑)")
        self.move_up_btn.clicked.connect(lambda: self.move_fractal(0, -1))
        grid_layout.addWidget(self.move_up_btn, 0, 1)

        self.move_left_btn = QPushButton("←")
        self.move_left_btn.setStyleSheet(button_style)
        self.move_left_btn.setToolTip("Влево (←)")
        self.move_left_btn.clicked.connect(lambda: self.move_fractal(-1, 0))
        grid_layout.addWidget(self.move_left_btn, 1, 0)

        self.move_right_btn = QPushButton("→")
        self.move_right_btn.setStyleSheet(button_style)
        self.move_right_btn.setToolTip("Вправо (→)")
        self.move_right_btn.clicked.connect(lambda: self.move_fractal(1, 0))
        grid_layout.addWidget(self.move_right_btn, 1, 2)

        self.move_down_btn = QPushButton("↓")
        self.move_down_btn.setStyleSheet(button_style)
        self.move_down_btn.setToolTip("Вниз (↓)")
        self.move_down_btn.clicked.connect(lambda: self.move_fractal(0, 1))
        grid_layout.addWidget(self.move_down_btn, 2, 1)

        nav_layout.addWidget(grid_frame)
        left_layout.addWidget(nav_group)

        # Панель масштабирования
        zoom_group = QFrame()
        zoom_group.setStyleSheet(f"background-color: {self.panel_color.name()};")
        zoom_layout = QVBoxLayout(zoom_group)
        zoom_layout.setContentsMargins(0, 0, 0, 0)
        zoom_layout.setSpacing(10)

        zoom_label = QLabel("Масштабирование:")
        zoom_label.setStyleSheet(f"color: {self.text_color.name()}; font-size: 14px;")
        zoom_layout.addWidget(zoom_label)

        btn_frame = QFrame()
        btn_layout = QHBoxLayout(btn_frame)
        btn_layout.setContentsMargins(0, 0, 0, 0)
        btn_layout.setSpacing(8)

        self.zoom_out_btn = QPushButton("-")
        self.zoom_out_btn.setStyleSheet(button_style)
        self.zoom_out_btn.setToolTip("Уменьшить (-)")
        self.zoom_out_btn.clicked.connect(self.zoom_out)

        self.zoom_in_btn = QPushButton("+")
        self.zoom_in_btn.setStyleSheet(button_style)
        self.zoom_in_btn.setToolTip("Увеличить (+)")
        self.zoom_in_btn.clicked.connect(self.zoom_in)

        self.reset_btn = QPushButton("Сброс")
        self.reset_btn.setStyleSheet(f"""
            QPushButton {{
                background-color: {self.button_color.name()};
                color: {self.text_color.name()};
                border: 1px solid {self.highlight_color.name()};
                border-radius: 4px;
                padding: 10px 15px;
                font-size: 14px;
                min-height: 45px;
            }}
            QPushButton:hover {{
                background-color: {self.highlight_color.name()};
            }}
            QPushButton:pressed {{
                background-color: {self.accent_color.name()};
            }}
        """)
        self.reset_btn.setToolTip("Сбросить вид (R)")
        self.reset_btn.clicked.connect(self.reset_view)

        btn_layout.addWidget(self.zoom_out_btn)
        btn_layout.addWidget(self.zoom_in_btn)
        btn_layout.addWidget(self.reset_btn)
        zoom_layout.addWidget(btn_frame)
        left_layout.addWidget(zoom_group)

        left_layout.addStretch()

        # Правая панель (график)
        self.figure = Figure(facecolor=self.bg_color.name())
        self.canvas = FigureCanvas(self.figure)
        self.canvas.setStyleSheet(f"background-color: {self.bg_color.name()};")
        self.ax = self.figure.add_subplot(111)

        # Включаем обработку событий мыши
        self.canvas.mpl_connect('button_press_event', self.on_click)
        self.canvas.mpl_connect('scroll_event', self.on_scroll)

        main_layout.addWidget(left_panel)
        main_layout.addWidget(self.canvas)

        # Статус бар
        self.status_bar = QStatusBar()
        self.status_bar.setStyleSheet(f"""
            QStatusBar {{
                background-color: {self.panel_color.name()};
                color: {self.text_color.name()};
                font-size: 12px;
                border-top: 1px solid {self.highlight_color.name()};
            }}
        """)
        self.setStatusBar(self.status_bar)

        # Настройка горячих клавиш
        self.setup_shortcuts()

    def setup_shortcuts(self):
        # Горячие клавиши для навигации
        self.action_up = QAction(self)
        self.action_up.setShortcut(QKeySequence(Qt.Key_Up))
        self.action_up.triggered.connect(lambda: self.move_fractal(0, -1))
        self.addAction(self.action_up)

        self.action_down = QAction(self)
        self.action_down.setShortcut(QKeySequence(Qt.Key_Down))
        self.action_down.triggered.connect(lambda: self.move_fractal(0, 1))
        self.addAction(self.action_down)

        self.action_left = QAction(self)
        self.action_left.setShortcut(QKeySequence(Qt.Key_Left))
        self.action_left.triggered.connect(lambda: self.move_fractal(-1, 0))
        self.addAction(self.action_left)

        self.action_right = QAction(self)
        self.action_right.setShortcut(QKeySequence(Qt.Key_Right))
        self.action_right.triggered.connect(lambda: self.move_fractal(1, 0))
        self.addAction(self.action_right)

        self.action_zoom_in = QAction(self)
        self.action_zoom_in.setShortcut(QKeySequence(Qt.Key_Plus))
        self.action_zoom_in.triggered.connect(self.zoom_in)
        self.addAction(self.action_zoom_in)

        self.action_zoom_out = QAction(self)
        self.action_zoom_out.setShortcut(QKeySequence(Qt.Key_Minus))
        self.action_zoom_out.triggered.connect(self.zoom_out)
        self.addAction(self.action_zoom_out)

        self.action_reset = QAction(self)
        self.action_reset.setShortcut(QKeySequence(Qt.Key_R))
        self.action_reset.triggered.connect(self.reset_view)
        self.addAction(self.action_reset)

        self.action_home = QAction(self)
        self.action_home.setShortcut(QKeySequence(Qt.Key_H))
        self.action_home.triggered.connect(self.reset_view)
        self.addAction(self.action_home)

    def on_fractal_selected(self, button):
        self.current_fractal = button.text()
        self.current_zoom = self.fractals[self.current_fractal]["zoom"]
        self.generate_fractal()

    def on_click(self, event):
        if event.inaxes == self.ax:
            if event.dblclick:
                self.zoom_at_point(event.xdata, event.ydata, 2.0)

    def on_scroll(self, event):
        if event.inaxes == self.ax:
            factor = 1.1 if event.button == 'up' else 1 / 1.1
            self.zoom_at_point(event.xdata, event.ydata, factor)

    def zoom_at_point(self, x, y, factor):
        xmin, xmax, ymin, ymax = self.current_zoom
        width = (xmax - xmin) / factor
        height = (ymax - ymin) / factor

        self.current_zoom = (
            x - width / 2,
            x + width / 2,
            y - height / 2,
            y + height / 2
        )
        self.generate_fractal()

    def move_fractal(self, dx, dy):
        xmin, xmax, ymin, ymax = self.current_zoom
        width = xmax - xmin
        height = ymax - ymin

        # Вычисляем шаг перемещения (20% от текущего размера)
        step_x = width * self.move_step
        step_y = height * self.move_step

        # Обновляем границы
        self.current_zoom = (
            xmin + dx * step_x,
            xmax + dx * step_x,
            ymin + dy * step_y,
            ymax + dy * step_y
        )
        self.generate_fractal()

    def zoom_in(self):
        self.zoom(1.3)

    def zoom_out(self):
        self.zoom(1 / 1.3)

    def zoom(self, factor):
        xmin, xmax, ymin, ymax = self.current_zoom
        x_center = (xmin + xmax) / 2
        y_center = (ymin + ymax) / 2

        # Вычисляем новые размеры
        width = (xmax - xmin) / factor
        height = (ymax - ymin) / factor

        # Обновляем границы с сохранением центра
        self.current_zoom = (
            x_center - width / 2,
            x_center + width / 2,
            y_center - height / 2,
            y_center + height / 2
        )
        self.generate_fractal()

    def reset_view(self):
        if self.current_fractal in self.fractals:
            self.current_zoom = self.fractals[self.current_fractal]["zoom"]
            self.generate_fractal()

    def generate_fractal(self):
        fractal = self.fractals[self.current_fractal]
        xmin, xmax, ymin, ymax = self.current_zoom

        self.status_bar.showMessage(f"Генерация: {self.current_fractal}...")
        QApplication.processEvents()

        img = compute_julia(
            fractal["c_real"], fractal["c_imag"],
            800, 800,
            xmin, xmax, ymin, ymax,
            fractal["iter"]
        )

        self.ax.clear()
        self.ax.imshow(img, cmap=fractal["cmap"], extent=(xmin, xmax, ymin, ymax))

        self.ax.set_title(self.current_fractal, color=self.text_color.name(), pad=15, fontsize=14)
        self.ax.set_xlabel('', color=self.text_color.name(), fontsize=12)
        self.ax.set_ylabel('', color=self.text_color.name(), fontsize=12)

        self.ax.tick_params(colors=self.text_color.name(), labelsize=10)
        for spine in self.ax.spines.values():
            spine.set_color(self.text_color.name())

        self.ax.set_facecolor(self.bg_color.name())
        self.figure.tight_layout()
        self.canvas.draw()

        self.status_bar.showMessage(f"Готово: {self.current_fractal}")


if __name__ == "__main__":
    app = QApplication([])
    app.setStyle('Fusion')

    font = QFont("Segoe UI", 10)
    app.setFont(font)

    window = JuliaFractalApp()
    window.show()
    app.exec_()


def generate_fractal(self):
    # Получаем параметры текущего фрактала
    fractal = self.fractals[self.current_fractal]

    # Обновляем статус
    self.status_bar.showMessage(f"Генерация: {self.current_fractal}...")
    QApplication.processEvents()  # Для обновления

    # Вычисляем фрактал
    img = compute_julia(
        fractal["c_real"], fractal["c_imag"],
        800, 800,  # Фиксированный размер
        *self.current_zoom,
        fractal["iter"]
    )

    # Отрисовка
    self.ax.clear()
    self.ax.imshow(img, cmap=fractal["cmap"], extent=self.current_zoom)

    # Настройка отображения
    self.ax.set_title(self.current_fractal, color=self.text_color.name())
    self.figure.tight_layout()
    self.canvas.draw()

    # Обновление статуса
    self.status_bar.showMessage(f"Готово: {self.current_fractal}")