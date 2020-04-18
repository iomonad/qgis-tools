#
# Nomalize PTT Data
# (c) iomonad <iomonad@riseup.net>
#

FALLBACK_NAME = "Trappe d'accès"

RDLR = [
    'car',
    'rdlr',
    'rectangle'
    'carre'
]

NORINCO = [
    'triangle',
    'norinco',
]

layer = iface.activeLayer()

layer.startEditing()
for feature in layer.getFeatures():
    feat = QgsFeature(layer.fields())
    if not feature['name']:
         layer.changeAttributeValue(feature.id(), 0, FALLBACK_NAME)
         continue
    layer.changeAttributeValue(feature.id(), 0, str(feature['name']).strip().capitalize().replace('ces', 'cès'))
    if 'Trappes' in feature['name']:
        layer.changeAttributeValue(feature.id(), 0, str(feature['name']).replace('Trappes', 'Trappe'))
    print (feature['name'])
    if any(x in str(feature['name']).lower() for x in NORINCO):
        layer.changeAttributeValue(feature.id(), 3, "Norinco")
        layer.changeAttributeValue(feature.id(), 0, FALLBACK_NAME)
    if any(x in str(feature['name']).lower() for x in RDLR):
        layer.changeAttributeValue(feature.id(), 3, "RDLR")
        layer.changeAttributeValue(feature.id(), 0, FALLBACK_NAME)
    if not feature['type']:
        layer.changeAttributeValue(feature.id(), 3, "Generique")

layer.updateFields()