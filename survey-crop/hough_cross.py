import math

import numpy as np
from scipy.signal import convolve2d
from skimage.morphology import dilation, disk




def generate_cross(size, lw):
    assert size % 2 == 1

    center = math.floor(size/2.)
    cross = np.zeros([size, size])
    cross[center, :] = np.ones(size)
    cross[:, center] = np.ones(size)

    if lw != 0:
        cross = dilation(cross, disk(lw))
    
    return cross

def kernel_gaussian(d, sigma):
    return math.exp(-d/sigma**2)

def generate_cross_kernel(kernel_size, f_kernel, lw, angle, **kwargs):
    kernel = generate_cross(kernel_size, lw)

    dr = np.array([0.5, 0.5])
    center = np.array([math.floor(kernel_size/2.)]*2) + dr
    for x in range(kernel_size):
        for y in range(kernel_size):
            point = np.array([x, y]) + dr
            kernel[x, y] = kernel[x, y]*f_kernel(np.linalg.norm(point - center), **kwargs)

    return kernel

def hough_cross_convolve(edges, kernel_size=5, kernel_sigma=2., lw=1, angles=None):
    if angles is None:
        angles = [0.]

    kernels = [generate_cross_kernel(kernel_size, kernel_gaussian, lw, angle, sigma=kernel_sigma) for angle in angles]

    hough_space = np.zeros([len(angles), edges.shape[0], edges.shape[1]])
    for kernel, i in zip(kernels, range(len(angles))):
        hough_space[i] = convolve2d(edges, kernel, mode='same')

    return hough_space

from skimage.util import crop
from skimage.measure import label
import matplotlib.pyplot as plt

def hough_cross_connectivity(edges, kernel_size, lw=0., angles=None):
    def _hough(edges, kernel):
        hough_space = np.zeros(edges.shape)
        kernel_radius = math.floor(kernel_size/2.)
        for i in range(edges.shape[0]):
            xmin = i - kernel_radius - 1
            xmax = i + kernel_radius
            if xmin < 0 or xmax > edges.shape[0]:
                continue

            for j in range(edges.shape[1]):
                ymin = j - kernel_radius - 1
                ymax = j + kernel_radius
                if ymin < 0 or ymax > edges.shape[1]:
                    continue

                neighborhood = edges[xmin:xmax, ymin:ymax]
                labeled = label(kernel*neighborhood)
                value = labeled[kernel_radius, kernel_radius]

                if value == 0:
                    continue
                else:
                    hough_space[i, j] = np.sum(labeled == value)

        return hough_space

    if angles is None:
        angles = [0]

    kernels = [generate_cross(kernel_size, lw) for angle in angles]

    hough_space = np.zeros([len(angles), edges.shape[0], edges.shape[1]])
    for kernel, i in zip(kernels, range(len(angles))):
        hough_space[i] = _hough(edges, kernel)

    return hough_space




