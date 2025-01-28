import numpy as np
import matplotlib.pyplot as plt


X = np.linspace(-2, 2, 401)
leftX = []
leftY = []
rightX = []
rightY = []

for x in X:
    if x < -1.28:
        leftX.append(x)
        leftY.append((np.log(np.abs(x - 1) + 1) + np.tan(x * np.pi / 6)) / (x / 2 + 2 ** (x / 2)))
    else:
        rightX.append(x)
        rightY.append((np.log(np.abs(x - 1) + 1) + np.tan(x * np.pi / 6)) / (x / 2 + 2 ** (x / 2)))

Y = leftY + rightY
with open("res.txt", "w") as f:
    for i in range(len(X)):
        line = str(X[i]) + " " + str(Y[i]) + "\n"
        f.write(line)


plt.figure(figsize=(10, 6))
plt.plot(leftX, leftY, label=r'$\frac{\ln(|X-1|+1) + \tan\left(\frac{X \cdot \pi}{6}\right)}{X/2 + 2^{X/2}}$; x<-1.28')
plt.plot(rightX, rightY, label=r'$\frac{\ln(|X-1|+1) + \tan\left(\frac{X \cdot \pi}{6}\right)}{X/2 + 2^{X/2}}$; x>=-1.28')
plt.ylim(-10, 10)
plt.xlabel('X')
plt.ylabel('y')
plt.title('Plot of the given function')
plt.legend()
plt.grid(True)
plt.show()