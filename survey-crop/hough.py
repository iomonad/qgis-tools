import time
import sys
import os
import math

import numpy as np
from skimage.color import rgb2grey
from skimage.transform import hough_line, hough_line_peaks, probabilistic_hough_line
from skimage.feature import canny
from skimage.filters import prewitt
from skimage import io
from skimage.morphology import dilation, disk
import matplotlib.pyplot as plt

from hough_cross import hough_cross_connectivity


def edge_detector(image):
    return prewitt(image)

in_filename = sys.argv[1]
filename, _ = os.path.splitext(in_filename)

image = io.imread(in_filename)

start = time.perf_counter()
greyscale = rgb2grey(image)
print("Greyscale. Elapsed time={elapsed}".format(elapsed=time.perf_counter() - start))

start = time.perf_counter()
edges = edge_detector(greyscale)
print("Edge detection. Elapsed time={elapsed}".format(elapsed=time.perf_counter() - start))

plt.imshow(edges, cmap='gray')
plt.show()

exit()

start = time.perf_counter()
hough_space = hough_cross_connectivity(edges, kernel_size=11, lw=0)
print("Hough transform. Elapsed time={elapsed}".format(elapsed=time.perf_counter() - start))

plt.subplot(1, 2, 1)
plt.imshow(hough_space, cmap='gray')

plt.subplot(1, 2, 2)
plt.imshow(image)

plt.show()

# thetas = np.linspace(-math.pi/2., math.pi/2., 360)

# start = time.perf_counter()
# hough_space, thetas, d = hough_line(edges, theta=thetas)
# print("Hough transform. Elapsed time={elapsed}".format(elapsed=time.perf_counter() - start))

# _, lines_angles, lines_distances = hough_line_peaks(hough_space, thetas, d)

# origin = np.array([0., image.shape[1]])
# lines = [(origin, (distance - origin * np.cos(angle))/np.sin(angle)) for distance, angle in zip(lines_distances, lines_angles)]

# print(lines)


# start = time.perf_counter()
# lines = probabilistic_hough_line(edges, threshold=500, line_length=300, line_gap=10)
# print("Hough transform. Elapsed time={elapsed}".format(elapsed=time.perf_counter() - start))
# print("{count} lines found.".format(count=len(lines)))

# plt.imshow(image)

# for line in lines:
#     p0, p1 = line
#     plt.plot((p0[0], p1[0]), (p0[1], p1[1]), '--', color='xkcd:red', lw=2.)

# plt.show()

