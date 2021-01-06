//
// (c) iomonad <iomonad@riseup.net>
// See: https://github.com/iomonad/qgis-tools
//

var mapview = L.map('mapid').setView([48.860, 2.333], 14);

L.tileLayer('https://basemaps.cartocdn.com/dark_all/{z}/{x}/{y}.png', {
    maxZoom: 18,
    attribution: '',
    id: 'mapbox/streets-v11',
    tileSize: 512,
    zoomOffset: -1
}).addTo(mapview);


const dataset = [
    {
	"name": "centrales",
	"location": "https://trosa.io/qgis-tools/data/poste-source.json",
	"layer": L.geoJSON().addTo(mapview),
	"fill_color": 'red'
    }
]

dataset.forEach(d => {
    //localStorage.clear();	// TODO: Implement cache
    d.layer.setStyle({fillColor : d.fill_color});
    if (localStorage.getItem(d.name) == null) {
	fetch(d.location)
	    .then(res => res.json())
	    .then((data) => {
		localStorage.setItem(d.name, data);
		data.features.map(feature => d.layer.addData(feature));
	    })
	    .catch ((err) => {
		console.log(err);
	    });
    } else {
	const data = localStorage.getItem(d.name);
	data.features.map(feature => d.layer.addData(feature));
    }
});
