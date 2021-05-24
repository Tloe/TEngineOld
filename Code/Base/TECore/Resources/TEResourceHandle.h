#ifndef TERESOURCEHANDLE_H
#define TERESOURCEHANDLE_H

#include "TEDataTypes.h"
#include <iostream>

namespace TE::Resources {
    template <typename ResourceT> class ResourceHandle {
      public:
        ResourceHandle();
        ResourceHandle(ResourceT &resource);
        ResourceHandle(const ResourceHandle &other);
        ResourceHandle &operator=(const ResourceHandle &rhs);
        ~ResourceHandle();
        operator bool() { return m_resource != 0; }
        ResourceT &operator*() const { return *m_resource; }
        ResourceT *operator->() const { return m_resource; }
        U32 GetReferenceCount() const { return m_resource->m_referenceCount; }
        void Reset();

      private:
        ResourceT *m_resource;
    };

    template <typename ResourceT> ResourceHandle<ResourceT>::ResourceHandle()
        : m_resource(nullptr) {}

    template <typename ResourceT> ResourceHandle<ResourceT>::ResourceHandle(ResourceT &resource)
        : m_resource(&resource) {
        ++m_resource->m_referenceCount;
    }

    template <typename ResourceT>
    ResourceHandle<ResourceT>::ResourceHandle(const ResourceHandle &other)
        : m_resource(other.m_resource) {
        ++m_resource->m_referenceCount;
    }

    template <typename ResourceT> ResourceHandle<ResourceT> &
    TE::Resources::ResourceHandle<ResourceT>::operator=(const ResourceHandle &rhs) {
        Reset();

        m_resource = rhs.m_resource;
        ++m_resource->m_referenceCount;

        return *this;
    }

    template <typename ResourceT> ResourceHandle<ResourceT>::~ResourceHandle() { Reset(); }

    template <typename ResourceT> void ResourceHandle<ResourceT>::Reset() {
        if (m_resource)
            --m_resource->m_referenceCount;

        m_resource = nullptr;
    }
}

#endif
