#ifndef TESMARTPOintERS_H
#define TESMARTPOintERS_H

#include <unordered_map>
#include "TENew.h"
#include <iostream>

namespace TE
{
	namespace Memory
	{
		class ReferenceCountedPointer
		{
		protected:
			typedef std::unordered_map<void*, I32> ReferenceMap;
			typedef std::unordered_map<void*, I32>::iterator ReferenceMapIter;

			static ReferenceMap s_referenceMap;
		};

		template <typename T>
		class Pointer0 : public ReferenceCountedPointer
		{
		public:
			Pointer0 (T* memory = 0);
			Pointer0 (const Pointer0& ptr);
			template <typename U>
			Pointer0 (const Pointer0<U>& ptr);
			~Pointer0 ();

			inline operator T* () const;
			inline T& operator* () const;
			inline T* operator-> () const;

			Pointer0& operator= (T* memory);
			Pointer0& operator= (const Pointer0& ptr);
			/*template <typename U>
			Pointer0& operator= (const Pointer0<U>& ptr);*/

			inline bool operator== (T* memory) const;
			inline bool operator!= (T* memory) const;
			inline bool operator== (const Pointer0& ptr) const;
			inline bool operator!= (const Pointer0& ptr) const;

			inline I32 GetReferenceCount();
		private:
			T* m_memory;

			template<typename>
			friend class Pointer0;
		};

		template <typename T>
		class Pointer1 : public ReferenceCountedPointer
		{
		public:
			Pointer1 (T* memory = 0);
			template <typename U>
			Pointer1 (const Pointer1<U>& ptr);
			~Pointer1 ();

			inline operator T* () const;
			inline T& operator* () const;
			inline T* operator-> () const;

			Pointer1& operator= (T* memory);
			Pointer1& operator= (const Pointer1& ptr);

			inline bool operator== (T* memory) const;
			inline bool operator!= (T* memory) const;
			inline bool operator== (const Pointer1& ptr) const;
			inline bool operator!= (const Pointer1& ptr) const;

			inline I32 GetReferenceCount();
		private:
			T* m_memory;

			template<typename>
			friend class Pointer1;
		};

		template <typename T>
		class Pointer2 : public PointerBase
		{
		public:
			Pointer2 (T** memory = 0);
			template <typename U>
			Pointer2 (const Pointer2<U>& ptr);
			~Pointer2 ();

			inline operator T** () const;
			inline T*& operator* () const;

			Pointer2& operator= (T** memory);
			Pointer2& operator= (const Pointer2& ptr);

			inline bool operator== (T** memory) const;
			inline bool operator!= (T** memory) const;
			inline bool operator== (const Pointer2& ptr) const;
			inline bool operator!= (const Pointer2& ptr) const;

			inline I32 GetReferenceCount();
		private:
			T** m_memory;

			template<typename>
			friend class Pointer2;
		};

		template <typename T>
		class Pointer3 : public PointerBase
		{
		public:
			Pointer3 (T*** memory = 0);
			template <typename U>
			Pointer3 (const Pointer3<U>& ptr);
			~Pointer3 ();

			inline operator T*** () const;
			inline T**& operator* () const;

			Pointer3& operator= (T*** memory);
			Pointer3& operator= (const Pointer3& ptr);

			inline bool operator== (T*** memory) const;
			inline bool operator!= (T*** memory) const;
			inline bool operator== (const Pointer3& ptr) const;
			inline bool operator!= (const Pointer3& ptr) const;

			inline I32 GetReferenceCount();
		private:
			T*** m_memory;

			template<typename>
			friend class Pointer3;
		};

		template <typename T>
		class Pointer4 : public PointerBase
		{
		public:
			Pointer4 (T**** memory = 0);
			template <typename U>
			Pointer4 (const Pointer4<U>& ptr);
			~Pointer4 ();

			inline operator T**** () const;
			inline T***& operator* () const;

			Pointer4& operator= (T**** memory);
			Pointer4& operator= (const Pointer4& ptr);

			inline bool operator== (T**** memory) const;
			inline bool operator!= (T**** memory) const;
			inline bool operator== (const Pointer4& ptr) const;
			inline bool operator!= (const Pointer4& ptr) const;

			inline I32 GetReferenceCount();
		private:
			T**** m_memory;

			template<typename>
			friend class Pointer4;
		};

		template <typename T>
		TE::Memory::Pointer0<T>::Pointer0 (T* memory)
		{
			m_memory = memory;
			if (m_memory)
			{
				ReferenceMapIter iter = s_referenceMap.find(m_memory);
				if (iter != s_referenceMap.end())
				{
					++iter->second;
				}
				else
				{
					s_referenceMap[m_memory] = 1;
				}
			}
		}

		template <typename T>
		TE::Memory::Pointer0<T>::Pointer0 (const Pointer0& ptr)
		{
			m_memory = ptr.m_memory;
			if (m_memory)
			{
				ReferenceMapIter iter = s_referenceMap.find(m_memory);
				if (iter != s_referenceMap.end())
				{
					++iter->second;
				}
				else
				{
					assert(false && "ptr.m_memory must be in the map\n");
				}
			}
		}

		template <typename T>
		template <typename U>
		TE::Memory::Pointer0<T>::Pointer0 (const Pointer0<U>& ptr)
		{
			m_memory = ptr.m_memory;
			if (m_memory)
			{
				ReferenceMapIter iter = s_referenceMap.find(m_memory);
				if (iter != s_referenceMap.end())
				{
					++iter->second;
				}
				else
				{
					assert(false && "ptr.m_memory must be in the map\n");
				}
			}
		}

		template <typename T>
		TE::Memory::Pointer0<T>::~Pointer0 ()
		{
			static I32 calls = 0;
			//std::cout << calls++ << std::endl;
			if (m_memory)
			{
				ReferenceMapIter iter = s_referenceMap.find(m_memory);
				if (iter != s_referenceMap.end())
				{
					if (--iter->second == 0)
					{
						s_referenceMap.erase(m_memory);
						delete0(m_memory);
					}
				}
				else
				{
					assert(false && "m_memory must be in the map\n");
				}
			}
		}

		template <typename T>
		inline TE::Memory::Pointer0<T>::operator T* () const
		{
			return m_memory;
		}

		template <typename T>
		inline T& TE::Memory::Pointer0<T>::operator* () const
		{
			return *m_memory;
		}

		template <typename T>
		inline T* TE::Memory::Pointer0<T>::operator-> () const
		{
			return m_memory;
		}

		template <typename T>
		TE::Memory::Pointer0<T>& TE::Memory::Pointer0<T>::operator= (T* memory)
		{
			if (m_memory != memory)
			{
				ReferenceMapIter iter;

				if (memory)
				{
					iter = s_referenceMap.find(memory);
					if (iter != s_referenceMap.end())
					{
						++iter->second;
					}
					else
					{
						s_referenceMap[memory] = 1;
					}
				}

				if (m_memory)
				{
					iter = s_referenceMap.find(m_memory);
					if (iter != s_referenceMap.end())
					{
						if (--iter->second == 0)
						{
							s_referenceMap.erase(m_memory);
							delete0(m_memory);
						}
					}
					else
					{
						assert(false && "m_memory must be in the map\n");
					}
				}

				m_memory = memory;
			}

			return *this;
		}

		template <typename T>
		TE::Memory::Pointer0<T>& TE::Memory::Pointer0<T>::operator= (const Pointer0& ptr)
		{
			if (m_memory != ptr.m_memory)
			{
				ReferenceMapIter iter;

				if (ptr.m_memory)
				{
					iter = s_referenceMap.find(ptr.m_memory);
					if (iter != s_referenceMap.end())
					{
						++iter->second;
					}
					else
					{
						assert(false && "ptr.m_memory must be in the map\n");
					}
				}

				if (m_memory)
				{
					iter = s_referenceMap.find(m_memory);
					if (iter != s_referenceMap.end())
					{
						if (--iter->second == 0)
						{
							s_referenceMap.erase(m_memory);
							delete0(m_memory);
						}
					}
					else
					{
						assert(false && "m_memory must be in the map\n");
					}
				}

				m_memory = ptr.m_memory;
			}

			return *this;
		}

		/*template <typename T>
		template <typename U>
		TE::Memory::Pointer0<T>& TE::Memory::Pointer0<T>::operator= (const Pointer0<U>& ptr)
		{
			if (m_memory != ptr.m_memory)
			{
				ReferenceMapIter iter;

				if (ptr.m_memory)
				{
					iter = s_referenceMap.find(ptr.m_memory);
					if (iter != s_referenceMap.end())
					{
						++iter->second;
					}
					else
					{
						assert(false && "ptr.m_memory must be in the map\n");
					}
				}

				if (m_memory)
				{
					iter = s_referenceMap.find(m_memory);
					if (iter != s_referenceMap.end())
					{
						if (--iter->second == 0)
						{
							s_referenceMap.erase(m_memory);
							delete0(m_memory);
						}
					}
					else
					{
						assert(false && "m_memory must be in the map\n");
					}
				}

				m_memory = ptr.m_memory;
			}

			return *this;
		}*/

		template <typename T>
		inline bool TE::Memory::Pointer0<T>::operator== (T* memory) const
		{
			return m_memory == memory;
		}

		template <typename T>
		inline bool TE::Memory::Pointer0<T>::operator!= (T* memory) const
		{
			return m_memory != memory;
		}

		template <typename T>
		inline bool TE::Memory::Pointer0<T>::operator== (const Pointer0& ptr) const
		{
			return m_memory == ptr.m_memory;
		}

		template <typename T>
		inline bool TE::Memory::Pointer0<T>::operator!= (const Pointer0& ptr) const
		{
			return m_memory != ptr.m_memory;
		}

		template <typename T>
		I32 TE::Memory::Pointer0<T>::GetReferenceCount()
		{
			ReferenceMapIter iter = s_referenceMap.find(m_memory);
			if (iter != s_referenceMap.end())
			{
				return iter->second;
			}
			return 0;
		}

		template <typename T>
		TE::Memory::Pointer1<T>::Pointer1 (T* memory)
		{
			m_memory = memory;
			if (m_memory)
			{
				ReferenceMapIter iter = s_referenceMap.find(m_memory);
				if (iter != s_referenceMap.end())
				{
					++iter->second;
				}
				else
				{
					s_referenceMap[m_memory] = 1;
				}
			}
		}

		template <typename T>
		template <typename U>
		TE::Memory::Pointer1<T>::Pointer1 (const Pointer1<U>& ptr)
		{
			m_memory = ptr.m_memory;
			if (m_memory)
			{
				ReferenceMapIter iter = s_referenceMap.find(m_memory);
				if (iter != s_referenceMap.end())
				{
					++iter->second;
				}
				else
				{
					assert(false && "ptr.m_memory must be in the map\n");
				}
			}
		}

		template <typename T>
		TE::Memory::Pointer1<T>::~Pointer1 ()
		{
			if (m_memory)
			{
				ReferenceMapIter iter = s_referenceMap.find(m_memory);
				if (iter != s_referenceMap.end())
				{
					if (--iter->second == 0)
					{
						s_referenceMap.erase(m_memory);
						delete1(m_memory);
					}
				}
				else
				{
					assert(false && "m_memory must be in the map\n");
				}
			}
		}

		template <typename T>
		inline TE::Memory::Pointer1<T>::operator T* () const
		{
			return m_memory;
		}

		template <typename T>
		inline T& TE::Memory::Pointer1<T>::operator* () const
		{
			return *m_memory;
		}

		template <typename T>
		inline T* TE::Memory::Pointer1<T>::operator-> () const
		{
			return m_memory;
		}

		template <typename T>
		TE::Memory::Pointer1<T>& TE::Memory::Pointer1<T>::operator= (T* memory)
		{
			if (m_memory != memory)
			{
				ReferenceMapIter iter;

				if (memory)
				{
					iter = s_referenceMap.find(memory);
					if (iter != s_referenceMap.end())
					{
						++iter->second;
					}
					else
					{
						s_referenceMap[memory] = 1;
					}
				}

				if (m_memory)
				{
					iter = s_referenceMap.find(m_memory);
					if (iter != s_referenceMap.end())
					{
						if (--iter->second == 0)
						{
							s_referenceMap.erase(m_memory);
							delete1(m_memory);
						}
					}
					else
					{
						assert(false && "m_memory must be in the map\n");
					}
				}

				m_memory = memory;
			}

			return *this;
		}

		template <typename T>
		TE::Memory::Pointer1<T>& TE::Memory::Pointer1<T>::operator= (const Pointer1& ptr)
		{
			if (m_memory != ptr.m_memory)
			{
				ReferenceMapIter iter;

				if (ptr.m_memory)
				{
					iter = s_referenceMap.find(ptr.m_memory);
					if (iter != s_referenceMap.end())
					{
						++iter->second;
					}
					else
					{
						assert(false && "ptr.m_memory must be in the map\n");
					}
				}

				if (m_memory)
				{
					iter = s_referenceMap.find(m_memory);
					if (iter != s_referenceMap.end())
					{
						if (--iter->second == 0)
						{
							s_referenceMap.erase(m_memory);
							delete1(m_memory);
						}
					}
					else
					{
						assert(false && "m_memory must be in the map\n");
					}
				}

				m_memory = ptr.m_memory;
			}

			return *this;
		}

		template <typename T>
		inline bool TE::Memory::Pointer1<T>::operator== (T* memory) const
		{
			return m_memory == memory;
		}

		template <typename T>
		inline bool TE::Memory::Pointer1<T>::operator!= (T* memory) const
		{
			return m_memory != memory;
		}

		template <typename T>
		inline bool TE::Memory::Pointer1<T>::operator== (const Pointer1& ptr) const
		{
			return m_memory == ptr.m_memory;
		}

		template <typename T>
		inline bool TE::Memory::Pointer1<T>::operator!= (const Pointer1& ptr) const
		{
			return m_memory != ptr.m_memory;
		}

		template <typename T>
		I32 TE::Memory::Pointer1<T>::GetReferenceCount()
		{
			ReferenceMapIter iter = s_referenceMap.find(m_memory);
			if (iter != s_referenceMap.end())
			{
				return iter->second;
			}
			return 0;
		}

		template <typename T>
		TE::Memory::Pointer2<T>::Pointer2 (T** memory)
		{
			m_memory = memory;
			if (m_memory)
			{
				ReferenceMapIter iter = s_referenceMap.find(m_memory);
				if (iter != s_referenceMap.end())
				{
					++iter->second;
				}
				else
				{
					s_referenceMap[m_memory] = 1;
				}
			}
		}

		template <typename T>
		template <typename U>
		TE::Memory::Pointer2<T>::Pointer2 (const Pointer2<U>& ptr)
		{
			m_memory = ptr.m_memory;
			if (m_memory)
			{
				ReferenceMapIter iter = s_referenceMap.find(m_memory);
				if (iter != s_referenceMap.end())
				{
					++iter->second;
				}
				else
				{
					assert(false && "ptr.m_memory must be in the map\n");
				}
			}
		}

		template <typename T>
		TE::Memory::Pointer2<T>::~Pointer2 ()
		{
			if (m_memory)
			{
				ReferenceMapIter iter = s_referenceMap.find(m_memory);
				if (iter != s_referenceMap.end())
				{
					if (--iter->second == 0)
					{
						s_referenceMap.erase(m_memory);
						delete2(m_memory);
					}
				}
				else
				{
					assert(false && "m_memory must be in the map\n");
				}
			}
		}

		template <typename T>
		inline TE::Memory::Pointer2<T>::operator T** () const
		{
			return m_memory;
		}

		template <typename T>
		inline T*& TE::Memory::Pointer2<T>::operator* () const
		{
			return *m_memory;
		}

		template <typename T>
		TE::Memory::Pointer2<T>& TE::Memory::Pointer2<T>::operator= (T** memory)
		{
			if (m_memory != memory)
			{
				ReferenceMapIter iter;

				if (memory)
				{
					iter = s_referenceMap.find(memory);
					if (iter != s_referenceMap.end())
					{
						++iter->second;
					}
					else
					{
						s_referenceMap[memory] = 1;
					}
				}

				if (m_memory)
				{
					iter = s_referenceMap.find(m_memory);
					if (iter != s_referenceMap.end())
					{
						if (--iter->second == 0)
						{
							s_referenceMap.erase(m_memory);
							delete2(m_memory);
						}
					}
					else
					{
						assert(false && "m_memory must be in the map\n");
					}
				}

				m_memory = memory;
			}

			return *this;
		}

		template <typename T>
		TE::Memory::Pointer2<T>& TE::Memory::Pointer2<T>::operator= (const Pointer2& ptr)
		{
			if (m_memory != ptr.m_memory)
			{
				ReferenceMapIter iter;

				if (ptr.m_memory)
				{
					iter = s_referenceMap.find(ptr.m_memory);
					if (iter != s_referenceMap.end())
					{
						++iter->second;
					}
					else
					{
						assert(false && "ptr.m_memory must be in the map\n");
					}
				}

				if (m_memory)
				{
					iter = s_referenceMap.find(m_memory);
					if (iter != s_referenceMap.end())
					{
						if (--iter->second == 0)
						{
							s_referenceMap.erase(m_memory);
							delete2(m_memory);
						}
					}
					else
					{
						assert(false && "m_memory must be in the map\n");
					}
				}

				m_memory = ptr.m_memory;
			}

			return *this;
		}

		template <typename T>
		inline bool TE::Memory::Pointer2<T>::operator== (T** memory) const
		{
			return m_memory == memory;
		}

		template <typename T>
		inline bool TE::Memory::Pointer2<T>::operator!= (T** memory) const
		{
			return m_memory != memory;
		}

		template <typename T>
		inline bool TE::Memory::Pointer2<T>::operator== (const Pointer2& ptr) const
		{
			return m_memory == ptr.m_memory;
		}

		template <typename T>
		inline bool TE::Memory::Pointer2<T>::operator!= (const Pointer2& ptr) const
		{
			return m_memory != ptr.m_memory;
		}

		template <typename T>
		I32 TE::Memory::Pointer2<T>::GetReferenceCount()
		{
			ReferenceMapIter iter = s_referenceMap.find(m_memory);
			if (iter != s_referenceMap.end())
			{
				return iter->second;
			}
			return 0;
		}

		template <typename T>
		TE::Memory::Pointer3<T>::Pointer3 (T*** memory)
		{
			m_memory = memory;
			if (m_memory)
			{
				ReferenceMapIter iter = s_referenceMap.find(m_memory);
				if (iter != s_referenceMap.end())
				{
					++iter->second;
				}
				else
				{
					s_referenceMap[m_memory] = 1;
				}
			}
		}

		template <typename T>
		template <typename U>
		TE::Memory::Pointer3<T>::Pointer3 (const Pointer3<U>& ptr)
		{
			m_memory = ptr.m_memory;
			if (m_memory)
			{
				ReferenceMapIter iter = s_referenceMap.find(m_memory);
				if (iter != s_referenceMap.end())
				{
					++iter->second;
				}
				else
				{
					assert(false && "ptr.m_memory must be in the map\n");
				}
			}
		}

		template <typename T>
		TE::Memory::Pointer3<T>::~Pointer3 ()
		{
			if (m_memory)
			{
				ReferenceMapIter iter = s_referenceMap.find(m_memory);
				if (iter != s_referenceMap.end())
				{
					if (--iter->second == 0)
					{
						s_referenceMap.erase(m_memory);
						delete3(m_memory);
					}
				}
				else
				{
					assert(false && "m_memory must be in the map\n");
				}
			}
		}

		template <typename T>
		inline TE::Memory::Pointer3<T>::operator T*** () const
		{
			return m_memory;
		}

		template <typename T>
		inline T**& TE::Memory::Pointer3<T>::operator* () const
		{
			return *m_memory;
		}

		template <typename T>
		TE::Memory::Pointer3<T>& TE::Memory::Pointer3<T>::operator= (T*** memory)
		{
			if (m_memory != memory)
			{
				ReferenceMapIter iter;

				if (memory)
				{
					iter = s_referenceMap.find(memory);
					if (iter != s_referenceMap.end())
					{
						++iter->second;
					}
					else
					{
						s_referenceMap[memory] = 1;
					}
				}

				if (m_memory)
				{
					iter = s_referenceMap.find(m_memory);
					if (iter != s_referenceMap.end())
					{
						if (--iter->second == 0)
						{
							s_referenceMap.erase(m_memory);
							delete3(m_memory);
						}
					}
					else
					{
						assert(false && "m_memory must be in the map\n");
					}
				}

				m_memory = memory;
			}

			return *this;
		}

		template <typename T>
		TE::Memory::Pointer3<T>& TE::Memory::Pointer3<T>::operator= (const Pointer3& ptr)
		{
			if (m_memory != ptr.m_memory)
			{
				ReferenceMapIter iter;

				if (ptr.m_memory)
				{
					iter = s_referenceMap.find(ptr.m_memory);
					if (iter != s_referenceMap.end())
					{
						++iter->second;
					}
					else
					{
						assert(false && "ptr.m_memory must be in the map\n");
					}
				}

				if (m_memory)
				{
					iter = s_referenceMap.find(m_memory);
					if (iter != s_referenceMap.end())
					{
						if (--iter->second == 0)
						{
							s_referenceMap.erase(m_memory);
							delete3(m_memory);
						}
					}
					else
					{
						assert(false && "m_memory must be in the map\n");
					}
				}

				m_memory = ptr.m_memory;
			}

			return *this;
		}

		template <typename T>
		inline bool TE::Memory::Pointer3<T>::operator== (T*** memory) const
		{
			return m_memory == memory;
		}

		template <typename T>
		inline bool TE::Memory::Pointer3<T>::operator!= (T*** memory) const
		{
			return m_memory != memory;
		}

		template <typename T>
		inline bool TE::Memory::Pointer3<T>::operator== (const Pointer3& ptr) const
		{
			return m_memory == ptr.m_memory;
		}

		template <typename T>
		inline bool TE::Memory::Pointer3<T>::operator!= (const Pointer3& ptr) const
		{
			return m_memory != ptr.m_memory;
		}

		template <typename T>
		I32 TE::Memory::Pointer3<T>::GetReferenceCount()
		{
			ReferenceMapIter iter = s_referenceMap.find(m_memory);
			if (iter != s_referenceMap.end())
			{
				return iter->second;
			}
			return 0;
		}

		template <typename T>
		TE::Memory::Pointer4<T>::Pointer4 (T**** memory)
		{
			m_memory = memory;
			if (m_memory)
			{
				ReferenceMapIter iter = s_referenceMap.find(m_memory);
				if (iter != s_referenceMap.end())
				{
					++iter->second;
				}
				else
				{
					s_referenceMap[m_memory] = 1;
				}
			}
		}

		template <typename T>
		template <typename U>
		TE::Memory::Pointer4<T>::Pointer4 (const Pointer4<U>& ptr)
		{
			m_memory = ptr.m_memory;
			if (m_memory)
			{
				ReferenceMapIter iter = s_referenceMap.find(m_memory);
				if (iter != s_referenceMap.end())
				{
					++iter->second;
				}
				else
				{
					assert(false && "ptr.m_memory must be in the map\n");
				}
			}
		}

		template <typename T>
		TE::Memory::Pointer4<T>::~Pointer4 ()
		{
			if (m_memory)
			{
				ReferenceMapIter iter = s_referenceMap.find(m_memory);
				if (iter != s_referenceMap.end())
				{
					if (--iter->second == 0)
					{
						s_referenceMap.erase(m_memory);
						delete4(m_memory);
					}
				}
				else
				{
					assert(false && "m_memory must be in the map\n");
				}
			}
		}

		template <typename T>
		inline TE::Memory::Pointer4<T>::operator T**** () const
		{
			return m_memory;
		}

		template <typename T>
		inline T***& TE::Memory::Pointer4<T>::operator* () const
		{
			return *m_memory;
		}

		template <typename T>
		TE::Memory::Pointer4<T>& TE::Memory::Pointer4<T>::operator= (T**** memory)
		{
			if (m_memory != memory)
			{
				ReferenceMapIter iter;

				if (memory)
				{
					iter = s_referenceMap.find(memory);
					if (iter != s_referenceMap.end())
					{
						++iter->second;
					}
					else
					{
						s_referenceMap[memory] = 1;
					}
				}

				if (m_memory)
				{
					iter = s_referenceMap.find(m_memory);
					if (iter != s_referenceMap.end())
					{
						if (--iter->second == 0)
						{
							s_referenceMap.erase(m_memory);
							delete4(m_memory);
						}
					}
					else
					{
						assert(false && "m_memory must be in the map\n");
					}
				}

				m_memory = memory;
			}

			return *this;
		}

		template <typename T>
		TE::Memory::Pointer4<T>& TE::Memory::Pointer4<T>::operator= (const Pointer4& ptr)
		{
			if (m_memory != ptr.m_memory)
			{
				ReferenceMapIter iter;

				if (ptr.m_memory)
				{
					iter = s_referenceMap.find(ptr.m_memory);
					if (iter != s_referenceMap.end())
					{
						++iter->second;
					}
					else
					{
						assert(false && "ptr.m_memory must be in the map\n");
					}
				}

				if (m_memory)
				{
					iter = s_referenceMap.find(m_memory);
					if (iter != s_referenceMap.end())
					{
						if (--iter->second == 0)
						{
							s_referenceMap.erase(m_memory);
							delete4(m_memory);
						}
					}
					else
					{
						assert(false && "m_memory must be in the map\n");
					}
				}

				m_memory = ptr.m_memory;
			}

			return *this;
		}

		template <typename T>
		inline bool TE::Memory::Pointer4<T>::operator== (T**** memory) const
		{
			return m_memory == memory;
		}

		template <typename T>
		inline bool TE::Memory::Pointer4<T>::operator!= (T**** memory) const
		{
			return m_memory != memory;
		}

		template <typename T>
		inline bool TE::Memory::Pointer4<T>::operator== (const Pointer4& ptr) const
		{
			return m_memory == ptr.m_memory;
		}

		template <typename T>
		inline bool TE::Memory::Pointer4<T>::operator!= (const Pointer4& ptr) const
		{
			return m_memory != ptr.m_memory;
		}

		template <typename T>
		I32 TE::Memory::Pointer4<T>::GetReferenceCount()
		{
			ReferenceMapIter iter = s_referenceMap.find(m_memory);
			if (iter != s_referenceMap.end())
			{
				return iter->second;
			}
			return 0;
		}
	}
}

#endif