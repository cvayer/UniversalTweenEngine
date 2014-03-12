#ifndef __TWEENPATHS__H__
#define __TWEENPATHS__H__

#include "CatmullRomPath.h"
#include "LinearPath.h"

namespace Tween
{
//--------------------------------------------------------------------------------------
// Paths
//--------------------------------------------------------------------------------------
namespace Path
{
	static CatmullRomPath		CATMULLROM;
	static LinearPath			LINEAR;

}// Namespace Path
}// Namespace Tween

#endif