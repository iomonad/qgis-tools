#
# Nomalize PTT Data
# (c) iomonad <iomonad@riseup.net>
#

layer = iface.activeLayer()

layer.startEditing()
for feature in layer.getFeatures():
    if not feature['name']:
        layer.changeAttributeValue(feature.id(), 1, "Galerie PTT")
layer.updateFields()