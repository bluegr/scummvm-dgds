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
#include "common/memstream.h"

#include "dgds/dgds.h"
#include "dgds/bmpimage.h"
#include "dgds/resourceman.h"

namespace Dgds {

#define FILENAME_LENGTH 12

BmpImage::BmpImage(Common::String filename, ResourceManager *resMan) {
	Common::SeekableReadStream *data = resMan->getResource(filename);
	if (data == nullptr)
		error("Unable to load image %s", filename.c_str());

	if (data->readUint32BE() != MKTAG('B', 'M', 'P', ':'))
		error("Invalid header in image %s", filename.c_str());

	uint32 size = data->readUint32LE();
	if (!(size & 0x80000000))
		error("Image %s does not contain subentries", filename.c_str());
	
	size &= 0x7FFFFFFF;
	if (data->size() != size + 4 + 4)
		error("Unexpected length for image %s (expected: %d bytes, got: %d)", filename.c_str(), size + 4 + 4, data->size());

	// INF chunk (image slices)
	if (data->readUint32BE() != MKTAG('I', 'N', 'F', ':'))
		error("Image %s is missing the INF chunk", filename.c_str());

	data->skip(4);	// chunk size, unused
	
	uint16 slices = data->readUint16LE();
	debug("Image %s has %d slices", filename.c_str(), slices);

	uint16 w, h;
	uint16 total = 0;
	for (uint16 i = 0; i < slices; i++) {
		w = data->readUint16LE();
		h = data->readUint16LE();
		total += w * h;
	}
	debug("Total: %d", total);

	// VQT chunk (image data)
	if (data->readUint32BE() != MKTAG('V', 'Q', 'T', ':'))
		error("Image %s is missing the VQT chunk", filename.c_str());

	size = data->readUint32LE();
	debug("Image has %d bytes", size);

	// TODO
	data->skip(size);
	//Common::MemoryReadStream *imgData = decompRLE(data, total);

	// OFF chunk
	if (data->readUint32BE() != MKTAG('O', 'F', 'F', ':'))
		error("Image %s is missing the OFF chunk", filename.c_str());

	size = data->readUint32LE();

	// TODO
	data->skip(size);
}

BmpImage::~BmpImage() {

}

Common::MemoryReadStream* BmpImage::decompRLE(Common::SeekableReadStream *in, int size) {
	byte *data = new byte[size];
	int32 pos = -1;
	while (!in->eos()) {
		byte control = in->readByte();
		if (control & 0x80) {
			byte len = in->readByte();
			for (int32 i = 0; i < len; i++) {
				data[pos++] = control & 0x7F;
				//if (pos >= size)
				//	break;
			}
		} else {
			for (int32 i = 0; i < control; i++) {
				data[pos++] = in->readByte();
				//if (pos >= size)
				//	break;
			}
		}

		//if (pos >= size)
		//	break;
	}

	if (pos != size)
		warning("decompRLE expected %d, wrote %d", size, pos);

	return new Common::MemoryReadStream(data, size, DisposeAfterUse::YES);
}

} // End of namespace Dgds
