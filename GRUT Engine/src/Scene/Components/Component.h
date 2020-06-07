#pragma once
#include "Core/GRUTAlias.h"
#include "Core/Memory/ObjectHandle.h"

namespace GRUT {
    class GameObject;
    class ICollider;

    class Component {
        friend class GameObject;

        protected:
            ObjectHandle<Component> m_handle;
            template <class C>
            void SetHandle(ObjectHandle<C> p_handle);
            Component() = default;
            virtual ~Component() = default;

        public:
            ObjectHandle<GameObject> gameObject;
            virtual void Initialize() {}; //Called after m_handle is set
            virtual void FixedUpdate(float p_deltaTime) {};
            virtual void Update(float p_deltaTime) {};
            virtual void OnCollisionEnter(ObjectHandle<ICollider>& p_other) {};
            virtual void OnCollisionExit(ObjectHandle<ICollider>& p_other) {};
    };
    template<class C>
    inline void Component::SetHandle(ObjectHandle<C> p_handle) {
        m_handle = p_handle;
    }
}