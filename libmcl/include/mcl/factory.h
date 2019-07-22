
#ifndef MCL_FACTORY_H_
#define MCL_FACTORY_H_

#include "lang.h"


#ifdef __cplusplus
#include <map>
#include <string>
#include <memory>
MCL_BEGIN_NAMESPACE(mcl)


/** ����ע����. */
template<class FactoryClass>
class FactoryRegistry
{
	typedef FactoryClass FactoryType;
	typedef FactoryRegistry<FactoryClass> RegistryType;
	typedef std::shared_ptr<FactoryClass> FactoryPointer;
	typedef std::map<const std::string, FactoryPointer> ContainerType;

public:
	/** �Ǽ�ָ�����͵Ĺ���. */
	void registerFactory(const std::string &name, const FactoryPointer &factory)
	{
		auto r = factories.insert(typename ContainerType::value_type(name, factory));
		if (!r.second)
			r.first->second = factory;
	}

	/** ��ȡָ�����ƵĹ���. */
	FactoryPointer getFactory(const std::string &name) const
	{
		auto ite = factories.find(name);
		return ite != factories.end() ? ite->second : FactoryPointer();
	}

	/** ��ȡĬ�Ϲ����ǼǱ�. */
	MCL_NOINLINE static FactoryRegistry<FactoryClass> *registry(MCL_NOINLINE_DOTDOTDOT);

private:
	ContainerType factories;
};

/** ��ȡĬ�Ϲ����ǼǱ�. */
template<class FactoryClass>
FactoryRegistry<FactoryClass> *FactoryRegistry<FactoryClass>::registry(MCL_NOINLINE_DOTDOTDOT)
{
	static FactoryRegistry<FactoryClass> s_registry;
	return &s_registry;
}


/** �Ǽ�ָ�����͵Ĺ�����Ĭ�ϵǼǱ�. */
template<class FactoryClass, class FactoryClassImpl = FactoryClass>
struct RegisterFactory
{
	RegisterFactory(const std::string &name) {
		static auto s_factory = std::make_shared<FactoryClassImpl>();
		FactoryRegistry<FactoryClass>::registry()->registerFactory(name, s_factory);
	}
};

MCL_END_NAMESPACE
#endif

#endif
