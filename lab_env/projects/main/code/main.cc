//------------------------------------------------------------------------------
// main.cc
// (C) 2015-2018 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "PBDScene.h"

int
main(int argc, const char** argv)
{
	PBD::PBDScene app;
	if (app.Open())
	{
		app.Run();
		app.Close();
	}
	app.Exit();
	
}