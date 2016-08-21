#include "initparams.h"

#include <map>

using Test::InitParams;
using std::map;

class Test::InitParams::Impl
{
public:
    map<int, QVariant> data;
};

InitParams::InitParams() : m_Impl( new Test::InitParams::Impl )
{
}

InitParams::~InitParams() {}

InitParams::InitParams(const InitParams & rhs) : m_Impl( new Test::InitParams::Impl(*rhs.m_Impl))
{
}

InitParams & InitParams::operator=(const InitParams& rhs)
{
    *m_Impl = *rhs.m_Impl;
    return *this;
}

void InitParams::insertValue( int key, QVariant value )
{
    m_Impl->data[key] = value;
}

QVariant InitParams::value( int key ) const
{
    auto it = m_Impl->data.find( key );
    return ( it == m_Impl->data.end() ? QVariant() : it->second );
}

bool InitParams::contains( int key ) const
{
    return ( m_Impl->data.find( key ) != m_Impl->data.end() );
}
