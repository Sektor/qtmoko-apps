/*  accelerometers.cpp
 *
 *  Accelerometer stuff
 *
 *  (c) 2009 Anton Olkhovik <ant007h@gmail.com>
 *  (c) 2008 Thomas White <taw27@srcf.ucam.org>
 *  (c) 2008 Joachim Breitner <mail@joachim-breitner.de>
 *
 *  This library is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ACCELEROMETERS_H
#define ACCELEROMETERS_H

void accelerometer_start();
void accelerometer_stop();

double getacx();
double getacy();
double getacz();

#endif /* ACCELEROMETERS_H */

