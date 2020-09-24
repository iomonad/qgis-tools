import time
import pickle
import sys
import os

import numpy as np
from numba import njit, prange
from skimage import io
from skimage.transform import warp

from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt

output_shape = (3540, 2350)
out_format = ".tga"

def gen_triangles():
    triangles = []
    for j in range(4):
        for i in range(6):
            triangle_0 = (i+j*7, i+1+j*7, 7*(j+1)+i)
            triangle_1 = (i+1+j*7, 7*(j+1)+i+1, 7*(j+1)+i)
            triangles.append(triangle_0)
            triangles.append(triangle_1)

    return tuple(triangles)


def gen_points():
    grid_x, grid_y = np.meshgrid(np.linspace(0., output_shape[0], 7),
                                 np.linspace(0., output_shape[1], 5))

    return np.stack([grid_x, grid_y]).reshape(2, -1).T


@njit(fastmath=False)
def inverse(p, points_in, points_out):
    for tri in tris:
        v0 = points_out[tri[0]]
        v1 = points_out[tri[1]]
        v2 = points_out[tri[2]]

        A = np.array([[v1[0]-v0[0], v2[0]-v0[0]],
                      [v1[1]-v0[1], v2[1]-v0[1]]])
        Y = p-v0
        alphas = np.linalg.solve(A, Y)
        lambdas = np.array([alphas[0], alphas[1], 1.-alphas[0]-alphas[1]])

        if lambdas[0] < 0 or lambdas[1] < 0 or lambdas[2] < 0:
            continue
        else:
            A = np.array([[v0[0], v1[0], v2[0]],
                          [v0[1], v1[1], v2[1]],
                          [1., 1., 1.]])
            Y = np.array([p[0], p[1], 1])
            lambdas = np.linalg.solve(A, Y)

            c0 = points_in[tri[0]]
            c1 = points_in[tri[1]]
            c2 = points_in[tri[2]]

            return lambdas[0]*c0+lambdas[1]*c1+lambdas[2]*c2


@njit(parallel=False)
def inverse_map(p, points_in, points_out):
    out = np.empty_like(p)

    for i in prange(p.shape[0]):
        out[i] = inverse(p[i], points_in, points_out)

    return out


in_filename = sys.argv[1]
filename, _ = os.path.splitext(in_filename)

image = io.imread(in_filename)

tris = gen_triangles()
points_in = np.array(pickle.load(open(filename+".pickle", 'rb')))
points_out = gen_points()

print("Warping...")
start = time.perf_counter()
output_image = warp(image, inverse_map, map_args={'points_in': points_in, 'points_out': points_out}, output_shape=(output_shape[1], output_shape[0]))
print("Elapsed: {elapsed}".format(elapsed=time.perf_counter()-start))

out_filename = filename.split('_')[1] + out_format
io.imsave(out_filename, output_image)
print("Saved as {out_filename}".format(out_filename=out_filename))

