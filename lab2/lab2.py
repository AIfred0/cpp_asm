import matplotlib.pyplot as plt


# получим объект файла
file = open("result.txt", "r")

x, y = [], []

while True:
    # считываем строку
    line = file.readline()
    # прерываем цикл, если строка пустая
    if not line:
        break
    # выводим строку
    x.append(float(line.split()[0])) 
    y.append(float(line.split()[1]))

# закрываем файл
file.close

plt.figure(figsize=(10, 6))

plt.plot(x, y, label=r'$\frac{\sin(X * 100)}{X}$')
plt.ylim(0, 30)
plt.xlabel('Кол-во шагов')
plt.ylabel('Значение интеграла')
plt.title('Вычисление интеграла путем левых прямоугольников')
plt.legend()
plt.grid(True)
plt.show()
