MESSAGE( STATUS "Fetching SDL2..." )

SET( SDL_PTHREADS ON )
ADD_COMPILE_DEFINITIONS( SDL_THREAD_GENERIC_COND_SUFFIX )

FETCHCONTENT_DECLARE( SDL2
	GIT_REPOSITORY https://github.com/libsdl-org/SDL
	GIT_TAG release-2.28.3
	)

FETCHCONTENT_MAKEAVAILABLE( SDL2 )
