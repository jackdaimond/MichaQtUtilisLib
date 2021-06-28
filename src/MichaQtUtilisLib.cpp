#include "MichaQtUtilisLib.h"

#define MAKE_STRING(name) #name
#define MAKE_VERSION(x)  MAKE_STRING(x)

namespace MichaLib
{



QVersionNumber getVersion()
{
    return QVersionNumber::fromString( MAKE_VERSION( MICHA_LIB_VERSION ) );
}

} //MichaLib
