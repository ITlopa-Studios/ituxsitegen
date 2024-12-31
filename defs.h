#ifndef HEADER_A476A47366E7E40
#define HEADER_A476A47366E7E40

#ifdef __unix__
#include <sys/stat.h>
#else
#include <direct.h>
#endif

/*
 * Copyright (C) 2025 ITlopa
 *
 * This file is part of ItuxSiteGen.
 *
 * ItuxSiteGen is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * ItuxSiteGen is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
*/

#ifdef __unix__
#define MAKE_DIRECTORY(dir_name) mkdir(dir_name, 0755)
#else
#define MAKE_DIRECTORY(dir_name) _mkdir(dir_name)
#endif






#ifdef __unix__
#define PAUSE() printf("Press Enter to continue..."); getchar()
#else
#define PAUSE() system("pause")
#endif

#endif // header guard

