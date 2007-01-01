/*************** <auto-copyright.pl BEGIN do not edit this line> **************
 *
 * VR Juggler is (C) Copyright 1998-2007 by Iowa State University
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
 *************** <auto-copyright.pl END do not edit this line> ***************/

package org.vrjuggler.tweek.event;

import javax.swing.event.EventListenerList;

import org.vrjuggler.tweek.beans.FileLoader;


/**
 * Interface for informing Tweek objects about file action events that occur
 * as a result of Tweek Beans manipulating files.  The Tweek Beans must
 * implement the BeanLoader interface.  Instances of this class must be
 * registered with org.vrjuggler.tweek.TweekCore using the method
 * TweekCore.registerFileActionGenerator().  When the generator is no longer
 * in use, it must be unregistered using the method
 * TweekCore.unregisterFileActionGenerator().
 *
 * @see FileLoader
 * @see org.vrjuggler.tweek.TweekCore
 *
 * @since 0.92.3
 */
public class FileActionGenerator
{
   /**
    * Adds the given FileActionListener implementation to the list of listeners
    * for file action events.
    *
    * @param l  the listener to add
    */
   public void addFileActionListener(FileActionListener l)
   {
      mListenerList.add(FileActionListener.class, l);
   }

   /**
    * Removes the given FileActionListener implementation from the list of
    * listeners for file action events.
    *
    * @param l  the listener to remove
    */
   public void removeFileActionListener(FileActionListener l)
   {
      mListenerList.remove(FileActionListener.class, l);
   }

   /**
    * Generates a file open action and delivers it to all the listeners
    * registered with this generator.  The method
    * FileActionListener.fileOpenPerformed() is invoked on all listeners.
    *
    * @param source     a reference to the Tweek Bean implementing the
    *                   FileLoader interface that is responsible for opening
    *                   the file
    *
    * @see FileActionListener
    */
   public void fireOpenPerformed(FileLoader source)
   {
      fireOpenPerformed(source, source);
   }

   /**
    * Generates a file open action and delivers it to all the listeners
    * registered with this generator.  The method
    * FileActionListener.fileOpenPerformed() is invoked on all listeners.
    *
    * @param source     the source of the event to be generated
    * @param loader     a reference to the Tweek Bean implementing the
    *                   FileLoader interface that is responsible for opening
    *                   the file
    *
    * @see FileActionListener
    *
    * @since 0.92.4
    */
   public void fireOpenPerformed(Object source, FileLoader loader)
   {
      FileActionEvent e = null;
      Object[] listeners = mListenerList.getListenerList();
      for ( int i = listeners.length - 2; i >= 0; i -= 2 )
      {
         if ( listeners[i] == FileActionListener.class )
         {
            if ( e == null )
            {
               e = new FileActionEvent(source, loader);
            }

            ((FileActionListener) listeners[i + 1]).fileOpenPerformed(e);
         }
      }
   }

   /**
    * Generates a file open action and delivers it to all the listeners
    * registered with this generator.  The method
    * FileActionListener.fileOpenPerformed() is invoked on all listeners.
    *
    * @param source     a reference to the Tweek Bean implementing the
    *                   FileLoader interface that is responsible for opening
    *                   the file
    *
    * @see FileActionListener
    */
   public void fireChangePerformed(FileLoader source)
   {
      fireChangePerformed(source, source);
   }

   /**
    * Generates a file open action and delivers it to all the listeners
    * registered with this generator.  The method
    * FileActionListener.fileOpenPerformed() is invoked on all listeners.
    *
    * @param source     the source of the event to be generated
    * @param loader     a reference to the Tweek Bean implementing the
    *                   FileLoader interface that is responsible for opening
    *                   the file
    *
    * @see FileActionListener
    *
    * @since 0.92.4
    */
   public void fireChangePerformed(Object source, FileLoader loader)
   {
      FileActionEvent e = null;
      Object[] listeners = mListenerList.getListenerList();
      for ( int i = listeners.length - 2; i >= 0; i -= 2 )
      {
         if ( listeners[i] == FileActionListener.class )
         {
            if ( e == null )
            {
               e = new FileActionEvent(source, loader);
            }

            ((FileActionListener) listeners[i + 1]).fileChangePerformed(e);
         }
      }
   }

   /**
    * Generates a file save action and delivers it to all the listeners
    * registered with this generator.  The method
    * FileActionListener.fileSavePerformed() is invoked on all listeners.
    *
    * @param source     a reference to the Tweek Bean implementing the
    *                   FileLoader interface that is responsible for saving
    *                   an open file
    *
    * @see FileActionListener
    */
   public void fireSavePerformed(FileLoader source)
   {
      fireSavePerformed(source, source);
   }

   /**
    * Generates a file save action and delivers it to all the listeners
    * registered with this generator.  The method
    * FileActionListener.fileSavePerformed() is invoked on all listeners.
    *
    * @param source     the source of the event to be generated
    * @param loader     a reference to the Tweek Bean implementing the
    *                   FileLoader interface that is responsible for saving
    *                   an open file
    *
    * @see FileActionListener
    *
    * @since 0.92.4
    */
   public void fireSavePerformed(Object source, FileLoader loader)
   {
      FileActionEvent e = null;
      Object[] listeners = mListenerList.getListenerList();
      for ( int i = listeners.length - 2; i >= 0; i -= 2 )
      {
         if ( listeners[i] == FileActionListener.class )
         {
            if ( e == null )
            {
               e = new FileActionEvent(source, loader);
            }

            ((FileActionListener) listeners[i + 1]).fileSavePerformed(e);
         }
      }
   }

   /**
    * Generates a file save-as action and delivers it to all the listeners
    * registered with this generator.  The method
    * FileActionListener.fileSaveAsPerformed() is invoked on all listeners.
    *
    * @param source     a reference to the Tweek Bean implementing the
    *                   FileLoader interface that is responsible for saving
    *                   an open file
    *
    * @see FileActionListener
    */
   public void fireSaveAsPerformed(FileLoader source)
   {
      fireSaveAsPerformed(source, source);
   }

   /**
    * Generates a file save-as action and delivers it to all the listeners
    * registered with this generator.  The method
    * FileActionListener.fileSaveAsPerformed() is invoked on all listeners.
    *
    * @param source     the source of the event to be generated
    * @param loader     a reference to the Tweek Bean implementing the
    *                   FileLoader interface that is responsible for saving
    *                   an open file
    *
    * @see FileActionListener
    *
    * @since 0.92.4
    */
   public void fireSaveAsPerformed(Object source, FileLoader loader)
   {
      FileActionEvent e = null;
      Object[] listeners = mListenerList.getListenerList();
      for ( int i = listeners.length - 2; i >= 0; i -= 2 )
      {
         if ( listeners[i] == FileActionListener.class )
         {
            if ( e == null )
            {
               e = new FileActionEvent(source, loader);
            }

            ((FileActionListener) listeners[i + 1]).fileSaveAsPerformed(e);
         }
      }
   }

   /**
    * Generates a file save-all action and delivers it to all the listeners
    * registered with this generator.  The method
    * FileActionListener.fileSaveAllPerformed() is invoked on all listeners.
    *
    * @param source     a reference to the Tweek Bean implementing the
    *                   FileLoader interface that is responsible for having
    *                   saved all the open files
    *
    * @see FileActionListener
    */
   public void fireSaveAllPerformed(FileLoader source)
   {
      fireSaveAllPerformed(source, source);
   }

   /**
    * Generates a file save-all action and delivers it to all the listeners
    * registered with this generator.  The method
    * FileActionListener.fileSaveAllPerformed() is invoked on all listeners.
    *
    * @param source     the source of the event to be generated
    * @param loader     a reference to the Tweek Bean implementing the
    *                   FileLoader interface that is responsible for having
    *                   saved all the open files
    *
    * @see FileActionListener
    *
    * @since 0.92.4
    */
   public void fireSaveAllPerformed(Object source, FileLoader loader)
   {
      FileActionEvent e = null;
      Object[] listeners = mListenerList.getListenerList();
      for ( int i = listeners.length - 2; i >= 0; i -= 2 )
      {
         if ( listeners[i] == FileActionListener.class )
         {
            if ( e == null )
            {
               e = new FileActionEvent(source, loader);
            }

            ((FileActionListener) listeners[i + 1]).fileSaveAllPerformed(e);
         }
      }
   }

   /**
    * Generates a file close action and delivers it to all the listeners
    * registered with this generator.  The method
    * FileActionListener.fileClosePerformed() is invoked on all listeners.
    *
    * @param source     a reference to the Tweek Bean implementing the
    *                   FileLoader interface that is responsible for closing
    *                   the file
    *
    * @see FileActionListener
    */
   public void fireClosePerformed(FileLoader source)
   {
      fireClosePerformed(source, source);
   }

   /**
    * Generates a file close action and delivers it to all the listeners
    * registered with this generator.  The method
    * FileActionListener.fileClosePerformed() is invoked on all listeners.
    *
    * @param source     the source of the event to be generated
    * @param loader     a reference to the Tweek Bean implementing the
    *                   FileLoader interface that is responsible for closing
    *                   the file
    *
    * @see FileActionListener
    *
    * @since 0.92.4
    */
   public void fireClosePerformed(Object source, FileLoader loader)
   {
      FileActionEvent e = null;
      Object[] listeners = mListenerList.getListenerList();
      for ( int i = listeners.length - 2; i >= 0; i -= 2 )
      {
         if ( listeners[i] == FileActionListener.class )
         {
            if ( e == null )
            {
               e = new FileActionEvent(source, loader);
            }

            ((FileActionListener) listeners[i + 1]).fileClosePerformed(e);
         }
      }
   }

   private EventListenerList mListenerList = new EventListenerList();
}
