/*********************************************************************
 *  AUTHOR: Tomas Soltys                                             *
 *  FILE:   session_entity_id.h                                      *
 *  GROUP:  Range                                                    *
 *  TYPE:   header file (*.h)                                        *
 *  DATE:   28-th January 2012                                       *
 *                                                                   *
 *  DESCRIPTION: Session Entity ID class declaration                 *
 *********************************************************************/

#ifndef SESSION_ENTITY_ID_H
#define SESSION_ENTITY_ID_H

#include <QtGlobal>

#include <rmlib.h>

class SessionEntityID
{

    private:

        //! Internal initialization function.
        void _init ( const SessionEntityID *pSessionEntityID = nullptr );

    protected:
        uint              mid;
        REntityGroupType type;
        uint              eid;

    public:

        //! Constructor.
        SessionEntityID();

        //! Constructor.
        SessionEntityID(uint mid, REntityGroupType type, uint eid);

        //! Copy constructor.
        SessionEntityID(const SessionEntityID &sessionEntityID);

        //! Destructor.
        ~SessionEntityID();

        //! Assignment operator.
        SessionEntityID & operator =(const SessionEntityID &sessionEntityID);

        //! Compare operator.
        bool operator ==(const SessionEntityID &sessionEntityID) const;

        //! Compare less operator.
        bool operator <(const SessionEntityID &sessionEntityID) const;

        //! Compare greater operator.
        bool operator >(const SessionEntityID &sessionEntityID) const;

        //! Return model ID.
        uint getMid(void) const;

        //! Set model ID.
        void setMid(uint mid);

        //! Return model ID.
        REntityGroupType getType(void) const;

        //! Set model ID.
        void setType(REntityGroupType type);

        //! Return entity ID.
        uint getEid(void) const;

        //! Set entity ID.
        void setEid(uint eid);

        //! Filter entities from the list based on the type.
        static QList<SessionEntityID> filterList(const QList<SessionEntityID> &entityList,REntityGroupTypeMask entityGroupTypeMask = R_ENTITY_GROUP_ALL);

        //! Produce list of entity IDs.
        static QList<uint> getEntityIDs(const QList<SessionEntityID> &entityList,REntityGroupTypeMask entityGroupTypeMask = R_ENTITY_GROUP_ALL);

};

#endif /* SESSION_ENTITY_ID_H */
