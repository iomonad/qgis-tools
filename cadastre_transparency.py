#
# (c) iomonad <iomonad@riseup.net>
#
# Small hack to set layer transparency
# of french `Cadastre` layer to half.

layers = QgsProject.instance().mapLayers()

OPACITY = 0.5

for id, layer in layers.items():
    if "cadastre-" in layer.name():
        layer.setOpacity(OPACITY)