/*
  Copyright (c) 2008-2009 by Jakob Schroeter <js@camaya.net>
  This file is part of the gloox library. http://camaya.net/gloox

  This software is distributed under a license. The full license
  agreement can be found in the file LICENSE in this distribution.
  This software may not be copied, modified, sold or distributed
  other than expressed in the named license agreement.

  This software is distributed without any warranty.
*/


#ifndef JINGLETRANSPORT_H__
#define JINGLETRANSPORT_H__

#include "jingleplugin.h"

namespace gloox
{

  class Tag;

  namespace Jingle
  {

    /**
     * @brief An abstraction of a Jingle Transport.
     *
     * You should not need to use this class directly. See
     * @link gloox::Jingle::Session Jingle::Session @endlink for more info on Jingle.
     *
     * @author Jakob Schroeter <js@camaya.net>
     * @since 1.0
     */
    class Transport : public Plugin
    {
      public:
        /**
         * Virtual destructor.
         */
        virtual ~Transport() {}

        // reimplemented from Plugin
        virtual const std::string& filterString() const;

        // reimplemented from Plugin
        virtual Tag* tag() const;

      protected:
        /**
         * Returns the Transport's namespace.
         * @return The namespace being handled by the Transport.
         */
        virtual const std::string& xmlns() const = 0;

        /**
         *
         */
        virtual Tag* childTag() const = 0;

    };

  }

}

#endif // JINGLETRANSPORT_H__
