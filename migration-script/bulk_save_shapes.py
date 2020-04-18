#!/usr/bin/python

import ogr,os
myDir = '/home/iomonad/Documents/Qgis/Backups/Shapes'

if os.path.exists (myDir) == False:
    print "Path does not exist"
else:
    for vLayer in iface.mapCanvas().layers():
        if vLayer.type() == 0:
            QgsVectorFileWriter.writeAsVectorFormat(vLayer, myDir + vLayer.name() + ".shp", "utf-8", vLayer.crs(),  "ESRI Shapefile")
            print vLayer.name() + " saved successfully"
