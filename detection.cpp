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

#include "common/savefile.h"
#include "common/system.h"
#include "base/plugins.h"

#include "engines/advancedDetector.h"

#include "dgds/dgds.h"

namespace Dgds {

	struct DgdsGameDescription {
		ADGameDescription desc;

		GameType gameID;
	};

	GameType DgdsEngine::getGameID() const {
		return _gameDescription->gameID;
	}

	Common::Platform DgdsEngine::getPlatform() const {
		return _gameDescription->desc.platform;
	}

	Common::Language DgdsEngine::getLanguage() const {
		return _gameDescription->desc.language;
	}

} // End of namespace Sherlock

static const PlainGameDescriptor dgdsGames[] = {
	{"china",  "Heart of China"},
	{"dragon", "Rise of the Dragon"},
	{"willy",  "The Adventures of Willy Beamish"},
	{0, 0}
};

/*static const ADGameDescription DgdsGameGeneric[] = {
	{"dgds", 0,
		AD_ENTRY1("volume.rmf", NULL),
		Common::UNK_LANG,
		Common::kPlatformUnknown,
		0,
		GUIO1(GUIO_NONE)
	},
	AD_TABLE_END_MARKER
};

static const ADFileBasedFallback fileBasedFallback[] = {
	{&DgdsGameGeneric[0], {"volume.rmf", NULL} },
	{&DgdsGameGeneric[0], {"volume.vga", NULL} },
	{&DgdsGameGeneric[0], {"resource.map", NULL} },
	{0, {NULL}}
};*/

//} // End of namespace Dgds

#include "dgds/detection_tables.h"

class DgdsMetaEngine : public AdvancedMetaEngine {
public:
	DgdsMetaEngine() : AdvancedMetaEngine(Dgds::gameDescriptions, sizeof(Dgds::DgdsGameDescription), dgdsGames) {}

	virtual const char *getName() const {
		return "Dynamix Game Development System";
	}
	
	virtual const char *getOriginalCopyright() const {
		return "Dynamix Game Development System (c) Dynamix";
	}

	/**
	 * Creates an instance of the game engine
	 */
	virtual bool createInstance(OSystem *syst, Engine **engine, const ADGameDescription *desc) const;
	
	/**
	 * Returns a list of features the game's MetaEngine support
	 */
	virtual bool hasFeature(MetaEngineFeature f) const;
	
	/**
	 * Return a list of savegames
	 */
	virtual SaveStateList listSaves(const char *target) const;
	
	/**
	 * Returns the maximum number of allowed save slots
	 */
	virtual int getMaximumSaveSlot() const;
	
	/**
	 * Deletes a savegame in the specified slot
	 */
	virtual void removeSaveState(const char *target, int slot) const;
	
	/**
	 * Given a specified savegame slot, returns extended information for the save
	 */
	SaveStateDescriptor querySaveMetaInfos(const char *target, int slot) const;
	
	/*virtual const ADGameDescription *fallbackDetect(const FileMap &allFiles, const Common::FSList &fslist) const {
		return detectGameFilebased(allFiles, Dgds::fileBasedFallback);
	}*/
};

bool DgdsMetaEngine::hasFeature(MetaEngineFeature f) const {
	return
		(f == kSupportsListSaves) ||
		(f == kSupportsLoadingDuringStartup) ||
		(f == kSupportsDeleteSave) ||
		(f == kSavesSupportMetaInfo) ||
		(f == kSavesSupportThumbnail) ||
		(f == kSimpleSavesNames);
}

bool Dgds::DgdsEngine::hasFeature(EngineFeature f) const {
	return
		(f == kSupportsRTL) ||
		(f == kSupportsLoadingDuringRuntime) ||
		(f == kSupportsSavingDuringRuntime);
}

bool DgdsMetaEngine::createInstance(OSystem *syst, Engine **engine, const ADGameDescription *desc) const {
	const Dgds::DgdsGameDescription *gd = (const Dgds::DgdsGameDescription *)desc;
	if (gd) {
		*engine = new Dgds::DgdsEngine(syst, gd);
	}
	return gd != 0;
}

SaveStateList DgdsMetaEngine::listSaves(const char *target) const {
	Common::SaveFileManager *saveFileMan = g_system->getSavefileManager();
	//Lab::SaveGameHeader header;
	Common::String pattern = target;
	pattern += ".###";

	Common::StringArray filenames;
	filenames = saveFileMan->listSavefiles(pattern.c_str());

	SaveStateList saveList;

	for (Common::StringArray::const_iterator file = filenames.begin(); file != filenames.end(); ++file) {
		// Obtain the last 3 digits of the filename, since they correspond to the save slot
		int slotNum = atoi(file->c_str() + file->size() - 3);

		if ((slotNum >= 0) && (slotNum <= 999)) {
			Common::InSaveFile *in = saveFileMan->openForLoading(file->c_str());
			if (in) {
				//if (Lab::readSaveGameHeader(in, header))
				//	saveList.push_back(SaveStateDescriptor(slotNum, header._descr.getDescription()));
				delete in;
			}
		}
	}

	// Sort saves based on slot number.
	Common::sort(saveList.begin(), saveList.end(), SaveStateDescriptorSlotComparator());
	return saveList;
}

int DgdsMetaEngine::getMaximumSaveSlot() const {
	return 999;
}

void DgdsMetaEngine::removeSaveState(const char *target, int slot) const {
	Common::SaveFileManager *saveFileMan = g_system->getSavefileManager();
	saveFileMan->removeSavefile(Common::String::format("%s.%03u", target, slot));
}

SaveStateDescriptor DgdsMetaEngine::querySaveMetaInfos(const char *target, int slot) const {
	Common::String filename = Common::String::format("%s.%03u", target, slot);
	Common::InSaveFile *in = g_system->getSavefileManager()->openForLoading(filename.c_str());

	if (in) {
		/*Lab::SaveGameHeader header;

		bool successfulRead = Lab::readSaveGameHeader(in, header);
		delete in;

		if (successfulRead) {
			SaveStateDescriptor desc(slot, header._descr.getDescription());
			// Do not allow save slot 0 (used for auto-saving) to be deleted or
			// overwritten.
			//desc.setDeletableFlag(slot != 0);
			//desc.setWriteProtectedFlag(slot == 0);

			return header._descr;
		}*/
	}

	return SaveStateDescriptor();
}


#if PLUGIN_ENABLED_DYNAMIC(DGDS)
REGISTER_PLUGIN_DYNAMIC(DGDS, PLUGIN_TYPE_ENGINE, DgdsMetaEngine);
#else
REGISTER_PLUGIN_STATIC(DGDS, PLUGIN_TYPE_ENGINE, DgdsMetaEngine);
#endif
