#
# Nomalize Data
# (c) iomonad <iomonad@riseup.net>
#

FALLBACK_NAME = "Trappe d'accès"

layer = iface.activeLayer()

layer.startEditing()
for feature in layer.getFeatures():
    if not feature['name']:
         layer.changeAttributeValue(feature.id(), 0, FALLBACK_NAME)
         continue
    layer.changeAttributeValue(feature.id(), 0, str(feature['name']).strip().capitalize())
    if "trappe" in str(feature['name']).lower() or "plaque" in str(feature['name']).lower():
        layer.changeAttributeValue(feature.id(), 3, str("Abloy"))
        layer.changeAttributeValue(feature.id(), 2, str("Trappe"))
    if "porte" in str(feature['name']).lower():
        layer.changeAttributeValue(feature.id(), 2, str("Porte"))
    if "pep" in str(feature['name']).lower():
        if feature['descriptio'] and "pep" in str(feature['descriptio']).lower():
            layer.changeAttributeValue(feature.id(), 4, str("PEP"))
        layer.changeAttributeValue(feature.id(), 4, str("PEP"))
    if "ventil" in str(feature['name']).lower():
        if feature['descriptio'] and "ventilation" in str(feature['descriptio']).lower():
            layer.changeAttributeValue(feature.id(), 4, str("VT"))
        layer.changeAttributeValue(feature.id(), 4, str("VT"))
    print (feature['name'])

layer.updateFields()