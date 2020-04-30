#!/usr/bin/python
#-----------------------------------------------
# (c) iomonad
#
# Usage: ARGV[1] should be the project root path.
# Note: The 'length_km' should be present in
#       your shapefile attribute and be defined
#       as "$length / 1000"
# -----------------------------------------------

import sys
import shapefile

resources = [
    {'name': "EDF/RTE HTB",
     'file': "Shapes/Concessionaires/EDF_Enedis/" },
    {'name': "PTT / France Telecom",
     'file': "Shapes/Concessionaires/PTT_Telecom/"
    }
]

for concess in resources:
    path = "{}/{}/Galeries_Souterraines.shp".format(sys.argv[1], concess['file'])
    with shapefile.Reader(path) as shp:
        sel = *map(lambda k: k['length_km'], shp.records()),
        res = round(sum(sel), 2)
        print ("{:25.25}: {} km".format(concess['name'], res))
