#include "GUILoader.hpp"

int main(int argc, char** argv)
{
	GUILoader gui(argc, argv);

  gui.Show();

	return gui.exec();
}

