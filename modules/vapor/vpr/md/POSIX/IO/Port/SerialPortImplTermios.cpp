/*************** <auto-copyright.pl BEGIN do not edit this line> **************
 *
 * VR Juggler is (C) Copyright 1998, 1999, 2000 by Iowa State University
 *
 * Original Authors:
 *   Allen Bierbaum, Christopher Just,
 *   Patrick Hartling, Kevin Meinert,
 *   Carolina Cruz-Neira, Albert Baker
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile$
 * Date modified: $Date$
 * Version:       $Revision$
 * -----------------------------------------------------------------
 *
 *************** <auto-copyright.pl END do not edit this line> ***************/

#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <errno.h>

#include <md/POSIX/SerialPortImpTermios.h>


extern int errno;

namespace vpr {

// ============================================================================
// Public methods.
// ============================================================================

// ----------------------------------------------------------------------------
// Constructor.  This creates a file handle object connected to the given port
// name and sets the update action to happen immediately.
// ----------------------------------------------------------------------------
SerialPortImpTermios::SerialPortImpTermios (const std::string& port_name)
    : Port(port_name), m_handle(NULL)
{
    m_handle = new FileHandleUNIX(port_name);
    setUpdateAction(SerialTypes::NOW);
}

// ----------------------------------------------------------------------------
// Destructor.  If the file handle is non-NULL, its memory is released.
// ----------------------------------------------------------------------------
SerialPortImpTermios::~SerialPortImpTermios () {
    if ( m_handle != NULL ) {
        delete m_handle;
    }
}

// ----------------------------------------------------------------------------
// Open the serial port and initialize its flags.
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::open () {
    Status status;

    status = m_handle->open();

    // If the serial port could not be opened, print an error message.
    if ( ! status.success() ) {
        fprintf(stderr,
                "[vpr::SerialPortImpTermios] Could not open serial port %s: %s\n",
                m_name.c_str(), strerror(errno));
        m_open = false;
    }
    // Otherwise, initialize the serial port's flags.
    else {
        struct termios term;

        m_open = true;

        if ( getAttrs(&term).success() ) {
            // Initialize all the flags to 0.
            term.c_iflag = term.c_oflag = term.c_cflag = term.c_lflag = 0;

            // Initialize the minimum buffer size to 1 and the timeout to 0.
            term.c_cc[VMIN]  = 1;
            term.c_cc[VTIME] = 0;

            // If we cannot set the initialized attribute flags on the port,
            // then we are not considered open.
            if ( ! setAttrs(&term, "Could not initialize flags").success() ) {
                m_open = false;
                status.setCode(Status::Failure);
            }
        }
    }

    return status;
}

// ----------------------------------------------------------------------------
// Get the current update action.  This tells when updates to the serial
// device take effect.
// ----------------------------------------------------------------------------
SerialTypes::UpdateActionOption
SerialPortImpTermios::getUpdateAction () {
    SerialTypes::UpdateActionOption action;

    switch (m_actions) {
      case TCSANOW:
        action = SerialTypes::NOW;
        break;
      case TCSADRAIN:
        action = SerialTypes::DRAIN;
        break;
      case TCSAFLUSH:
        action = SerialTypes::FLUSH;
        break;
    }

    return action;
}

// ----------------------------------------------------------------------------
// Change the current update action to take place as described by the given
// value.
// ----------------------------------------------------------------------------
void
SerialPortImpTermios::setUpdateAction (SerialTypes::UpdateActionOption action)
{
    switch (action) {
      case SerialTypes::NOW:
        m_actions = TCSANOW;
        break;
      case SerialTypes::DRAIN:
        m_actions = TCSADRAIN;
        break;
      case SerialTypes::FLUSH:
        m_actions = TCSAFLUSH;
        break;
    }
}

// ----------------------------------------------------------------------------
// Get the local attach state.  That is, test if the device is attached
// locally.
// ----------------------------------------------------------------------------
bool
SerialPortImpTermios::getLocalAttachState () {
    return getBit(CLOCAL, SerialPortImpTermios::CFLAG);
}

// ----------------------------------------------------------------------------
// Mark the device as locally attached.
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::enableLocalAttach () {
    return setBit(CLOCAL, SerialPortImpTermios::CFLAG, true,
                  "Could not enable local attachment");
}

// ----------------------------------------------------------------------------
// Mark the device as not locally attached.
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::disableLocalAttach () {
    return setBit(CLOCAL, SerialPortImpTermios::CFLAG, false,
                  "Could not disable local attachment");
}

// ----------------------------------------------------------------------------
// Query the serial port for the maximum buffer size.
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::getBufferSize (Uint8& size) {
    Status retval;
    struct termios term;

    if ( (retval = getAttrs(&term)).success() ) {
        size = term.c_cc[VMIN];
    }

    return retval;
}

// ----------------------------------------------------------------------------
// Attempt to change the buffer size to the given argument.
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::setBufferSize (const Uint8 size) {
    Status retval;
    struct termios term;

    if ( (retval = getAttrs(&term)).success() ) {
        term.c_cc[VMIN] = size;
        retval = setAttrs(&term, "Could not set minimum buffer size");
    }

    return retval;
}

// ----------------------------------------------------------------------------
// Get the value of the timeout (in tenths of a second) to wait for data to
// arrive.  This is only applicable in non-canonical mode.
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::getTimeout (Uint8& timeout) {
    Status retval;
    struct termios term;

    if ( (retval = getAttrs(&term)).success() ) {
        timeout = term.c_cc[VTIME];
    }

    return retval;
}

// ----------------------------------------------------------------------------
// Set the value of the timeout to wait for data to arrive.  The value given
// must be in tenths of a second.  This is only applicable in non-canonical
// mode.
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::setTimeout (const Uint8 timeout) {
    Status retval;
    struct termios term;

    if ( (retval = getAttrs(&term)).success() ) {
        term.c_cc[VTIME] = timeout;
        retval = setAttrs(&term, "Could not set minimum buffer size");
    }

    return retval;
}

// ----------------------------------------------------------------------------
// Get the character size (the bits per byte).
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::getCharacterSize (SerialTypes::CharacterSizeOption& size)
{
    Status retval;
    struct termios term;

    if ( (retval = getAttrs(&term)).success() ) {
        switch (term.c_cflag & CSIZE) {
          case CS5:
            size = SerialTypes::CS_BITS_5;
            break;
          case CS6:
            size = SerialTypes::CS_BITS_6;
            break;
          case CS7:
            size = SerialTypes::CS_BITS_7;
            break;
          case CS8:
            size = SerialTypes::CS_BITS_8;
            break;
        }
    }

    return retval;
}

// ----------------------------------------------------------------------------
// Set the current character size (the bits per byte) to the size in the given
// value.  This is used for both reding and writing, and the size does not
// include the parity bit (if any).
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::setCharacterSize (const SerialTypes::CharacterSizeOption bpb)
{
    struct termios term;
    Status retval;

    if ( (retval = getAttrs(&term)).success() ) {
        term.c_cflag &= ~CSIZE;	// Zero out the bits

        // Set the character size based on the given bits-per-byte value.
        switch (bpb) {
          // 5 bits/byte.
          case SerialTypes::CS_BITS_5:
            term.c_cflag |= CS5;
            break;
          // 6 bits/byte.
          case SerialTypes::CS_BITS_6:
            term.c_cflag |= CS6;
            break;
          // 7 bits/byte.
          case SerialTypes::CS_BITS_7:
            term.c_cflag |= CS7;
            break;
          // 8 bits/byte.
          case SerialTypes::CS_BITS_8:
            term.c_cflag |= CS8;
            break;
        }

        retval = setAttrs(&term, "Could not set character size");
    }

    return retval;
}

// ----------------------------------------------------------------------------
// Get the current read state for the port.
// ----------------------------------------------------------------------------
bool
SerialPortImpTermios::getReadState () {
    return getBit(CREAD, SerialPortImpTermios::CFLAG);
}

// ----------------------------------------------------------------------------
// Enable the receiver so that bytes can be read from the port.
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::enableRead () {
    return setBit(CREAD, SerialPortImpTermios::CFLAG, true,
                  "Could not enable reading");
}

// ----------------------------------------------------------------------------
// Disable the receiver so that bytes cannot be read from the port.
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::disableRead () {
    return setBit(CREAD, SerialPortImpTermios::CFLAG, false,
                  "Could not disable reading");
}

// ----------------------------------------------------------------------------
// Get the number of stop bits in use.  This will be either 1 or 2.
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::getStopBits (Uint8& num_bits) {
    struct termios term;
    Status retval;

    if ( (retval = getAttrs(&term)).success() ) {
        switch (term.c_cflag & CSTOPB) {
          case 0:
            num_bits = 1;
            break;
          case 1:
            num_bits = 2;
            break;
        }
    }

    return retval;
}

// ----------------------------------------------------------------------------
// Set the number of stop bits to use.  The value must be either 1 or 2.
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::setStopBits (const Uint8 num_bits) {
    struct termios term;
    Status retval;

    if ( (retval = getAttrs(&term)).success() ) {
        std::string msg;

        switch (num_bits) {
          case 1:
            term.c_cflag &= ~CSTOPB;
            break;
          case 2:
            term.c_cflag |= CSTOPB;
            break;
          default:
            fprintf(stderr,
                    "[vpr::SerialPortImpTermios] Stop bits may only be set to "
                    "1 or 2 on port %s\n", m_name.c_str());
            break;
        }

        // Construct the error message to send to setAttrs().
        msg = "Could set not stop bits to ";
        msg += num_bits;

        retval = setAttrs(&term, msg);
    }

    return retval;
}

// ----------------------------------------------------------------------------
// Get the current input echo state (either on or off) for the serial port.
// ----------------------------------------------------------------------------
bool
SerialPortImpTermios::getInputEchoState () {
    return getBit(ECHO, SerialPortImpTermios::LFLAG);
}

// ----------------------------------------------------------------------------
// Enable input echo.
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::enableInputEcho () {
    return setBit(ECHO, SerialPortImpTermios::LFLAG, true,
                  "Could not enable input echo");
}

// ----------------------------------------------------------------------------
// Disable input echo.
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::disableInputEcho () {
    return setBit(ECHO, SerialPortImpTermios::LFLAG, false,
                  "Could not disable input echo");
}

// ----------------------------------------------------------------------------
// Query the canonical input state of the serial port.  If canonical mode is
// enabled, the characters EOF, EOL, EOL2, ERASE, KILL, REPRINT, STATUS, and
// WERASE are enabled, and the input characters are assembled into lines.
// Otherwise, read requests are satisfied directly from the input queue, and a
// read will not return until the buffer is at its minimum capacity or the
// timeout has expired.  See getBufferSize() and getTimeout() for more
// information.
// ----------------------------------------------------------------------------
bool
SerialPortImpTermios::getCanonicalState () {
    return getBit(ICANON, SerialPortImpTermios::LFLAG);
}

// ----------------------------------------------------------------------------
// Enable canonical input.  See getCanonicalState() for more information about
// what this means.
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::enableCanonicalInput () {
    return setBit(ICANON, SerialPortImpTermios::LFLAG, true,
           "Could not enable canonical input mode");
}

// ----------------------------------------------------------------------------
// Disable canonical input.  See getCanonicalState() for more information
// about what this means.
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::disableCanonicalInput () {
    return setBit(ICANON, SerialPortImpTermios::LFLAG, false,
           "Could not disable canonical input mode");
}

// ----------------------------------------------------------------------------
// Get the current state of carriage return (CR) to newline (NL) translation.
// ----------------------------------------------------------------------------
bool
SerialPortImpTermios::getCRTranslateState () {
    return getBit(ICRNL, SerialPortImpTermios::IFLAG);
}

// ----------------------------------------------------------------------------
// Enable translation of received carriage returns to newlines.
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::enableCRTranslation () {
    return setBit(ICRNL, SerialPortImpTermios::IFLAG, true,
                  "Could not enable carriage return translation mode");
}

// ----------------------------------------------------------------------------
// Disable translation of received carriage returns to newlines.
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::disableCRTranslation () {
    return setBit(ICRNL, SerialPortImpTermios::IFLAG, false,
                  "Could not disable carriage return translation mode");
}

// ----------------------------------------------------------------------------
// Get the current state of ignoring received carriage returns (CRs).  If CRs
// are not ignored, they may be translated to newlines.
// ----------------------------------------------------------------------------
bool
SerialPortImpTermios::getCRIgnoreState () {
    return getBit(IGNCR, SerialPortImpTermios::IFLAG);
}

// ----------------------------------------------------------------------------
// Enable ignoring of received carriage returns.
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::enableCRIgnore () {
    return setBit(IGNCR, SerialPortImpTermios::IFLAG, true,
                  "Could not enable carriage return ignoring");
}

// ----------------------------------------------------------------------------
// Disable ignoring of received carriage returns.  Once disabled, received
// carriage returns may be converted to newlines.
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::disableCRIgnore () {
    return setBit(IGNCR, SerialPortImpTermios::IFLAG, false,
                  "Could not disable carriage return ignoring");
}

// ----------------------------------------------------------------------------
// Get the current state of ignoring bytes with framing errors (other than a
// BREAK) or parity errors.
// ----------------------------------------------------------------------------
bool
SerialPortImpTermios::getBadByteIgnoreState () {
    return getBit(IGNPAR, SerialPortImpTermios::IFLAG);
}

// ----------------------------------------------------------------------------
// Enable ignoring of received bytes with framing errors or parity errors.
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::enableBadByteIgnore () {
    return setBit(IGNPAR, SerialPortImpTermios::IFLAG, true,
                  "Could not enable bad byte ignoring");
}

// ----------------------------------------------------------------------------
// Disable ignoring of received bytes with framing errors or parity errors.
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::disableBadByteIgnore () {
    return setBit(IGNPAR, SerialPortImpTermios::IFLAG, false,
                  "Could not disable bad byte ignoring");
}

// ----------------------------------------------------------------------------
// Get the state of parity checking for input.
// ----------------------------------------------------------------------------
bool
SerialPortImpTermios::getInputParityCheckState () {
    return getBit(IGNPAR, SerialPortImpTermios::IFLAG);
}

// ----------------------------------------------------------------------------
// Enable input parity checking.
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::enableInputParityCheck () {
    return setBit(INPCK, SerialPortImpTermios::IFLAG, true,
                  "Could not enable input parity checking");
}

// ----------------------------------------------------------------------------
// Disable input parity checking.
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::disableInputParityCheck () {
    return setBit(INPCK, SerialPortImpTermios::IFLAG, false,
                  "Could not disable input parity checking");
}

// ----------------------------------------------------------------------------
// Get the current signal generation state.  If it is enabled, the input bytes
// are checked against signal values.  If equal, the corresponding signal is
// generated.
// ----------------------------------------------------------------------------
bool
SerialPortImpTermios::getSignalGenerateState () {
    return getBit(ISIG, SerialPortImpTermios::LFLAG);
}

// ----------------------------------------------------------------------------
// Enable signal generation.  The signals checked are interrupt, quit, and
// suspend.
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::enableSignalGeneration () {
    return setBit(ISIG, SerialPortImpTermios::LFLAG, true,
                  "Could not enable signal generation for input characters");
}

// ----------------------------------------------------------------------------
// Disable signal generation.
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::disableSignalGeneration () {
    return setBit(ISIG, SerialPortImpTermios::LFLAG, false,
                  "Could not disable signal generation for input characters");
}

// ----------------------------------------------------------------------------
// Get the current state of bit stripping.  When enabled, input bytes are
// stripped to seven bits.  Otherwise, all eight bits are processed.
// ----------------------------------------------------------------------------
bool
SerialPortImpTermios::getBitStripState () {
    return getBit(ISTRIP, SerialPortImpTermios::IFLAG);
}

// ----------------------------------------------------------------------------
// Enable stripping of input bytes to seven bits.
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::enableBitStripping () {
    return setBit(ISTRIP, SerialPortImpTermios::IFLAG, true,
                  "Could not enable bit stripping from eight to seven bits");
}

// ----------------------------------------------------------------------------
// Disable stripping of input bytes to seven bits.
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::disableBitStripping () {
    return setBit(ISTRIP, SerialPortImpTermios::IFLAG, false,
                  "Could not disable bit stripping");
}

// ----------------------------------------------------------------------------
// Get the state of start-stop input control.  When enabled, if the terminal
// driver sees that the receive buffer is getting full, a STOP command is sent
// to the serial device.  The device should respond by halting its data flow.
// When the input queue has been processed, a START command is sent to the
// serial device which should cause it to resume putting bytes onto the input
// queue.
// ----------------------------------------------------------------------------
bool
SerialPortImpTermios::getStartStopInputState () {
    return getBit(IXOFF, SerialPortImpTermios::IFLAG);
}

// ----------------------------------------------------------------------------
// Enable start-stop input control.  See getStartStopInputState() for more
// information.
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::enableStartStopInput () {
    return setBit(IXOFF, SerialPortImpTermios::IFLAG, true,
                  "Could not enable start-stop input control");
}

// ----------------------------------------------------------------------------
// Disable start-stop input control.  See getStartStopInputState() for more
// information.
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::disableStartStopInput () {
    return setBit(IXOFF, SerialPortImpTermios::IFLAG, false,
                  "Could not disable start-stop input control");
}

// ----------------------------------------------------------------------------
// Get the state of start-stop output control.  When enabled, when the
// terminal driver receives a STOP command, output stops.  When it receives a
// START command, output resumes.  If disabled, these/ commands are read as
// normal characters.
// ----------------------------------------------------------------------------
bool
SerialPortImpTermios::getStartStopOutputState () {
    return getBit(IXON, SerialPortImpTermios::IFLAG);
}

// ----------------------------------------------------------------------------
// Enable start-stop input control.  See getStartStopInputState() for more
// information.
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::enableStartStopOutput () {
    return setBit(IXON, SerialPortImpTermios::IFLAG, true,
                  "Could not enable start-stop output control");
}

// ----------------------------------------------------------------------------
// Disable start-stop input control.  See getStartStopInputState() for more
// information.
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::disableStartStopOutput () {
    return setBit(IXON, SerialPortImpTermios::IFLAG, false,
                  "Could not disable start-stop output control");
}

// ----------------------------------------------------------------------------
// Get the current state of parity generation for outgoing bytes and parity
// checking for incoming bytes.
// ----------------------------------------------------------------------------
bool
SerialPortImpTermios::getParityGenerationState () {
    return getBit(PARENB, SerialPortImpTermios::CFLAG);
}

// ----------------------------------------------------------------------------
// Enable parity generation for outgoing bytes and parity checking for
// incoming bytes.
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::enableParityGeneration () {
    return setBit(PARENB, SerialPortImpTermios::CFLAG, true,
                  "Could not enable parity generation on outgoing characters");
}

// ----------------------------------------------------------------------------
// Disable parity generation for outgoing bytes and parity checking for
// incoming bytes.
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::disableParityGeneration () {
    return setBit(PARENB, SerialPortImpTermios::CFLAG, false,
                  "Could not disable parity generation on outgoing characters");
}

// ----------------------------------------------------------------------------
// Enable marking of bytes with parity errors or framing errors (except
// BREAKs).  This is only active if input parity and framing error reporting
// is enabled (see getInputParityCheckState() for more information).  The mark
// is the three-byte sequence \377 \0 X where X is the byte received in error.
// If bit stripping is enabled, a valid \377 byte is passed as the two-byte
// sequence \377 \377.
// ----------------------------------------------------------------------------
bool
SerialPortImpTermios::getParityErrorMarkingState () {
    return getBit(PARMRK, SerialPortImpTermios::IFLAG);
}

// ----------------------------------------------------------------------------
// Enable parity error and framing error marking.
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::enableParityErrorMarking () {
    return setBit(PARMRK, SerialPortImpTermios::IFLAG, true,
                  "Could not enable parity error marking");
}

// ----------------------------------------------------------------------------
// Disable parity error and framing error marking.
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::disableParityErrorMarking () {
    return setBit(PARMRK, SerialPortImpTermios::IFLAG, false,
                  "Could not disable parity error marking");
}

// ----------------------------------------------------------------------------
// Get the current parity checking type (either odd or even).
// ----------------------------------------------------------------------------
SerialTypes::ParityType
SerialPortImpTermios::getParity () {
    SerialTypes::ParityType retval;

    // Odd parity if PARODD is set.
    if ( getBit(PARODD, SerialPortImpTermios::CFLAG) ) {
        retval = SerialTypes::PARITY_ODD;
    }
    // Even parity if PARODD is not set.
    else {
        retval = SerialTypes::PARITY_EVEN;
    }

    return retval;
}

// ----------------------------------------------------------------------------
// Enable odd parity.
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::setOddParity () {
    return setBit(PARODD, SerialPortImpTermios::CFLAG, true,
                  "Could not set odd parity");
}

// ----------------------------------------------------------------------------
// Enable even parity.
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::setEvenParity () {
    return setBit(PARODD, SerialPortImpTermios::CFLAG, false,
                  "Could not set even parity");
}

// ----------------------------------------------------------------------------
// Get the current input baud rate.
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::getInputBaudRate (Uint32& rate) {
    struct termios term;
    Status retval;

    if ( (retval = getAttrs(&term)).success() ) {
        speed_t baud_rate;

        baud_rate = cfgetispeed(&term);
        rate      = baudToInt(baud_rate);
    }

    return retval;
}

// ----------------------------------------------------------------------------
// Set the current input baud rate.
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::setInputBaudRate (const Uint32 baud) {
    struct termios term;
    Status retval;

    if ( (retval = getAttrs(&term)).success() ) {
        speed_t new_rate;

        new_rate = intToBaud(baud);

fprintf(stderr, "Setting input baud rate to %d\n", new_rate);

        if ( cfsetispeed(&term, new_rate) == -1 ) {
            fprintf(stderr,
                    "Failed to set the input baud rate to %u on port %s: %s\n",
                    baud, m_name.c_str(), strerror(errno));
            retval.setCode(Status::Failure);
        }
        else {
            std::string msg;

            msg     = "Failed to set the input baud rate to ";
            msg    += baud;
            retval  = setAttrs(&term, msg);
        }
    }

    return retval;
}

// ----------------------------------------------------------------------------
// Get the current output baud rate.
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::getOutputBaudRate (Uint32& rate) {
    struct termios term;
    Status retval;

    if ( (retval = getAttrs(&term)).success() ) {
        speed_t baud_rate;

        baud_rate = cfgetospeed(&term);
        rate      = baudToInt(baud_rate);
    }

    return retval;
}

// ----------------------------------------------------------------------------
// Set the current output baud rate.
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::setOutputBaudRate (const Uint32 baud) {
    struct termios term;
    Status retval;

    if ( (retval = getAttrs(&term)).success() ) {
        speed_t new_rate;

        new_rate = intToBaud(baud);

fprintf(stderr, "Setting output baud rate to %d\n", new_rate);

        if ( cfsetospeed(&term, new_rate) == -1 ) {
            fprintf(stderr,
                    "Failed to set the output baud rate to %u on port %s: %s\n",
                    baud, m_name.c_str(), strerror(errno));
            retval.setCode(Status::Failure);
        }
        else {
            std::string msg;

            msg     = "Failed to set the output baud rate to ";
            msg    += baud;
            retval  = setAttrs(&term, msg);
        }
    }

    return retval;
}

// ----------------------------------------------------------------------------
// Wait for all output to be transmitted.
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::drainOutput () {
    Status retval;

    if ( tcdrain(m_handle->m_fdesc) == -1 ) {
        fprintf(stderr,
                "[vpr::SerialPortImpTermios] Failed to drain output on port %s: %s\n",
                m_name.c_str(), strerror(errno));
        retval.setCode(Status::Failure);
    }

    return retval;
}

// ----------------------------------------------------------------------------
// Alter the input or output flow control.  Based on the
// vpr::SerialTypes::FlowActionOption argument, output can be suspended and
// restarted or the terminal device can be told to stop or to resume sending
// data.
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::controlFlow (SerialTypes::FlowActionOption opt) {
    int action;
    Status retval;

    switch (opt) {
      case SerialTypes::OUTPUT_OFF:
        action = TCOOFF;
        break;
      case SerialTypes::OUTPUT_ON:
        action = TCOON;
        break;
      case SerialTypes::INPUT_OFF:
        action = TCIOFF;
        break;
      case SerialTypes::INPUT_ON:
        action = TCION;
        break;
    }

    if ( tcflow(m_handle->m_fdesc, action) == -1 ) {
        fprintf(stderr,
                "[vpr::SerialPortImpTermios] Failed to alter flow control on "
                "port %s: %s\n", m_name.c_str(), strerror(errno));
        retval.setCode(Status::Failure);
    }

    return retval;
}

// ----------------------------------------------------------------------------
// Discard either the input buffer (unread data received from the terminal
// device) or the output buffer (data written but not yet transmitted to the
// terminal device).  The argument tells which queue (or queues) to flush.
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::flushQueue (SerialTypes::FlushQueueOption vpr_queue) {
    int queue;
    Status retval;

    switch (vpr_queue) {
      case SerialTypes::INPUT_QUEUE:
        queue = TCIFLUSH;
        break;
      case SerialTypes::OUTPUT_QUEUE:
        queue = TCOFLUSH;
        break;
      case SerialTypes::IO_QUEUES:
        queue = TCIOFLUSH;
        break;
    }

    if ( tcflush(m_handle->m_fdesc, queue) == -1 ) {
        std::string queue_name;

        switch (vpr_queue) {
          case SerialTypes::INPUT_QUEUE:
            queue_name = "input queue";
            break;
          case SerialTypes::OUTPUT_QUEUE:
            queue_name = "output queue";
            break;
          case SerialTypes::IO_QUEUES:
            queue_name = "input and output queues";
            break;
        }

        fprintf(stderr,
                "[vpr::SerialPortImpTermios] Failed to flush %s on port %s: %s\n",
                queue_name.c_str(), m_name.c_str(), strerror(errno));
        retval.setCode(Status::Failure);
    }

    return retval;
}

// ----------------------------------------------------------------------------
// Transmit a continuous stream of zero bits for the given duration.  If the
// argument is 0, the transmission will last between 0.25 and 0.5 seconds.
// Otherwise, the duration specfies the number of seconds to send the zero bit
// stream.
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::sendBreak (const Int32 duration) {
    Status retval;

    if ( tcsendbreak(m_handle->m_fdesc, duration) == -1 ) {
        fprintf(stderr,
                "[vpr::SerialPortImpTermios] Failed to send break on port %s: %s\n",
                m_name.c_str(), strerror(errno));
        retval.setCode(Status::Failure);
    }

    return retval;
}

// ============================================================================
// Protected methods.
// ============================================================================

// ----------------------------------------------------------------------------
// Set the control character at the given index to the given value.
// ----------------------------------------------------------------------------
void
SerialPortImpTermios::setControlCharacter (const Uint32 index,
                                           const Uint8 value)
{
    struct termios term;

    if ( getAttrs(&term).success() ) {
        if ( index < NCCS ) {
            std::string msg;

            term.c_cc[index] = value;

            msg  = "Could not set control character ";
            msg += index;
            msg += " to ";
            msg += value;
            setAttrs(&term, msg);
        }
        else {
            fprintf(stderr,
                    "[vpr::SerialPortImpTermios] Index %u too large for "
                    "control character array\n", index);
        }
    }
}

// ----------------------------------------------------------------------------
// Get the value of the control character at the given index.
// ----------------------------------------------------------------------------
Uint8
SerialPortImpTermios::getControlCharacter (const Uint32 index) {
    struct termios term;
    Uint8 retval;

    retval = 0;

    if ( getAttrs(&term).success() ) {
        if ( index < NCCS ) {
            retval = term.c_cc[index];
        }
        else {
            fprintf(stderr,
                    "[vpr::SerialPortImpTermios] Index %u too large for "
                    "control character array\n", index);
        }
    }

    return retval;
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::getAttrs (struct termios* term) {
    Status retval;

    if ( tcgetattr(m_handle->m_fdesc, term) == -1 ) {
        fprintf(stderr,
                "[vpr::SerialPortImpTermios] Could not get attributes for port %s: %s\n",
                m_name.c_str(), strerror(errno));
        retval.setCode(Status::Failure);
    }

    return retval;
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::setAttrs (struct termios* term, const char* err_msg,
                                const bool print_sys_err)
{
    Status retval;

fprintf(stderr, "[vpr::SerialPortImpTermios] term->c_iflag: %d\n",
        term->c_iflag);
fprintf(stderr, "[vpr::SerialPortImpTermios] term->c_oflag: %d\n",
        term->c_oflag);
fprintf(stderr, "[vpr::SerialPortImpTermios] term->c_cflag: %d\n",
        term->c_cflag);
fprintf(stderr, "[vpr::SerialPortImpTermios] term->c_lflag: %d\n",
        term->c_lflag);
fprintf(stderr, "[vpr::SerialPortImpTermios] term->c_ispeed: %d\n",
        cfgetispeed(term));
fprintf(stderr, "[vpr::SerialPortImpTermios] term->c_ospeed: %d\n\n",
        cfgetospeed(term));
fprintf(stderr, "[vpr::SerialPortImpTermios] term->c_cc[]:");
for ( int i = 0; i < NCCS; i++ ) {
    fprintf(stderr, " %u", (unsigned int) term->c_cc[i]);
}
fprintf(stderr, "\n");

    if ( tcsetattr(m_handle->m_fdesc, m_actions, term) == -1 ) {
        fprintf(stderr, "[vpr::SerialPortImpTermios] %s (port '%s')", err_msg,
                m_name.c_str());

        if ( print_sys_err ) {
            fprintf(stderr, ": %s", strerror(errno));
        }

        fprintf(stderr, "\n");

        retval.setCode(Status::Failure);
    }

    return retval;
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::setAttrs (struct termios* term,
                                const std::string& err_msg,
                                const bool print_sys_err)
{
    return setAttrs(term, err_msg.c_str(), print_sys_err);
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
bool
SerialPortImpTermios::getBit (const tcflag_t bit,
                              SerialPortImpTermios::_term_flag flag)
{
    struct termios term;
    bool retval;

    if ( ! getAttrs(&term).success() ) {
        retval = false;
    }
    else {
        switch (flag) {
          case IFLAG:
            retval = ((term.c_iflag & bit) != 0);
          case OFLAG:
            retval = ((term.c_oflag & bit) != 0);
          case CFLAG:
            retval = ((term.c_cflag & bit) != 0);
          case LFLAG:
            retval = ((term.c_lflag & bit) != 0);
        }
    }

    return retval;
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
Status
SerialPortImpTermios::setBit (const tcflag_t bit,
                              SerialPortImpTermios::_term_flag flag,
                              const bool enable,
                              const std::string& err_msg,
                              const bool print_sys_err)
{
    struct termios term;
    Status retval;

    if ( (retval = getAttrs(&term)).success() ) {
        // Set the bit for this port.
        if ( enable ) {
            switch (flag) {
              case IFLAG:
                term.c_iflag |= bit;
                break;
              case OFLAG:
                term.c_oflag |= bit;
                break;
              case CFLAG:
                term.c_cflag |= bit;
                break;
              case LFLAG:
                term.c_lflag |= bit;
                break;
            }
        }
        // Reset the bit for this port.
        else {
            switch (flag) {
              case IFLAG:
                term.c_iflag &= ~bit;
                break;
              case OFLAG:
                term.c_oflag &= ~bit;
                break;
              case CFLAG:
                term.c_cflag &= ~bit;
                break;
              case LFLAG:
                term.c_lflag &= ~bit;
                break;
            }
        }

        retval = setAttrs(&term, err_msg, print_sys_err);
    }

    return retval;
}

// ----------------------------------------------------------------------------
// Convert a termios baud rate to its corresponding integer value.
// ----------------------------------------------------------------------------
Uint32
SerialPortImpTermios::baudToInt (const speed_t baud_rate) {
    Uint32 retval;

    switch (baud_rate) {
      case B50:
        retval = 50;
        break;
      case B75:
        retval = 75;
        break;
      case B110:
        retval = 110;
        break;
      case B134:
        retval = 134;
        break;
      case B150:
        retval = 150;
        break;
      case B200:
        retval = 200;
        break;
      case B300:
        retval = 300;
        break;
      case B600:
        retval = 600;
        break;
      case B1200:
        retval = 1200;
        break;
      case B1800:
        retval = 1800;
        break;
      case B2400:
        retval = 2400;
        break;
      case B4800:
        retval = 4800;
        break;
      case B9600:
        retval = 9600;
        break;
      case B19200:
        retval = 19200;
        break;
      case B38400:
        retval = 38400;
        break;
      default:
        retval = baud_rate;
        break;
    }

    return retval;
}

// ----------------------------------------------------------------------------
// Convert an integer baud rate to the corresponding termios rate constant.
// ----------------------------------------------------------------------------
speed_t
SerialPortImpTermios::intToBaud (const Uint32 speed_int) {
    speed_t rate;

    switch (speed_int) {
      case 50:
        rate = B50;
        break;
      case 75:
        rate = B75;
        break;
      case 110:
        rate = B110;
        break;
      case 134:
        rate = B134;
        break;
      case 150:
        rate = B150;
        break;
      case 200:
        rate = B200;
        break;
      case 300:
        rate = B300;
        break;
      case 600:
        rate = B600;
        break;
      case 1200:
        rate = B1200;
        break;
      case 1800:
        rate = B1800;
        break;
      case 2400:
        rate = B2400;
        break;
      case 4800:
        rate = B4800;
        break;
      case 9600:
        rate = B9600;
        break;
      case 19200:
        rate = B19200;
        break;
      case 38400:
        rate = B38400;
        break;
      default:
        rate = speed_int;
        break;
    }

    return rate;
}

}; // End of vpr namespace
