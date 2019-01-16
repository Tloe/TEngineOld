#ifndef TEVARIANT_H
#define TEVARIANT_H

#include "TEDataTypes.h"

#include <vector>
#include <map>

namespace TE
{
	namespace Core
	{
		enum class VariantType
		{
			NotSet,
			String,
			I32,
			U32,
            BOOL,
			F32
		};

		class Variant
		{
		public:
			Variant();
			~Variant();
            Variant(const Variant & other);
            Variant(Variant && other);
            Variant & operator=(const Variant & other);
            Variant & operator=(Variant && other);

            explicit Variant(const std::string & str);
            explicit Variant(const char * str);
			explicit Variant(I32 i32);
			explicit Variant(U32 u32);
			explicit Variant(bool boolean);
			explicit Variant(F32 f32);

			VariantType GetType() const;

			void SetString(const std::string& str);
            void SetString(const char *str);
			void SetI32(I32 i32);
			void SetU32(U32 u32);
			void SetBool(bool boolean);
			void SetF32(F32 f32);

            const char* GetCString() const;
			std::string GetString() const;
			I32 GetI32() const;
			U32 GetU32() const;
			bool GetBool() const;
			F32 GetF32() const;

		private:
			union Value
			{
				I32 i32;
				U32 u32;
				bool boolean;
				F32 f32;
                char* cString;
			};

			void ClearString();

			VariantType m_variantType;
			Value m_value;
		};

        typedef std::vector<Variant> VariantVec;
	}
}

#endif
