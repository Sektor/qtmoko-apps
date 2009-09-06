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

#include "mixerslider.h"
#include <qdebug.h>

MixerSlider::MixerSlider(QWidget *parent, snd_mixer_elem_t *snd_mix)
  : QSlider( Qt::Horizontal, parent), snd_mix(snd_mix)
{
  long current;

  setObjectName(QString(snd_mixer_selem_get_name(snd_mix)));

  snd_mixer_selem_get_playback_volume_range(snd_mix, &min, &max);
  setMinimum(0);
  setMaximum(100);
  
  snd_mixer_selem_get_playback_volume
    (snd_mix, SND_MIXER_SCHN_FRONT_LEFT, &current);
  if (current < 0 || current > 255)
    setSliderPosition(0);
  else
    setSliderPosition((current * 100) / max);
    
  connect(this, SIGNAL(valueChanged(int)),
	  this, SLOT(setSndCurrentValue(int)));
}

MixerSlider::~MixerSlider()
{
}

void MixerSlider::setSndCurrentValue(int value)
{
  int realValue = (value * max) / 100;
  snd_mixer_selem_set_playback_volume
    (snd_mix, SND_MIXER_SCHN_FRONT_LEFT, realValue);
  snd_mixer_selem_set_playback_volume
    (snd_mix, SND_MIXER_SCHN_FRONT_RIGHT, realValue);
}
