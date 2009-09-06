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

#include "qalsamixer.h"
#include "mixerslider.h"
#include "mixertoggle.h"

#include <qgroupbox.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <qdebug.h>
#include <qslider.h>
#include <qlabel.h>

QAlsaMixer::QAlsaMixer(QWidget *parent, Qt::WindowFlags fl)
  : QMainWindow(parent, fl)
{
  setWindowTitle(tr("Alsa Mixer"));
  if (openAlsaMixer() != 0)
    qWarning("Init mixer problem");
  else
    setCentralWidget(buildCentralWidget());
}

QAlsaMixer::~QAlsaMixer()
{
  closeAlsaMixer();
}

QWidget *QAlsaMixer::buildCentralWidget()
{
  QScrollArea *scrollArea = new QScrollArea;

  QGroupBox *groupBox = new QGroupBox(tr("mixers"));
  QVBoxLayout *vbox = new QVBoxLayout;

  snd_mixer_elem_t *elem;
  for (elem = snd_mixer_first_elem(mixerFd); elem;
       elem = snd_mixer_elem_next(elem)) {
    if (snd_mixer_elem_get_type(elem) == SND_MIXER_ELEM_SIMPLE &&
	snd_mixer_selem_is_active(elem)) {
      QString elemName = QString(snd_mixer_selem_get_name(elem));
      
      if (snd_mixer_selem_has_playback_volume(elem)) {
	  QGroupBox *internalGroupBox = new QGroupBox(elemName);
	  QVBoxLayout *internalVbox = new QVBoxLayout;
	  internalVbox->addWidget(new MixerSlider(this, elem));
	  internalGroupBox->setLayout(internalVbox);
	  vbox->addWidget(internalGroupBox);
      } else if (snd_mixer_selem_has_playback_switch(elem)) {
	vbox->addWidget(new MixerToggle(this, elem, elemName));
      }
    }
  }
  
  groupBox->setLayout(vbox);
  groupBox->setMinimumWidth(scrollArea->width() - 170); /* ugly but works */
  scrollArea->setWidget(groupBox);
  return scrollArea;
}

int QAlsaMixer::openAlsaMixer()
{
  int ret = 0;

  if ((ret = snd_mixer_open(&mixerFd, 0)) < 0) {
    qWarning() << "snd_mixer_open error" << ret;
    goto err;
  }
  if ((ret = snd_mixer_attach(mixerFd, "default")) < 0) {
    qWarning() << "snd_mixer_attach error" << ret;
    goto err;
  }
  if ((ret = snd_mixer_selem_register(mixerFd, NULL, NULL)) < 0) {
    qWarning() << "snd_mixer_selem_register error" << ret;
    goto err;
  }
  if ((ret = snd_mixer_load(mixerFd)) < 0) {
    qWarning() << "snd_mixer_load error" << ret;
    goto err;
  }
  
  goto ok;

 err:
  if (mixerFd)
    snd_mixer_close(mixerFd);
  mixerFd = NULL;
 ok:
  return ret;
}

void QAlsaMixer::closeAlsaMixer()
{
  if (mixerFd) {
    snd_mixer_detach(mixerFd, "default");
    snd_mixer_close(mixerFd);
    mixerFd = NULL;
  }
}
