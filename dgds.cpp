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

#include "common/config-manager.h"
#include "common/error.h"
#include "common/events.h"
#include "common/system.h"
#include "graphics/palette.h"

#include "engines/engine.h"
#include "engines/util.h"

#include "dgds/dgds.h"
#include "dgds/resourceman.h"
#include "dgds/bmpimage.h"
#include "dgds/scrimage.h"

#include "common/stream.h"	//
#include "graphics/surface.h"
#include "common/memstream.h"

namespace Dgds {

DgdsEngine::DgdsEngine(OSystem *syst, const DgdsGameDescription *gameDesc)
	: Engine(syst),
	_gameDescription(gameDesc),
	_rnd("dgds") {
}

DgdsEngine::~DgdsEngine() {

}

void DgdsEngine::initialize() {

}

Common::MemoryReadStream* decompRLE(Common::SeekableReadStream *in, int size) {
	byte *data = new byte[size];
	int32 pos = -1;
	while (!in->eos()) {
		byte control = in->readByte();
		if (control & 0x80) {
			byte len = in->readByte();
			for (int32 i = 0; i < len; i++) {
				data[pos++] = control & 0x7F;
				if (pos >= size)
					break;
			}
		} else {
			for (int32 i = 0; i < control; i++) {
				data[pos++] = in->readByte();
				if (pos >= size)
					break;
			}
		}

		if (pos >= size)
			break;
	}

	if (pos != size)
		warning("decompRLE expected %d, wrote %d", size, pos);

	Common::MemoryReadStream *stream = new Common::MemoryReadStream(data, size, DisposeAfterUse::YES);
	return stream;
}

Common::Error DgdsEngine::run() {
	// Initialize backend
	initGraphics(320, 200, false);

	initialize();

	ResourceManager *resMan = new ResourceManager();

	//BmpImage *bmpImage = new BmpImage("drecept.bmp", resMan);
	//ScrImage *scrImage = new ScrImage("drecept.scr", resMan);
	ScrImage *scrImage = new ScrImage("dynamix.scr", resMan);

	//Common::SeekableReadStream *pal = resMan->getResource("dragon.pal");
	Common::SeekableReadStream *pal = resMan->getResource("dynamix.pal");
	byte palette[256 * 3];
	pal->skip(16);
	pal->read(palette, 256 * 3);
	g_system->getPaletteManager()->setPalette(palette, 0, 256);

	g_system->copyRectToScreen(scrImage->getData(), 320, 0, 0, 320, 200);

	Common::EventManager *eventMan = g_system->getEventManager();
	Common::Event ev;

	// Run a dummy loop
	while (!shouldQuit()) {
		//_events->processEvents();
		eventMan->pollEvent(ev);

		//_console->onFrame();

		g_system->updateScreen();
		g_system->delayMillis(10);
	}

	return Common::kNoError;
}

} // End of namespace Dgds
