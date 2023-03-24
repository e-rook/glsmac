#include "GameMenu.h"

#include "engine/Engine.h"
#include "../../../World.h"

namespace game {
namespace world {
namespace ui {
namespace menu {

GameMenu::GameMenu( World* world )
	: Menu( world )
{
#if DEBUG
	AddItem( "Save Dump..." );
	AddItem( "Load Dump..." );
#endif
	
	AddItem( "Start New Game", MH( this ) {
		m_world->ReturnToMainMenu();
		return false;
	});
	
	AddItem( "Quit", MH( this ) {
		g_engine->ShutDown();
		return false;
	});
}

}
}
}
}
