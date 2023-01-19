#include "Theme.h"

namespace ui {
namespace theme {

void Theme::AddStyle( Style* style ) {
	ASSERT( !m_is_finalized, "adding style to finalized theme" );
	ASSERT( m_styles.find( style->GetClassName() ) == m_styles.end(), "style '" + style->GetClassName() + "' already exists" );
	m_styles[ style->GetStyleName() ] = style;
	m_styles_order.push_back( style->GetStyleName() );
}

void Theme::AddStyleSheet( StyleSheet* stylesheet ) {
	ASSERT( !m_is_finalized, "adding style to finalized theme" );
	for ( auto& style : stylesheet->GetStyles() ) {
		AddStyle( style );
	}
}

const Style* Theme::GetStyle( const string style_class ) const {
	ASSERT( m_is_finalized, "getting style from non-finalized theme" );
	ASSERT( m_styles.find( style_class ) != m_styles.end(), "style '" + style_class + "' does not exist" ); // TODO: make optional
	return m_styles.at( style_class );
}

void Theme::Finalize() {
	ASSERT( !m_is_finalized, "theme already finalized" );
	for ( auto& style : m_styles_order ) {
		m_styles.at( style )->Initialize();
	}
	m_is_finalized = true;
}

}
}
