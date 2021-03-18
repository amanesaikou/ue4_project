import cv2
import numpy as np

img = cv2.imread('test6.jpg')
hsv = cv2.cvtColor(img, cv2.COLOR_RGB2HSV)

a = np.zeros((252, 257), dtype=np.uint8)
for i in range(len(img)):
    for j in range(len(img[0])):
        if img[i][j][0] > 15 and img[i][j][1] > 15 and img[i][j][2] > 15:
            a[i][j] = 255

b, g, r = cv2.split(img)

bgra = cv2.merge([b, g, r, a])
cv2.imwrite('t6.png', bgra)

