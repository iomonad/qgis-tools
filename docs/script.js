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


if (localStorage.getItem('centrales') == null) {
    let dataset_path = "https://trosa.io/qgis-tools/data/poste-source.json"
    fetch(dataset_path)
	.then((data) => {
	    localStorage.setItem('centrales', data.json());
	    data.json().map(feature => centrale_layer.addData(feature));
	})
	.catch ((err) => {
	    console.log(err);
	});
}
