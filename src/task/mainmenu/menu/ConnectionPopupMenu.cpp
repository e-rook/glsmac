#include "ConnectionPopupMenu.h"

#include "lobby/Lobby.h"

namespace task {
namespace mainmenu {

ConnectionPopupMenu::ConnectionPopupMenu( MainMenu* mainmenu, const std::string& title )
	: PopupMenu( mainmenu, title ) {
	//
}

void ConnectionPopupMenu::Iterate() {
	auto* connection = m_mainmenu->m_state->GetConnection();
	if ( connection ) {
		connection->Iterate();
	}
}

void ConnectionPopupMenu::SetConnection( ::game::connection::Connection* connection ) {
	ASSERT( !m_mainmenu->m_state->GetConnection(), "connection already set" );
	m_mainmenu->m_state->SetConnection( connection );

	connection->m_on_connect = [ this, connection ]() -> void {
		if ( connection->IsServer() ) {
			// server always starts in lobby
			Show();
			NEWV( menu, lobby::Lobby, m_mainmenu, connection );
			//connection = nullptr;
			NextMenu( menu );
		}
		else {
			// client may join either lobby or running game, so need to check game state first
			connection->AsClient()->m_on_game_state_change = [ this, connection ]( const Connection::game_state_t game_state ) -> void {
				switch ( game_state ) {
					case Connection::GS_LOBBY: {
						Show();
						NEWV( menu, lobby::Lobby, m_mainmenu, connection );
						//connection = nullptr;
						NextMenu( menu );
						break;
					}
					case Connection::GS_RUNNING: {
						Log( "Game is already running, trying to join" );

						connection->m_on_global_settings_update = [ this ]() -> void {
							Log( "Got global settings packet" );
							Show();
							m_mainmenu->StartGame();
							GoBack(); // show previous menu if canceled
						};

						break;
					}
					default: {
						Log( "Unexpected game state: " + std::to_string( game_state ) );
						connection->m_on_error( "Unexpected game state" );
					}
				}
			};
		}
	};
	connection->m_on_error = [ this, connection ]( const std::string& message ) -> void {
		Show();
		const std::string text = message;
		DELETE( connection );
		m_mainmenu->m_state->DetachConnection();
		m_mainmenu->m_state->Reset();
		//connection = nullptr;
		MenuError( text );
	};
	connection->m_on_cancel = [ this, connection ]() -> void {
		Show();
		DELETE( connection );
		m_mainmenu->m_state->DetachConnection();
		m_mainmenu->m_state->Reset();
		//connection = nullptr;
	};
	connection->Connect();
}

}
}
