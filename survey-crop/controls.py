import numpy
import pickle
import sys
import os
import glob
from os import path

import matplotlib
import matplotlib.pyplot as plt
from skimage import io

def sample_controls(imagename):
    image = io.imread(imagename)

    points = []

    def onclick(event):
        if str(event.button) == 'MouseButton.RIGHT':
            print("Adding point ({x}, {y})".format(x=event.xdata, y=event.ydata))
            points.append((event.xdata, event.ydata))

    fig, ax = plt.subplots()
    cid = fig.canvas.mpl_connect('button_press_event', onclick)
    
    plt.imshow(image)
    plt.show()

    if len(points) != 35:
        return

    filename, _ = os.path.splitext(imagename)
    out_filename = filename + ".pickle"
    print("Saving into {out_filename}".format(out_filename=out_filename))
    pickle.dump(points, open(out_filename, 'wb'))


in_files = [f for f in glob.glob(sys.argv[1], recursive=False)]
print("{count} matching files have been found.".format(count=len(in_files)))

files = []

for f in in_files:
    filename, _ = os.path.splitext(f)
    if not path.exists(filename + ".pickle"):
        files.append(f)
    
print("Of which {count} are missing their control file.".format(count=len(files)))

for f in files:
    print("Sampling controls from file {filename}".format(filename=f))
    sample_controls(f)

