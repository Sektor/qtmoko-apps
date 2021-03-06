/*
  Copyright (c) 2005-2009 by Jakob Schroeter <js@camaya.net>
  This file is part of the gloox library. http://camaya.net/gloox

  This software is distributed under a license. The full license
  agreement can be found in the file LICENSE in this distribution.
  This software may not be copied, modified, sold or distributed
  other than expressed in the named license agreement.

  This software is distributed without any warranty.
*/


#ifndef LASTACTIVITY_H__
#define LASTACTIVITY_H__

#include "iqhandler.h"

#include <time.h>

namespace gloox
{

  class JID;
  class ClientBase;
  class LastActivityHandler;

  /**
   * @brief This is an implementation of XEP-0012 (Last Activity) for both clients and components.
   *
   * LastActivity can be used to query remote entities about their last activity time as well
   * as answer incoming last-activity-queries.
   *
   * @author Jakob Schroeter <js@camaya.net>
   * @since 0.6
   */
  class GLOOX_API LastActivity : public IqHandler
  {
    public:
      /**
       * Constructs a new LastActivity object.
       * @param parent The ClientBase object to use for communication.
       */
      LastActivity( ClientBase* parent );

      /**
       * Virtual destructor.
       */
      virtual ~LastActivity();

      /**
       * Queries the given JID for their last activity. The result can be received by reimplementing
       * @ref LastActivityHandler::handleLastActivityResult() and
       * @ref LastActivityHandler::handleLastActivityError().
       */
      void query( const JID& jid );

      /**
       * Use this function to register an object as handler for incoming results of Last-Activity queries.
       * Only one handler is possible at a time.
       * @param lah The object to register as handler.
       */
      void registerLastActivityHandler( LastActivityHandler* lah ) { m_lastActivityHandler = lah; }

      /**
       * Use this function to un-register the LastActivityHandler set earlier.
       */
      void removeLastActivityHandler() { m_lastActivityHandler = 0; }

      /**
       * Use this function to reset the idle timer. By default the number of seconds since the
       * instantiation will be used.
       */
      void resetIdleTimer();

       // reimplemented from IqHandler
      virtual bool handleIq( const IQ& iq );

      // reimplemented from IqHandler
      virtual void handleIqID( const IQ& iq, int context );

    private:
#ifdef LASTACTIVITY_TEST
    public:
#endif
      class Query : public StanzaExtension
      {
        public:
          /**
           * Constructs a new Query object from the given Tag.
           * @param tag The Tag to parse.
           */
          Query( const Tag* tag = 0 );

          /**
           * Constructs a new Query object from the given long.
           * @param dummy Ignored.
           * @param seconds The number of seconds since last activity.
           */
          Query( int dummy, long seconds );

          /**
           * Virtual destructor.
           */
          virtual ~Query();

          /**
           * Returns the number of seconds since last activity.
           * @return The number of seconds since last activity.
           */
          long seconds() const { return m_seconds; }

          // reimplemented from StanzaExtension
          virtual const std::string& filterString() const;

          // reimplemented from StanzaExtension
          virtual StanzaExtension* newInstance( const Tag* tag ) const
          {
            return new Query( tag );
          }

          // reimplemented from StanzaExtension
          virtual Tag* tag() const;

          // reimplemented from StanzaExtension
          virtual StanzaExtension* clone() const
          {
            return new Query( *this );
          }

        private:
          long m_seconds;

      };

      LastActivityHandler* m_lastActivityHandler;
      ClientBase* m_parent;

      time_t m_active;

  };

}

#endif // LASTACTIVITY_H__
