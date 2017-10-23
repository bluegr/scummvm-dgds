/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#include "common/debug.h"
#include "common/stream.h"
#include "common/substream.h"
#include "common/textconsole.h"

#include "dgds/dgds.h"
#include "dgds/resourceman.h"

namespace Dgds {

#define FILENAME_LENGTH 12

ResourceManager::ResourceManager() {
	const char* indexFiles[] = {
		"volume.vga",	// early Dragon versions
		"volume.rmf",	// Beamish / HoC
		"volume.map"	// Beamish CD
	};

	Common::File indexFile;
	for (int i = 0; i < ARRAYSIZE(indexFiles); i++) {
		if (Common::File::exists(indexFiles[i])) {
			indexFile.open(indexFiles[i]);
			break;
		}
	}

	indexFile.skip(4);	// header, TODO
	int volumes = indexFile.readUint16LE();

	for (int i = 0; i < volumes; i++) {
		Common::String volumeName;
		for (int j = 0; j < FILENAME_LENGTH; j++)
			volumeName += indexFile.readByte();
		volumeName.toLowercase();

		_volumes[i].open(volumeName);

		indexFile.skip(1);	// unknown
		int entries = indexFile.readUint16LE();
		debug("File %s has %d entries", volumeName.c_str(), entries);

		for (int j = 0; j < entries; j++) {
			Resource res;
			res.volume = i;
			res.checksum = indexFile.readUint32LE();
			res.pos = indexFile.readUint32LE();

			_volumes[i].seek(res.pos, SEEK_SET);
			res.pos += FILENAME_LENGTH + 1 + 4;

			Common::String fileName;
			for (int k = 0; k < FILENAME_LENGTH; k++)
				fileName += _volumes[i].readByte();
			fileName.toLowercase();

			_volumes[i].skip(1);	// unknown
			res.size = _volumes[i].readUint32LE();
			_resources[fileName] = res;

			if (fileName == "" || res.size == 0)
				continue;

			debug("  - %s at %d, size: %d", fileName.c_str(), res.pos, res.size);

			/*Common::DumpFile out;
			Common::String outName = "dgds/";
			out.open(outName + fileName);
			byte *data = new byte[res.size];
			_volumes[i].read(data, res.size);
			out.write(data, res.size);
			out.flush();
			out.close();
			delete[] data;*/
		}
	}

	indexFile.close();
}

ResourceManager::~ResourceManager() {
	for (int i = 0; i < MAX_VOLUMES; i++)
		_volumes[i].close();
}

Common::SeekableReadStream *ResourceManager::getResource(Common::String name) {
	name.toLowercase();

	if (!_resources.contains(name))
		return nullptr;

	Resource res = _resources[name];
	return new Common::SeekableSubReadStream(&_volumes[res.volume], res.pos, res.pos + res.size);
}

} // End of namespace Dgds
