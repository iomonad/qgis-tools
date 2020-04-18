#
# Nomalize PTT Data
# (c) iomonad <iomonad@riseup.net>
#

FALLBACK_NAME = "Trappe d'accès"

TRAPPE = [
    'trappe'
    'trape'
]

TAMPON = [
    'tampon',
    'plaque',
]

SERRURE = [
    'thirard',
    'deny',
    'dény'
]

layer = iface.activeLayer()

layer.startEditing()
for feature in layer.getFeatures():
    if not feature['name']:
         layer.changeAttributeValue(feature.id(), 0, FALLBACK_NAME)
         continue
    layer.changeAttributeValue(feature.id(), 0, str(feature['name']).strip().capitalize())
    print (feature['name'])
    if any(x in str(feature['name']).lower() for x in TRAPPE):
        layer.changeAttributeValue(feature.id(), 2, "Trappe")
        layer.changeAttributeValue(feature.id(), 0, FALLBACK_NAME)
    if any(x in str(feature['name']).lower() for x in TAMPON):
        layer.changeAttributeValue(feature.id(), 2, "Tampon")
        layer.changeAttributeValue(feature.id(), 0, "Tampon d'accès")
        if 'pas de grille' in str(feature['descriptio']).lower():
            layer.changeAttributeValue(feature.id(), 4, 0)
        else:
            layer.changeAttributeValue(feature.id(), 4, 1)
    if 'thirard' in str(feature['descriptio']).lower():
        layer.changeAttributeValue(feature.id(), 3, "Thirard")
    if 'deny' in str(feature['descriptio']).lower().replace('é', 'e'):
        layer.changeAttributeValue(feature.id(), 3, "Dény")
layer.updateFields()