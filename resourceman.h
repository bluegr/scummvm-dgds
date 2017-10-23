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

#ifndef DGDS_RESOURCEMAN_H
#define DGDS_RESOURCEMAN_H


#include "common/scummsys.h"
#include "common/file.h"
#include "common/util.h"
#include "common/str.h"
#include "common/hashmap.h"
#include "common/hash-str.h"
#include "common/random.h"
#include "common/stream.h"
#include "common/list.h"

namespace Dgds {

struct Resource {
	byte volume;
	uint32 pos;
	uint32 size;
	uint32 checksum;
};

typedef Common::HashMap<Common::String, Resource> ResourceList;

#define MAX_VOLUMES 10

class ResourceManager {
public:
	ResourceManager();
	virtual ~ResourceManager();

	Common::SeekableReadStream *getResource(Common::String name);
private:
	Common::File _volumes[MAX_VOLUMES];
	ResourceList _resources;
};

} // End of namespace Dgds

#endif
