#include "probanac.h"

class probanaCData : public QSharedData
{
public:

};

probanaC::probanaC() : data(new probanaCData)
{

}

probanaC::probanaC(const probanaC &rhs) : data(rhs.data)
{

}

probanaC &probanaC::operator=(const probanaC &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

probanaC::~probanaC()
{

}
