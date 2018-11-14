#ifndef TEAPIRESOURCE_H
#define TEAPIRESOURCE_H

namespace TE
{
	//Forward declaration
	namespace Render { struct APIContext; }
	//End forward declaration

	namespace Render
	{
		class APIResource
		{
		public:
			APIResource();
			virtual ~APIResource();
		};
	}
}

#endif