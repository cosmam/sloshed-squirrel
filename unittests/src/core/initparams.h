#ifndef INITPARAMS_T_H
#define INITPARAMS_T_H

#include <QVariant>

#include <memory>

namespace Test
{
    class InitParams
    {
    public:
        InitParams();

        ~InitParams();

        InitParams( const InitParams &rhs );
        InitParams &operator=( const InitParams &rhs );

        InitParams( InitParams &&rhs ) = default;
        InitParams &operator=( InitParams &&rhs ) = default;

        void insertValue( int key, QVariant value );

        QVariant value( int key ) const;

        bool contains( int key ) const;

    private:
        class Impl;
        std::unique_ptr<Impl> m_Impl;
    };
}

#endif // INITPARAMS_T_H
