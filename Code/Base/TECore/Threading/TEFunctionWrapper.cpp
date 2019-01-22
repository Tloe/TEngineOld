#include "TEFunctionWrapper.h"

TE::Threading::FunctionWrapper::FunctionWrapper()
{

}

TE::Threading::FunctionWrapper::FunctionWrapper(FunctionWrapper && other)
    : m_function(std::move(other.m_function))
{

}

TE::Threading::FunctionWrapper& TE::Threading::FunctionWrapper::operator=( FunctionWrapper&& other )
{
	m_function = std::move(other.m_function);
	return *this;
}

void TE::Threading::FunctionWrapper::operator ()()
{
    m_function->Call();
}

TE::Threading::FunctionWrapper::FunctionWrapper(const TE::Threading::FunctionWrapper &)
{
}

