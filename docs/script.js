var mapview = L.map('mapid').setView([48.860, 2.333], 14);

L.tileLayer('http://basemaps.cartocdn.com/light_all/{z}/{x}/{y}.png', {
    maxZoom: 18,
    attribution: '',
    id: 'mapbox/streets-v11',
    tileSize: 512,
    zoomOffset: -1
}).addTo(mapview);
