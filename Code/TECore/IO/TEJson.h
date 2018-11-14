/*#ifndef TEJSON_H
#define TEJSON_H

#include "TEFileIO.h"

#include <json/value.h>
#include <json/reader.h>

namespace TE
{
	namespace IO
	{
		class JsonSerializer
		{
		public:
			virtual void JSONDeserialize(const Json::Value& jsonValue) = 0;
			virtual void JSONSerialize(Json::Value& jsonValue) = 0;
		};

		void JsonValueFromData(const U8* dataBegin, const U8* dataEnd, Json::Value & jsonValue);
	}
}

#endif*/