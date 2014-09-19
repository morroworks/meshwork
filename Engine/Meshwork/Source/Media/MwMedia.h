#pragma once

#include "..\MwGlobals.h"

#include "..\Tools\Streams\MwBaseStream.h"

// Represents a media, as a medium for translating content to Meshwork. The main functions of the class is to decode and encode different content types such as images, sounds and 3d scenes. Usually, a media handles one or more content types of the same group, for example images or sounds or 3d scenes
// Typically, the media decodes content into raw data and the engine then loads that data. If the engine needs to export content to a certain media type, a media will need to be able to encode raw data to the format of that media type.
// For example, if the engine needs to import a texture from a png file, it will use a media to decode the png into raw data in order to load it. And If the engine needs to export an image, it will again use media to encode raw data into the desired media format, for example png again.
class MWDLLCLASS MwMedia
{
public:
	MwMedia(void);
	virtual ~MwMedia(void);

	// Loads a media's content, decoding it from its native format into raw data
	// source - stream holding a media's content in its native format. The stream must be positioned at the start of the content. For example, if it represents a file of the media's native type, it's position should normally be zero
	// returns -  true if succeeds, false otherwise
	virtual bool Load(MwBaseStream &source) = 0;
	// Saves the media, encoding it into the given format
	// destination - stream where the encoded data will be written, starting at the stream's current position
	// encoding - the format, in which the media must be encoded into. For example, to encode an image in png format, it should be "png", or to encode a sound in wav format, it should be "wav" and so on
	// returns - true if succeeds, false otherwise
	virtual bool Save(MwBaseStream &destination, const char *format) = 0;
};

