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

namespace Dgds {

static const DgdsGameDescription gameDescriptions[] = {
	/*
	{
		// Rise of the Dragon - English PC v1.211
		{
			"dragon",
			"",
			AD_ENTRY1s("volume.vga", "0d9590fdc883d6d99c06e7935423d180", 7823),
			Common::EN_ANY,
			Common::kPlatformDOS,
			ADGF_NO_FLAGS,
			GUIO1(GUIO_NONE)
		},
		GType_Rise
	},
	*/

	{
		// Rise of the Dragon - English PC v1.211
		{
			"dragon",
			"",
			AD_ENTRY1s("volume.vga", "b0583c199614ed1c161a25398c5c7fba", 7823),
			Common::EN_ANY,
			Common::kPlatformDOS,
			ADGF_NO_FLAGS,
			GUIO1(GUIO_NONE)
		},
		GType_Rise
	},

	/*
	{
		// The Adventures of Willy Beamish - English PC v1.224
		{
			"willy",
			"",
			AD_ENTRY1s("volume.rmf", "ba5cf24ec4b6dc044b03115a0cd5f3ff", 9896),
			Common::EN_ANY,
			Common::kPlatformDOS,
			ADGF_NO_FLAGS,
			GUIO1(GUIO_NONE)
		},
		GType_Willy
	},
	*/

	{
		// The Adventures of Willy Beamish - English PC v1.224
		{
			"willy",
			"",
			AD_ENTRY1s("volume.rmf", "c2be5cd4693dfcdbe45dd0e74dd5306d", 9896),
			Common::EN_ANY,
			Common::kPlatformDOS,
			ADGF_NO_FLAGS,
			GUIO1(GUIO_NONE)
		},
		GType_Willy
	},

	/*
	{
		// Heart of China - English PC v1.216
		{
			"china",
			"",
			AD_ENTRY1s("volume.rmf", "2da720143c1e857490daded15682df87", 9791),
			Common::EN_ANY,
			Common::kPlatformDOS,
			ADGF_NO_FLAGS,
			GUIO1(GUIO_NONE)
		},
		GType_Hoc
	},
	*/

	{
		// Heart of China - English PC v1.216
		{
			"china",
			"",
			AD_ENTRY1s("volume.rmf", "677b91bc6961824f1997c187292f174e", 9791),
			Common::EN_ANY,
			Common::kPlatformDOS,
			ADGF_NO_FLAGS,
			GUIO1(GUIO_NONE)
		},
		GType_Hoc
	},
	
	{ AD_TABLE_END_MARKER, (GameType)0 }
};

/*
namespace Dgds {

static const ADGameDescription gameDescriptions[] = {
	// Rise of the Dragon - English Amiga
	{"dragon", "",
		AD_ENTRY1s("volume.rmf", "44cd1ffdfeb385dcfcd60563e1036167", 8972),
		Common::EN_ANY,
		Common::kPlatformAmiga,
		ADGF_NO_FLAGS,
		GUIO1(GUIO_NONE)
	},
  
	// Rise of the Dragon - English Amiga
	{"dragon", "",
		AD_ENTRY1s("volume.rmf", "5618ac459de017b5cb723757b711fcba", 8972),
		Common::EN_ANY,
		Common::kPlatformAmiga,
		ADGF_NO_FLAGS,
		GUIO1(GUIO_NONE)
	},
  
	// Rise of the Dragon - English Mac
	{"dragon", "",
		AD_ENTRY1s("volume.rmf", "ef8fb69e932946643b608532e0af3ad9", 7079),
		Common::EN_ANY,
		Common::kPlatformMacintosh,
		ADGF_NO_FLAGS,
		GUIO1(GUIO_NONE)
	},

	// The Adventures of Willy Beamish - Amiga
	{"willy", "",
		AD_ENTRY1s("volume.rmf",  "775388e795b17c33ce19d53b4fbd1003", 11906),
		Common::EN_ANY,
		Common::kPlatformAmiga,
		ADGF_NO_FLAGS,
		GUIO1(GUIO_NONE)
	},
  
	// The Adventurs of Willy Beamish - English PC CD version
	{"willy", "",
		{
			{ "resource.001", 0, "ddb2ca8176e00719efa9946450e3019c", 151525997 },
			{ "resource.map", 0, "ee70604d1fcac9c7fa04e64cbb54fa47", 27237 },
			{ "resource.rme", 0, "285f6558e37c6da35109a0ef021784fa", 44247 },
			AD_LISTEND
		},
		Common::EN_ANY,
		Common::kPlatformPC,
		ADGF_CD,
		GUIO1(GUIO_NONE)
	},

	// The Adventures of Willy Beamish - SegaCD
	{"willy", "",
		{
      {"WINV.REQ", 0, "b7397f428c8dd10ee34addf63b3eff98", 556},
      {"WVCR.REQ", 0, "ca76caf87e71eeaa36d3ad70a9fddfe0", 6000},
			AD_LISTEND
		},
		Common::EN_ANY,
		Common::kPlatformSegaCD,
		ADGF_NO_FLAGS,
		GUIO1(GUIO_NONE)
	},

	// Heart of China - Spanish PC
	{"china", "",
		AD_ENTRY1s("volume.rmf", "072cffb026d91b8d25d11c70f4a57fb2", 10032),
		Common::ES_ESP,
		Common::kPlatformPC,
		ADGF_NO_FLAGS,
		GUIO1(GUIO_NONE)
	},
	
	// Heart of China - English Amiga
	{"china", "",
		AD_ENTRY1s("volume.rmf", "b8f917288ce484c4969574da18b288ea", 11061),
		Common::EN_ANY,
		Common::kPlatformAmiga,
		ADGF_NO_FLAGS,
		GUIO1(GUIO_NONE)
	},
  
	// Heart of China - English Mac
	{"china", "",
		AD_ENTRY1s("volume.rmf", "c88125dabb6a547bca82ec27d82a25a6", 9918),
		Common::EN_ANY,
		Common::kPlatformMacintosh,
		ADGF_NO_FLAGS,
		GUIO1(GUIO_NONE)
	},

	AD_TABLE_END_MARKER
};
*/

} // End of namespace Dgds
