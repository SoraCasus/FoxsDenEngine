/*
 *     Fox's Den Engine
 *     Copyright (C) 2021  Joshua Mayer
 *
 *     This program is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 *
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#ifdef FD_BUILD_DLL
#define FD_API __declspec( dllexport )
#else
#define FD_API __declspec( dllimport )
#endif

class FD_API Test {

public:

	void FD_API Execute();

};