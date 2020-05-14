#!/usr/bin/python3
#
# Small script to export to Geojson that
# will be re-exploited in android application for
# offline survey mapping.
#

import unidecode

VECTOR_TYPE = 0
SAVE_PATH = '/home/iomonad/Work/com.github/underground/'
RPATTERNS = {" ": "_", "-": "", "(": "", ")": ""}
    
def regularize_androidres_name(lname):
    name = unidecode.unidecode(lname.name().lower())
    for k, v in RPATTERNS.items():
        name = name.replace(k, v)
    return SAVE_PATH + name + ".geojson"

for l in filter(lambda a: a.type() == VECTOR_TYPE,
        iface.mapCanvas().layers()):
    QgsVectorFileWriter.writeAsVectorFormat(l,
        regularize_androidres_name(l), 
        "utf-8", l.crs(),  "GeoJson"
    )
    print (l.name() + " saved to geojson")
