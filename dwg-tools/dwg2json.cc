//
// (c) iomonad <iomonad@riseup.net>
// See: https://github.com/iomonad/qgis-tools
//
// @desc Convert DWG file to GeoJSON with approximative
// genese referencement. Will be mainly used to import
// old legacy work into QGIS.
//
// @disclaimer The idea is very ODD and the code
// is totally EXPERIMENTAL -> USE AT YOUR OWN RISK !
//

#include <string>
#include <iostream>
#include <fstream>
#include <experimental/filesystem>

#include "dwg2json.hpp"

using namespace std;

static int prepare_header(ofstream *output) {
	*output << "{ \"type\": \"FeatureCollection\"," << endl;
	*output << "    \"features\": [" << endl;
	return 0;
}

static int end_of_document(ofstream *output) {
	*output << "    ]" << endl;
	*output << "}" << endl;
	return 0;
}

static int process_line(Dwg_Object *obj, ofstream *output) {
	Dwg_Entity_LINE *line = NULL;

	line = obj->tio.entity->tio.LINE;
	*output << "{\"type\": \"Feature\"," << endl << "\"geometry\":{" << endl;
	*output << "\"type\": \"LineString\"," << endl << "\"coordinates\": [";
	*output << "[ " << line->start.x << ", " << line->start.y << "], ["
		<< line->end.x << ", " << line->end.y << "]]}}";
	// TODO: Handle props support (useless in my case, segment just needed)
	return 0;
}

static int process_object_entitie(Dwg_Object *entitie,
				  ofstream *output) {
	if (entitie == NULL) {
		return 1;
	}
	switch (entitie->type) {
	case DWG_TYPE_LINE:
		process_line(entitie, output);
		*output << "," << endl;
		break;
	default:
		cout << "NOT IMPLEMENTED yet, WIP"<< endl;
		break;
	}
	return 0;
}

static int process_geojson_output(Dwg_Data *dwg,
				  ofstream *output) {
	Dwg_Object *it = NULL;

	prepare_header(output);
	for (size_t i = 0; i < dwg->num_objects; i++) {
		it = &dwg->object[i];
		if (process_object_entitie(it, output)) {
			// Get more info
			return 1;
		}
	}
	end_of_document(output);
	return 0;
}

int
main(int argc, char *argv[])
{

	int error;
	Dwg_Data dwg;
	std::ofstream output { "output.json"};

	if (argc != 2) {
		// usage
		return 1;
	}
	if ((error = dwg_read_file(argv[1], &dwg))) {
		std::cout << "File " << argv[1]
			  <<"is corrupted." << std::endl;
	}
	if (process_geojson_output(&dwg, &output)) {
		// Get more info
	}
	dwg_free(&dwg);
	output.close();
	return 0;
}
