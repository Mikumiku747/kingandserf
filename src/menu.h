//Text based menu header file
//Copyright Daniel Selmes 2015
//This file is part of King and the Serf (or kats).
//----------------------------------------------------------------------
//kats is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//kats is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with kats.  If not, see <http://www.gnu.org/licenses/>.
//----------------------------------------------------------------------

#ifndef _MENU_H
#define _MENU_H

//Define some text color constants
#define WHITEONBLACK "[47m[30m"
#define BLACKONWHITE "[40m[37m"
#define NORMALCOLORS "[49m[39m"

int presentMenu(char *question, int optionsc, char **optionsv);

int askYesNo(char *question);

int askForCard(char *question);

#endif
