#include "obstacle.h"
using namespace std;

namespace config {
	using path = filesystem::path;
	using value_type = filesystem::path::value_type;
	using string_type = filesystem::path::string_type;

	const path& input_file();
	const path& output_file();

	template<class Container>
	void output(const Container&);

	int read_map(
		const path& filename,
		sommet* start,
		sommet* finish,
		vector<obstacle>* obstacles
	);
}