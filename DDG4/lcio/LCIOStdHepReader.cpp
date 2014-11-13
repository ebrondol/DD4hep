// $Id: Geant4Converter.cpp 603 2013-06-13 21:15:14Z markus.frank $
//====================================================================
//  AIDA Detector description implementation for LCD
//--------------------------------------------------------------------
//
//====================================================================
#ifndef DD4HEP_DDG4_LCIOSTDHEPREADER_H
#define DD4HEP_DDG4_LCIOSTDHEPREADER_H

// Framework include files
#include "LCIOEventReader.h"
// LCIO include files
#include "UTIL/LCStdHepRdr.h"

/// Namespace for the AIDA detector description toolkit
namespace DD4hep  {

  /// Namespace for the Geant4 based simulation part of the AIDA detector description toolkit
  namespace Simulation  {

    /// Base class to read StdHep files with lcio
    /**
     *  \author  P.Kostka (main author)
     *  \author  M.Frank  (code reshuffeling into new DDG4 scheme)
     *  \version 1.0
     *  \ingroup DD4HEP_SIMULATION
     */
    class LCIOStdHepReader : public LCIOEventReader  {
    protected:
      /// Reference to Reader object
      UTIL::LCStdHepRdr* m_reader;
    public:
      /// Initializing constructor
      LCIOStdHepReader(const std::string& nam);
      /// Default destructor
      virtual ~LCIOStdHepReader();
      /// Read an event and fill a vector of MCParticles.
      virtual EventReaderStatus readParticles(int event_number, EVENT::LCCollection** particles);
    };
  }     /* End namespace lcio   */
}       /* End namespace DD4hep */
#endif  /* DD4HEP_DDG4_LCIOSTDHEPREADER_H */

#include "DDG4/Factories.h"
// Factory entry
DECLARE_GEANT4_EVENT_READER_NS(DD4hep::Simulation,LCIOStdHepReader)

using namespace DD4hep::Simulation;

/// Initializing constructor
LCIOStdHepReader::LCIOStdHepReader(const std::string& nam) 
  : LCIOEventReader(nam)
{
  m_reader = new UTIL::LCStdHepRdr(m_name.c_str());
}

/// Default destructor
LCIOStdHepReader::~LCIOStdHepReader()    {
  DD4hep::deletePtr(m_reader);
}

/// Read an event and fill a vector of MCParticles.
Geant4EventReader::EventReaderStatus
LCIOStdHepReader::readParticles(int /*event_number */, EVENT::LCCollection** particles)  {
  *particles = m_reader->readEvent();
  if ( 0 == *particles ) return EVENT_READER_ERROR;
  return EVENT_READER_OK;
}