#!/usr/bin/python3
#
# Small script to export to Geojson that
# will be re-exploited in android application for
# offline survey mapping.
#

import unidecode

VECTOR_TYPE = 0
SAVE_PATH = '/home/iomonad/Work/com.github/underground'

for l in filter(lambda a: a.type() == VECTOR_TYPE,
        iface.mapCanvas().layers()):
    QgsVectorFileWriter.writeAsVectorFormat(l,
        unidecode.unidecode(
            SAVE_PATH + l.name().lower()
            + ".geojson"
            .replace(" ", "_").replace("-", "")
            .replace("(", "").replace(")", "")
        ), "utf-8", l.crs(),  "GeoJSON"
    )
    print (l.name() + "saved to geojson")
