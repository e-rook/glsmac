#include "Popup.h"

#include "engine/Engine.h"

namespace ui {
namespace object {

Popup::Popup( const std::string& class_name )
	: Section( class_name )
{
	SetAlign( ALIGN_CENTER );

}

void Popup::Create() {
	Section::Create();
	
	// TODO: fix blending
	// TODO: maybe not needed?
	/* NEW( m_background_locker, Surface, "PopupBackground" );
	g_engine->GetUI()->AddObject( m_background_locker ); */
}

void Popup::Destroy() {
	// TODO: fix blending
	// TODO: maybe not needed?
	//g_engine->GetUI()->RemoveObject( m_background_locker );
	
	Section::Destroy();
}

}
}
