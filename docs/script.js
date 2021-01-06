//
// (c) iomonad <iomonad@riseup.net>
// See: https://github.com/iomonad/qgis-tools
//

var mapview = L.map('mapid').setView([48.860, 2.333], 14);
var centrale_layer = L.geoJSON().addTo(mapview);

L.tileLayer('https://basemaps.cartocdn.com/light_all/{z}/{x}/{y}.png', {
    maxZoom: 18,
    attribution: '',
    id: 'mapbox/streets-v11',
    tileSize: 512,
    zoomOffset: -1
}).addTo(mapview);


const dataset = [
    {
	"name": "centrales",
	"path": "https://trosa.io/qgis-tools/data/poste-source.json"
    }
]

for (const d in dataset) {
    if (localStorage.getItem(d.name) == null) {
	fetch(d.path)
	    .then(res => res.json())
	    .then((data) => {
		localStorage.setItem(d.name, data);
		data.features.map(feature => centrale_layer.addData(feature));
	    })
	    .catch ((err) => {
		console.log(err);
	    });
    } else {
	const data = localStorage.getItem(d.name);
	data.features.map(feature => centrale_layer.addData(feature));
    }
}
