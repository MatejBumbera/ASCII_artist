import cv2
import matplotlib.pyplot as pl

img = cv2.imread('.//ox-arch.jpg', 0)
for row in img:
    for i in range(len(row)):
        if row[i] >= 225:
            row[i] = 255

pl.imshow(img, cmap='gray')
pl.show()
