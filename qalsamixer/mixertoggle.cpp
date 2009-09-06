/*
 *  Jeremy Compostella <jeremy.compostella@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or (at
 *  your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
 */

#include "mixertoggle.h"
#include <qdebug.h>

MixerToggle::MixerToggle(QWidget *parent, snd_mixer_elem_t *snd_mix, QString name)
  : QCheckBox(name, parent), snd_mix(snd_mix)
{
  int current;
  snd_mixer_selem_get_playback_switch
    (snd_mix, SND_MIXER_SCHN_FRONT_LEFT, &current);
  setChecked(current);
  connect(this, SIGNAL(stateChanged(int)),
	  this, SLOT(setSndState(int)));
}

MixerToggle::~MixerToggle() {}

void MixerToggle::setSndState(int state)
{
  snd_mixer_selem_set_playback_switch
    (snd_mix, SND_MIXER_SCHN_FRONT_LEFT, state == Qt::Checked ? 1 : 0);
}
